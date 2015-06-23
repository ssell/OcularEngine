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
#ifndef __H__OCULAR_CORE_SCENE_ASCENE_TREE__H__
#define __H__OCULAR_CORE_SCENE_ASCENE_TREE__H__

#include "SceneNode.hpp"
#include "UUID.hpp"
#include "Math/Bounds/Ray.hpp"

#include <list>
#include <memory>

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
         * \class ISceneTree
         */
        class ISceneTree
        {
        public:

            /**
             * Periodically called (typically once per frame), this method behaves differently based on the SceneTree implementation.
             * Generally though, it will update interal nodes based on any movement and/or rotation that has happened since the last call.
             */
            virtual void restructure() = 0;
            
            virtual void destroy() = 0;

            /**
             * Adds the object to the scene tree.
             * \param[in] object
             */
            virtual void addObject(SceneObject* object) = 0;

            /**
             * Removes the object from the scene tree.
             *
             * Note that this simply removes the reference to the object and 
             * does not actually delete/deallocate the object as that should
             * be handled by the scene manager.
             *
             * \param[in] object
             */
            virtual void removeObject(SceneObject* object) = 0;

            /**
             * Returns a flat list of all objects in the scene tree.
             * No order is guaranteed for the returned objects.
             *
             * \param[out] objects List of all objects in the scene tree.
             */
            virtual void getAllObjects(std::list<SceneObject*>& objects) const = 0;

            /**
             * Returns a flat list of all visbile objects in the scene tree.
             * No order is guaranteed for the returned objects.
             *
             * \param[out] objects List of all visible objects in the scene tree.
             */
            virtual void getAllVisibleObjects(std::list<SceneObject*>& objects) const = 0;

            /**
             * Returns a flat list of all active objects in the scene tree.
             * No order is guaranteed for the returned objects.
             *
             * \param[out] objects List of all active objects in the scene tree.
             */
            virtual void getAllActiveObjects(std::list<SceneObject*>& objects) const = 0;

            /**
             * Returns a list of all scene objects that intersect with the specified ray. The objects are given in the order they are
             * encountered (the first object is the first intersected, the last object is the last intersected).
             *
             * \param[in]  ray
             * \param[out] objects List of objects intersected by the specified ray.
             */
            virtual void getIntersections(Math::Ray const& ray, std::list<SceneObject*>& objects) const = 0;

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