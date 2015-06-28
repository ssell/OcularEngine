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
         */
        class BVHSceneTree : public ISceneTree
        {
        public:

            BVHSceneTree();
            virtual ~BVHSceneTree();

            //------------------------------------------------------------
            // Inherited Methods

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