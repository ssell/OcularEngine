/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Scene/BVHSceneTree.hpp"
#include "Math/MortonCode.hpp"
#include "Math/MathCommon.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        BVHSceneTree::BVHSceneTree()
        {
            m_Root = nullptr;
            m_IsDirty = true;
        }

        BVHSceneTree::~BVHSceneTree()
        {
            destroy();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void BVHSceneTree::restructure()
        {
            OCULAR_PROFILE()

            if(m_IsDirty)
            {
                if(rebuildNeeded())
                {
                    // A complete rebuild is needed.
                    rebuild();
                }
                else
                {
                    insertNewObjects();
                    updateDirtyNodes();
                }

                m_IsDirty = false;
            }
        }
        
        void BVHSceneTree::destroy()
        {
            if(m_Root)
            {
                destroyNode(m_Root);
                m_Root = nullptr;

                m_NewObjects.clear();
                m_AllObjects.clear();
            }
        }
        
        void BVHSceneTree::addObject(SceneObject* object)
        {
            if(object)
            {
                m_NewObjects.emplace_back(object);
                m_IsDirty = true;
            }
        }

        void BVHSceneTree::addObjects(std::vector<SceneObject*> const& objects)
        {
            if(objects.size() > 0)
            {
                for(auto object : objects)
                {
                    if(object)
                    {
                        m_NewObjects.emplace_back(object);
                    }
                }

                m_IsDirty = true;
            }
        }
        
        bool BVHSceneTree::removeObject(SceneObject* object)
        {
            bool result = false;

            if(object)
            {
                BVHSceneNode* leaf = findParent(m_Root, object);

                if(leaf)
                {
                    //----------------------------------------------------
                    // Must remove the leaf node and organize the tree.

                    BVHSceneNode* parent = dynamic_cast<BVHSceneNode*>(leaf->parent);

                    if(parent->type == SceneNodeType::Root)
                    {
                        // If the parent is the root, we can simply remove the leaf.

                        if(parent->left == leaf)
                        {
                            // Remove the left child and shift the right over

                            delete leaf;
                            leaf = nullptr;

                            parent->left = parent->right;
                            parent->right = nullptr;
                        }
                        else
                        {
                            // This is the right child of the root. Can simply remove.

                            delete leaf;
                            leaf = nullptr;
                            parent->right = nullptr;
                        }

                        m_Root->morton = m_Root->left->morton;
                        fitNodeBounds(m_Root);
                    }
                    else
                    {
                        // The parent is a non-root internal node.

                        // The parent will be removed and the remaining child will be moved
                        // to be a child of the parent's parent.

                        BVHSceneNode* survivingChild = (parent->left == leaf) ? parent->right : parent->left;
                        BVHSceneNode* parentParent = dynamic_cast<BVHSceneNode*>(parent->parent);

                        if(parentParent->left == parent)
                        {
                            parentParent->left = survivingChild;
                        }
                        else
                        {
                            parentParent->right = survivingChild;
                        }

                        survivingChild->parent = parentParent;

                        delete leaf;
                        delete parent;

                        leaf = nullptr;
                        parent = nullptr;

                        uint64_t morton = 0;

                        if(parentParent->left)
                        {
                            morton = parentParent->left->morton;

                            if(parentParent->right)
                            {
                                morton += parentParent->right->morton;
                                morton /= 2;
                            }
                        }
                        else if(parentParent->right)
                        {
                            morton = parentParent->right->morton;
                        }

                        parentParent->morton = morton;
                        fitNodeBounds(parentParent);
                    }

                    //----------------------------------------------------
                    // Remove from object collection

                    auto findObject = std::find(m_AllObjects.begin(), m_AllObjects.end(), object);

                    if(findObject != m_AllObjects.end())
                    {
                        m_AllObjects.erase(findObject);
                        m_IsDirty = true;
                    }

                    // Make sure the object isn't being queued for addition to the tree
                    for(auto iter = m_NewObjects.begin(); iter != m_NewObjects.end(); ++iter)
                    {
                        if((*iter) == object)
                        {
                            m_NewObjects.erase(iter);
                            break;
                        }
                    }

                    result = true;
                }
            }

            if(!result)
            {
                // Possibility that we are being asked to remove an item that is still in the
                // new object collection (added and removed prior to a restructure call)

                for(auto iter = m_NewObjects.begin(); iter != m_NewObjects.end(); ++iter)
                {
                    if((*iter) == object)
                    {
                        result = true;
                        m_NewObjects.erase(iter);
                        break;
                    }
                }
            }

            return result;
        }

        void BVHSceneTree::removeObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto iter = objects.begin(); iter != objects.end(); ++iter)
            {
                removeObject((*iter));
            }
        }
        
        void BVHSceneTree::getAllObjects(std::vector<SceneObject*>& objects) const
        {
            objects.reserve(objects.size() + m_AllObjects.size());
            objects.insert(objects.end(), m_AllObjects.begin(), m_AllObjects.end());
        }
        
        void BVHSceneTree::getAllVisibleObjects(Math::Frustum const& frustum, std::vector<SceneObject*>& objects) const
        {
            objects.reserve(m_AllObjects.size() + m_AllObjects.size());
            findVisible(m_Root, frustum, objects);
        }

        void BVHSceneTree::getIntersections(Math::Ray const& ray, std::vector<SceneObject*>& objects) const
        {
            //------------------------------------------------------------
            // Find intersections and their distances from the origin.

            std::vector<std::pair<SceneObject*, float>> intersections;
            intersections.reserve(m_AllObjects.size());

            findIntersections(m_Root, ray, intersections);

            //------------------------------------------------------------
            // Sort the objects based on distance from origin.
            // This is done such that the object nearest the origin is first.
            
            std::sort(intersections.begin(), intersections.end(), [](std::pair<SceneObject*, float>& first, std::pair<SceneObject*, float>& second)->bool
            {
                return (first.second) < (second.second);
            });

            //------------------------------------------------------------
            // Return the sorted intersections

            objects.clear();
            objects.reserve(intersections.size());

            for(auto pair : intersections)
            {
                objects.emplace_back(pair.first);
            }
        }

        void BVHSceneTree::getIntersections(Math::BoundsSphere const& bounds, std::vector<SceneObject*>& objects) const
        {
            objects.clear();
            objects.reserve(m_AllObjects.size());

            findIntersections(m_Root, bounds, objects);
        }

        void BVHSceneTree::getIntersections(Math::BoundsAABB const& bounds, std::vector<SceneObject*>& objects) const
        {
            objects.clear();
            objects.reserve(m_AllObjects.size());

            findIntersections(m_Root, bounds, objects);
        }

        void BVHSceneTree::getIntersections(Math::BoundsOBB const& bounds, std::vector<SceneObject*>& objects) const
        {
            objects.clear();
            objects.reserve(m_AllObjects.size());

            findIntersections(m_Root, bounds, objects);
        }

        SceneTreeType BVHSceneTree::getType() const
        {
            return SceneTreeType::BoundingVolumeHierarchyCPU;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void BVHSceneTree::rebuild()
        {
            //------------------------------------------------------------
            // Destroy the tree structure but preserve the objects

            destroyNode(m_Root);
            m_Root = nullptr;

            //------------------------------------------------------------
            // Add any new objects

            const uint32_t numNewObjects = static_cast<uint32_t>(m_NewObjects.size());
            const uint32_t numTotalObjects = static_cast<uint32_t>(m_AllObjects.size()) + numNewObjects;

            if(numNewObjects > 0)
            {
                m_AllObjects.reserve(numTotalObjects);
                m_AllObjects.insert(m_AllObjects.end(), m_NewObjects.begin(), m_NewObjects.end());

                m_NewObjects.clear();

                // May want to sort objects by if they are forced visible here.
                // Could potentially speed up visibility tests on large scenes.
            }

            //------------------------------------------------------------
            // Build the new tree

            build();
        }

        void BVHSceneTree::insertNewObjects()
        {
            // There are new objects that need to be added to the tree, 
            // but not enough to require a complete rebuild.

            for(auto object : m_NewObjects) 
            {
                insertObject(object);
            }

            m_NewObjects.clear();

            fitNodeBounds(m_Root);
        }

        void BVHSceneTree::updateDirtyNodes()
        {
            /// \todo Update dirty nodes
        }

        bool BVHSceneTree::rebuildNeeded() const
        {
            bool result = false;

            if(m_IsDirty)
            {
                result = true;
            }
            else
            {
                // ...
            }

            return result;
        }

        void BVHSceneTree::destroyNode(BVHSceneNode* node) const
        {
            if(node)
            {
                destroyNode(node->left);
                destroyNode(node->right);

                delete node;
                node = nullptr;
            }
        }

        void BVHSceneTree::insertObject(SceneObject* object)
        {
            if(object)
            {
                const uint64_t morton = Math::MortonCode::calculate(object->boundsAABB.getCenter());

                BVHSceneNode* newLeafNode = new BVHSceneNode();
                newLeafNode->morton = morton;
                newLeafNode->object = object;
                newLeafNode->type   = SceneNodeType::Leaf;


                if(m_AllObjects.size() < 2)
                {
                    //----------------------------------------------------
                    // Insert into the root

                    if(m_Root == nullptr)
                    {
                        m_Root = new BVHSceneNode();
                        m_Root->type = SceneNodeType::Root;
                    }

                    newLeafNode->parent = m_Root;

                    if(m_Root->left == nullptr)
                    {
                        m_Root->left = newLeafNode;
                    }
                    else
                    {
                        if(m_Root->left->morton < morton)
                        {
                            m_Root->right = newLeafNode;
                        }
                        else
                        {
                            m_Root->right = m_Root->left;
                            m_Root->left = newLeafNode;
                        }
                    }
                }
                else
                {
                    //----------------------------------------------------
                    // Insert into an arbitrary node

                    // Get the nearest leaf node
                    BVHSceneNode* nearestLeafNode = findNearest(m_Root, morton);
                    BVHSceneNode* nearestParent = dynamic_cast<BVHSceneNode*>(nearestLeafNode->parent);

                    // Insert our new leaf into the internal parent of the one we just found.
                    // The parent will already have two children. So we will need to create
                    // a new internal node as three children can not belong to a single parent.

                    BVHSceneNode* newInternalNode = new BVHSceneNode();
                    newInternalNode->type = SceneNodeType::Internal;
                    newInternalNode->parent = nearestParent;

                    // One of the three children will remain direct descendents of the parent,
                    // the other two children will move to be descendents of the new internal.

                    // The left-most child (smallest morton code) will remain as the direct descendent (left).
                    // The other two, will move to the new internal and place in order of their morton value.

                    if(newLeafNode->morton <= nearestParent->left->morton)
                    {
                        newInternalNode->left = nearestParent->left;
                        newInternalNode->right = nearestParent->right;

                        nearestParent->left = newLeafNode;
                    }
                    else if(newLeafNode->morton <= nearestParent->right->morton)
                    {
                        newInternalNode->left = newLeafNode;
                        newInternalNode->right = nearestParent->right;
                    }
                    else
                    {
                        newInternalNode->left = nearestParent->right;
                        newInternalNode->right = newLeafNode;
                    }

                    nearestParent->right = newInternalNode;

                    // Refit the morton codes

                    newInternalNode->morton = (newInternalNode->left->morton + newInternalNode->right->morton) / 2;
                    nearestParent->morton = (nearestParent->left->morton + nearestParent->right->morton) / 2;

                    // Bounds are fit by the caller method. No need to do so here.
                }
            }
        }

        //----------------------------------------------------------------------
        // Traversal Methods
        //----------------------------------------------------------------------

        BVHSceneNode* BVHSceneTree::findParent(BVHSceneNode* node, SceneObject* object) const
        {
            BVHSceneNode* parent = nullptr;

            if(node->type == SceneNodeType::Leaf)
            {
                if(node->object == object)
                {
                    parent = node;
                }
            }
            else
            {
                parent = findParent(node->left, object);

                if(parent == nullptr)
                {
                    parent = findParent(node->right, object);
                }
            }

            return parent;
        }

        BVHSceneNode* BVHSceneTree::findNearest(BVHSceneNode* node, uint64_t const& morton) const
        {
            if(morton < node->morton)
            {
                if(node->left)
                {
                    return findNearest(node->left, morton);
                }
            }
            else if(morton > node->morton)
            {
                if(node->right)
                {
                    return findNearest(node->right, morton);
                }
            }

            return node;
        }

        void BVHSceneTree::findVisible(BVHSceneNode* node, Math::Frustum const& frustum, std::vector<SceneObject*>& objects) const
        {
            if(node)
            {
                if(frustum.contains(node->bounds))
                {
                    if((node->type == SceneNodeType::Leaf) && 
                       (node->object) &&
                       (node->object->isActive()))
                    {
                        node->object->setVisible(true);
                        objects.emplace_back(node->object);
                    }
                    else
                    {
                        findVisible(node->left, frustum, objects);
                        findVisible(node->right, frustum, objects);
                    }
                }
                else if((node->type == SceneNodeType::Leaf) && (node->object))
                {
                    node->object->setVisible(false);
                }
            }
        }

        void BVHSceneTree::findIntersections(BVHSceneNode* node, Math::Ray const& ray, std::vector<std::pair<SceneObject*, float>>& objects) const
        {
            if(node)
            {
                Math::Vector3f point;
                float distance;

                if(ray.intersects(node->bounds, point, distance))
                {
                    if((node->type == SceneNodeType::Leaf) && (node->object))
                    {
                        objects.emplace_back(std::make_pair(node->object, distance));
                    }
                    else
                    {
                        findIntersections(node->left, ray, objects);
                        findIntersections(node->right, ray, objects);
                    }
                }
            }
        }

        void BVHSceneTree::findIntersections(BVHSceneNode* node, Math::BoundsSphere const& bounds, std::vector<SceneObject*>& objects) const
        {
            if(node)
            {
                if(bounds.intersects(node->bounds))
                {
                    if((node->type == SceneNodeType::Leaf) && (node->object))
                    {
                        objects.emplace_back(node->object);
                    }
                    else
                    {
                        findIntersections(node->left, bounds, objects);
                        findIntersections(node->right, bounds, objects);
                    }
                }

                // Do nothing if there is no intersection.
            }
        }

        void BVHSceneTree::findIntersections(BVHSceneNode* node, Math::BoundsAABB const& bounds, std::vector<SceneObject*>& objects) const
        {
            if(node)
            {
                if(bounds.intersects(node->bounds))
                {
                    if(node->type == SceneNodeType::Leaf)
                    {
                        objects.emplace_back(node->object);
                    }
                    else
                    {
                        findIntersections(node->left, bounds, objects);
                        findIntersections(node->right, bounds, objects);
                    }
                }
            }
        }

        void BVHSceneTree::findIntersections(BVHSceneNode* node, Math::BoundsOBB const& bounds, std::vector<SceneObject*>& objects) const
        {
            if(node)
            {
                if(bounds.intersects(node->bounds))
                {
                    if(node->type == SceneNodeType::Leaf)
                    {
                        objects.emplace_back(node->object);
                    }
                    else
                    {
                        findIntersections(node->left, bounds, objects);
                        findIntersections(node->right, bounds, objects);
                    }
                }
            }
        }


        //----------------------------------------------------------------------
        // Build Methods
        //----------------------------------------------------------------------

        void BVHSceneTree::build()
        {
            OCULAR_PROFILE()

            // 1. Generate the morton codes for each scene object and sort them
            // 2. Recursively build the tree top-down
            // 3. Recursively fit the bounds of each node around it's children

            const uint32_t numObjects = static_cast<uint32_t>(m_AllObjects.size());

            if(numObjects > 0)
            {
                std::vector<MortonPair> mortonPairs;  
                createMortonPairs(mortonPairs);

                m_Root = generateTree(nullptr, mortonPairs, 0, (numObjects) - 1);
                m_Root->type = SceneNodeType::Root;
            }
            else
            {
                m_Root = new BVHSceneNode();
                m_Root->type = SceneNodeType::Root;
            }

            fitNodeBounds(m_Root);
        }

        void BVHSceneTree::createMortonPairs(std::vector<MortonPair>& pairs) const
        {
            OCULAR_PROFILE()

            // MortonCode::calculate(vector) performs the same essential steps as below.
            // We do not use that method as it would require allocating and filling
            // an additional vector with N points.

            //------------------------------------------------------------
            // Find the minimum and maximum component extents

            float minValue = FLT_MAX;
            float maxValue = FLT_MIN;

            for(auto const object : m_AllObjects)
            {
                const Math::Vector3f center = object->boundsAABB.getCenter();

                minValue = fminf(minValue, fminf(center.x, fminf(center.y, center.z)));
                maxValue = fmaxf(maxValue, fmaxf(center.x, fmaxf(center.y, center.z)));
            }

            //------------------------------------------------------------
            // Find the transform values needed to transform all values to the range [0,1]

            float scaleValue = 1.0f / fmaxf(Math::EPSILON_FLOAT, (maxValue - minValue));
            float offsetValue = (minValue < 0.0f) ? -minValue : 0.0f;
            
            //------------------------------------------------------------
            // Create and sort the codes

            OCULAR_PROFILE_START("Create Morton Codes")

            pairs.reserve(m_AllObjects.size());

            for(auto const object : m_AllObjects)
            {
                Math::Vector3f transformedCenter = (object->boundsAABB.getCenter() + offsetValue) * scaleValue;
                uint64_t mortonCode = Math::MortonCode::calculate(transformedCenter);

                pairs.push_back(std::make_pair(mortonCode, object));
            }

            OCULAR_PROFILE_STOP()
            OCULAR_PROFILE_START("Sort Morton Codes")

            std::sort(pairs.begin(), pairs.end(), [](MortonPair const& a, MortonPair const& b)
            {
                return (a.first < b.first);
            });
            
            OCULAR_PROFILE_STOP()

            //------------------------------------------------------------
            // Handle any duplicates

            // ...

        }

        BVHSceneNode* BVHSceneTree::generateTree(BVHSceneNode* parent, std::vector<MortonPair> const& pairs, uint32_t first, uint32_t last) const
        {
            OCULAR_PROFILE()

            BVHSceneNode* result = nullptr;

            if(first == last)
            {
                // Split contains only one item. This is a leaf node.
                result = new BVHSceneNode();
                result->parent = parent;
                result->type   = SceneNodeType::Leaf;
                result->morton = pairs[first].first;
                result->object = pairs[first].second;
            }
            else
            {
                // Multiple objects. Determine where to split the collection.
                uint32_t split = findSplit(pairs, first, last);

                // Create a new internal node and it's children.
                result = new BVHSceneNode();
                result->parent = parent;
                result->type   = SceneNodeType::Internal;

                BVHSceneNode* childA = generateTree(result, pairs, first, split);
                BVHSceneNode* childB = generateTree(result, pairs, (split + 1), last);

                result->left  = childA;
                result->right = childB;
            }

            return result;
        }

        uint32_t BVHSceneTree::findSplit(std::vector<MortonPair> const& pairs, uint32_t first, uint32_t last) const
        {
            OCULAR_PROFILE()

            uint32_t result = first;

            const uint64_t firstCode = pairs[first].first;
            const uint64_t lastCode = pairs[last].first;

            if(firstCode == lastCode)
            {
                // Identical morton codes, so split the range in the middle
                result = (first + last) >> 1;
            }
            else
            {
                // Calculate the number of highest bits are the same for all objects.

                uint32_t commonPrefix = Math::Clz((firstCode ^ lastCode));

                // Use binary search to find where the next bit differs.
                // We are looking for the highest object that shares more than
                // just the commonPrefix bits with the first one.

                uint32_t stepSize = (last - first);
                uint32_t newSplit = result;

                do
                {
                    stepSize = (stepSize + 1) >> 1;    // Exponential decrease
                    newSplit = (result + stepSize);    // Proposed new position

                    if(newSplit < last)
                    {
                        uint64_t splitCode   = pairs[newSplit].first;
                        uint32_t splitPrefix = Math::Clz((firstCode ^ splitCode));

                        if(splitPrefix > commonPrefix)
                        {
                            result = newSplit;         // Accept the new split
                        }
                    }
                } while(stepSize > 1);
            }

            return result;
        }

        void BVHSceneTree::fitNodeBounds(BVHSceneNode* node) const
        {
            OCULAR_PROFILE()

            if(node)
            {
                if(node->type == SceneNodeType::Leaf)
                {
                    node->bounds = node->object->boundsAABB;
                }
                else if(node->type == SceneNodeType::Internal)
                {
                    fitNodeBounds(node->left);
                    fitNodeBounds(node->right);

                    node->bounds = node->left->bounds;
                    node->bounds.expandToContain(node->right->bounds);
                    node->morton = Math::MortonCode::calculate(node->bounds.getCenter());
                }
                else
                {
                    // Care must be taken with the root node as it is 
                    // the only internal node that can have null children.

                    fitNodeBounds(node->left);
                    fitNodeBounds(node->right);

                    if(node->left)
                    {
                        node->bounds = node->left->bounds;

                        if(node->right)
                        {
                            node->bounds.expandToContain(node->right->bounds);
                        }
                        
                        node->morton = Math::MortonCode::calculate(node->bounds.getCenter());
                    }
                  //else
                  //{
                        // There will never be a root node with the left child
                        // null while the right child is not null.
                  //}
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}