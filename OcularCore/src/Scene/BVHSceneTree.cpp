/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
            if(rebuildNeeded())
            {
                //--------------------------------------------------------------------
                // Destroy the tree structure but preserve the objects

                destroyNode(m_Root);
                m_Root = nullptr;

                //--------------------------------------------------------------------
                // Add any new objects

                uint32_t numNewObjects = m_NewObjects.size();
                uint32_t numTotalObjects = m_AllObjects.size() + numNewObjects;

                if(numNewObjects > 0)
                {
                    m_AllObjects.reserve(numTotalObjects);
                    m_AllObjects.insert(m_AllObjects.end(), m_NewObjects.begin(), m_NewObjects.end());

                    m_NewObjects.clear();
                }

                //--------------------------------------------------------------------
                // Build the new tree

                build();
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
            }
        }

        void BVHSceneTree::addObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto object : objects)
            {
                if(object)
                {
                    m_NewObjects.emplace_back(object);
                }
            }
        }
        
        void BVHSceneTree::removeObject(SceneObject* object)
        {
        
        }
        
        void BVHSceneTree::getAllObjects(std::vector<SceneObject*>& objects) const
        {
        
        }
        
        void BVHSceneTree::getAllVisibleObjects(std::vector<SceneObject*>& objects) const
        {
        
        }

        void BVHSceneTree::getAllActiveObjects(std::vector<SceneObject*>& objects) const
        {
        
        }

        void BVHSceneTree::getIntersections(Math::Ray const& ray, std::vector<SceneObject*>& objects) const
        {
        
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool BVHSceneTree::rebuildNeeded() const
        {
            bool result = false;

            if(m_NewObjects.size() > 0)
            {
                result = true;
            }
            else
            {
                
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

        //----------------------------------------------------------------------
        // Build Methods
        //----------------------------------------------------------------------

        void BVHSceneTree::build()
        {
            uint32_t numObjects = m_AllObjects.size();

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
        }

        void BVHSceneTree::createMortonPairs(std::vector<MortonPair>& pairs) const
        {
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

            pairs.reserve(m_AllObjects.size());

            for(auto const object : m_AllObjects)
            {
                Math::Vector3f transformedCenter = (object->boundsAABB.getCenter() + offsetValue) * scaleValue;
                uint64_t mortonCode = Math::MortonCode::calculate(transformedCenter);

                pairs.push_back(std::make_pair(mortonCode, object));
            }

            std::sort(pairs.begin(), pairs.end(), [](MortonPair const& a, MortonPair const& b)
            {
                return (a.first < b.first);
            });

            //------------------------------------------------------------
            // Handle any duplicates

            // ...
        }

        BVHSceneNode* BVHSceneTree::generateTree(BVHSceneNode* parent, std::vector<MortonPair> const& pairs, uint32_t first, uint32_t last) const
        {
            BVHSceneNode* result = nullptr;

            if(first == last)
            {
                // Split contains only one item. This is a leaf node.
                result = new BVHSceneNode();
                result->parent = parent;
                result->type   = SceneNodeType::Leaf;
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

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}