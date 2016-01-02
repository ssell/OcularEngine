/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#ifndef __H__OCULAR_CORE_SCENE_BVH_SCENE_TREE__H__
#define __H__OCULAR_CORE_SCENE_BVH_SCENE_TREE__H__

#include "ISceneTree.hpp"
#include "SceneObject.hpp"
#include "BVHSceneNode.hpp"

#include <vector>
#include <utility>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class BVHSceneTree
         *
         * Linear implementation of a Bounding Volume Hierarchy (BVH) Scene Tree. <br/>
         * For a parallel implementation (GPU) please see ... (does not exist yet).
         *
         * The BVH Tree is implemented as a binary tree where each leaf node contains exactly
         * one child SceneObject. This SceneObject may itself have child objects attached to
         * it of course, but each node is limited to a single object.
         *
         * Internal nodes have exactly two child nodes. In the event of an odd amount of leaf
         * nodes, the root node can have direct child leaf nodes.
         *
         * Enforcing these rules allows for the following to be expected:
         *
         *     A tree has N leaf nodes
         *     A tree has N-1 internal nodes (including root)
         *
         * Each node has a corresponding bounding box that encompasses all of it's children.
         * Thus, the bounds of a leaf node are equal to that of it's attached object. The bounds
         * of a internal node contains both of it's children. The bounds of the root then must
         * encompass all objects within the entire scene.
         *
         * The implementation of this tree is based on several sources:
         *
         *     Tero Karras, NVIDIA Research
         *     Thinking Parallel, Parts I-III
         *     http://devblogs.nvidia.com/parallelforall/thinking-parallel-part-i-collision-detection-gpu/
         *
         *     Real-Time Rendering, 3rd Edition
         *     ...
         *
         *     Daniel Kopta, et al. 
         *     Fast, Effective BVH Updates for Animated Scenes
         *     http://www.cs.utah.edu/~thiago/papers/rotations.pdf
         */
        class BVHSceneTree : public ISceneTree
        {
            typedef std::pair<uint64_t, SceneObject*> MortonPair;  ///< Pairing of morton codes and associated scene object

        public:

            BVHSceneTree();
            virtual ~BVHSceneTree();

            //------------------------------------------------------------
            // Inherited Methods
            //------------------------------------------------------------

            virtual void restructure() override;
            virtual void destroy() override;
            virtual void addObject(SceneObject* object) override;
            virtual void addObjects(std::vector<SceneObject*> const& objects) override;
            virtual bool removeObject(SceneObject* object) override;
            virtual void removeObjects(std::vector<SceneObject*> const& objects) override;
            virtual void getAllObjects(std::vector<SceneObject*>& objects) const override;
            virtual void getAllVisibleObjects(Math::Frustum const& frustum, std::vector<SceneObject*>& objects) const override;
            virtual void getIntersections(Math::Ray const& ray, std::vector<SceneObject*>& objects) const override;
            virtual void getIntersections(Math::BoundsSphere const& bounds, std::vector<SceneObject*>& objects) const override;
            virtual void getIntersections(Math::BoundsAABB const& bounds, std::vector<SceneObject*>& objects) const override;
            virtual void getIntersections(Math::BoundsOBB const& bounds, std::vector<SceneObject*>& objects) const override;

            virtual SceneTreeType getType() const override;

        protected:

            /**
             * Performs a complete rebuild of the tree.
             *
             * This is a potentially costly operation and should only be called when absolutely necessary 
             * (either on initial tree construction or when a significant number of new objects have been added).
             */
            void rebuild();

            /**
             * Individually inserts new objects into the tree.
             *
             * If the number of new objects that need to be added is significant, then a complete tree rebuild
             * will often be faster and more accurate.
             */
            void insertNewObjects();

            /**
             * Updates all dirty nodes (leafs) whose objects have either moved or rotated.
             */
            void updateDirtyNodes();

            /**
             * Checks to see if the tree needs to be rebuilt.
             */
            bool rebuildNeeded() const;

            /**
             * Safely destroys the specified node and all children.
             */
            void destroyNode(BVHSceneNode* node) const;

            /**
             * Inserts a single new object into the tree.
             * \param[in] object
             */
            void insertObject(SceneObject* object);

            //------------------------------------------------------------
            // Traversal Methods
            //------------------------------------------------------------

            /**
             * Finds the leaf node that owns the specified object in the tree.
             *
             * \param[in] node   Current node.
             * \param[in] object The object to find.
             *
             * \return The parent node.
             */
            BVHSceneNode* findParent(BVHSceneNode* node, SceneObject* object) const;

            /**
             * Finds the node with the nearest morton code to the one specified.
             * 
             * \param[in] node   Current node.
             * \param[in] morton Morton code to compare against
             *
             * \return The nearest node.
             */
            BVHSceneNode* findNearest(BVHSceneNode* node, uint64_t const& morton) const;

            /**
             * 
             * \param[in]  node    Current node.
             * \param[in]  frustum Frustum to test against.
             * \param[out] objects All discovered SceneObjects that intersect.
             */
            void findVisible(BVHSceneNode* node, Math::Frustum const& frustum, std::vector<SceneObject*>& objects) const;

            /**
             * Recursively finds all SceneObjects that intersect with the specified ray. The results are unordered.
             *
             * \param[in]  node    Current node.
             * \param[in]  ray     Ray to test against.
             * \param[out] objects All discovered SceneObjects that intersect and their intersection points.
             */
            void findIntersections(BVHSceneNode* node, Math::Ray const& ray, std::vector<std::pair<SceneObject*, float>>& objects) const;

            /**
             * Recursively finds all SceneObjects that intersect with the specified bounds.
             *
             * \param[in]  node    Current node.
             * \param[in]  bounds  Bounds to test against.
             * \param[out] objects All discovered SceneObjects that intersect.
             */
            void findIntersections(BVHSceneNode* node, Math::BoundsSphere const& bounds, std::vector<SceneObject*>& objects) const;

            /**
             * Recursively finds all SceneObjects that intersect with the specified bounds.
             *
             * \param[in]  node    Current node.
             * \param[in]  bounds  Bounds to test against.
             * \param[out] objects All discovered SceneObjects that intersect.
             */
            void findIntersections(BVHSceneNode* node, Math::BoundsAABB const& bounds, std::vector<SceneObject*>& objects) const;

            /**
             * Recursively finds all SceneObjects that intersect with the specified bounds.
             *
             * \param[in]  node    Current node.
             * \param[in]  bounds  Bounds to test against.
             * \param[out] objects All discovered SceneObjects that intersect.
             */
            void findIntersections(BVHSceneNode* node, Math::BoundsOBB const& bounds, std::vector<SceneObject*>& objects) const;

            //------------------------------------------------------------
            // Build Methods
            //------------------------------------------------------------
            
            /**
             * Builds the tree from the collection of objects stored in m_AllObjects.
             */
            void build();

            /**
             * Calculates and sorts the Morton Codes for all objects in the tree.
             * \param[out] pairs Container to be filled with the sorted Morton Codes and their associated SceneObject
             */
            void createMortonPairs(std::vector<MortonPair>& pairs) const;

            /**
             * Recursively generates the tree in a top-down manner beginning at the root.
             *
             * \param[in] parent The node calling this recursive sequence.
             * \param[in] pairs  Sorted list of morton code/scene object pairings.
             * \param[in] first  First node in the current split
             * \param[in] last   Last node in the current split (inclusive)
             *
             * \return Pointer to the root node of the newly generated tree.
             */
            BVHSceneNode* generateTree(BVHSceneNode* parent, std::vector<MortonPair> const& pairs, uint32_t first, uint32_t last) const;

            /**
             * Finds the index to split the remaining objects to fit the tree.
             *
             * \param[in] pairs Sorted list of morton code/scene object pairings.
             * \param[in] first Index of first object remaining to be added to the tree
             * \param[in] last  Index of the last object remaining to be added to the tree
             * 
             * \return Best index to split the remaining objects.
             */
            uint32_t findSplit(std::vector<MortonPair> const& pairs, uint32_t first, uint32_t last) const;

            /**
             * Adjusts the bounds of the specified node to fit over it's children.
             * \param[in] node Node to adjust the bounds of.
             */
            void fitNodeBounds(BVHSceneNode* node) const;

        private:

            bool m_IsDirty;                            ///< Dirty flag indicating if the tree needs to be updated
                              
            BVHSceneNode* m_Root;                      ///< Root scene node of the tree.
            
            std::vector<BVHSceneNode*> m_DirtyNodes;   ///< Container of all dirty nodes that need to be updated
            std::vector<SceneObject*>  m_AllObjects;   ///< Convenience container for tree reconstruction. Prevents the need of a full-traversal.
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif