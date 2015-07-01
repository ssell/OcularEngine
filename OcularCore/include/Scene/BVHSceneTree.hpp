/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
         * Implementation of a Bounding Volume Hierarchy (BVH) Scene Tree.
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
         *     A tree has a single root node
         *     A tree has N leaf nodes
         *     A tree has N-1 internal nodes
         *     A tree has a total of 2N nodes
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
         *     http://devblogs.nvidia.com/parallelforall/thinking-parallel-part-ii-tree-traversal-gpu/
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
            virtual void removeObject(SceneObject* object) override;
            virtual void getAllObjects(std::vector<SceneObject*>& objects) const override;
            virtual void getAllVisibleObjects(std::vector<SceneObject*>& objects) const override;
            virtual void getAllActiveObjects(std::vector<SceneObject*>& objects) const override;
            virtual void getIntersections(Math::Ray const& ray, std::vector<SceneObject*>& objects) const override;

        protected:

            /**
             * Checks to see if the tree needs to be rebuilt.
             */
            bool rebuildNeeded() const;

            /**
             * Safely destroys the specified node and all children.
             */
            void destroyNode(BVHSceneNode* node) const;

            //------------------------------------------------------------
            // Build methods
            //------------------------------------------------------------
            
            /**
             * Builds the tree from the collection of objects stored in m_AllObjects.
             */
            void build();

            /**
             * Calculates and sorts the Morton Codes for all objects in the tree.
             * \param[out] codes Container to be filled with the sorted Morton Codes.
             */
            void createMortonCodes(std::vector<uint64_t>& codes) const;

            BVHSceneNode* createRootNode() const;
            BVHSceneNode* createInternalNode(BVHSceneNode* parent) const;
            BVHSceneNode* createLeafNode(BVHSceneNode* parent) const;

        private:

            BVHSceneNode* m_Root;                     ///< Root scene node of the tree.
            std::vector<SceneObject*> m_AllObjects;   ///< Convenience container for tree reconstruction. Prevents the need of a full-traversal.
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