/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_CORE_SCENE_BVH_SCENE_NODE__H__
#define __H__OCULAR_CORE_SCENE_BVH_SCENE_NODE__H__

#include "SceneNode.hpp"
#include "Math/Bounds/BoundsAABB.hpp"

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
         * \class BVHSceneNode
         *
         * Implementation of a node of a Bounding Volume Hierarchy Tree. 
         * See the BVHSceneTree for more information.
         */
        class BVHSceneNode : public SceneNode
        {
        public:

            BVHSceneNode();
            virtual ~BVHSceneNode();

            virtual void attachObject(SceneObject* object) override;

            //------------------------------------------------------------
            // Public Variables

            Math::BoundsAABB bounds;         ///< Bounds of this BVH node that encompass all children.
            uint64_t morton;                 ///< The morton index value for this node.

            BVHSceneNode* left;              ///< The 'left' child node (null if this is a leaf).
            BVHSceneNode* right;             ///< The 'right' child node (null if this is a leaf).

            SceneObject* object;             ///< The object attached to this node (null unless this is a leaf).

        protected:

        private:

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