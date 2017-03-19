/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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
#include "SceneTreeType.hpp"
#include "UUID.hpp"

#include "Math/Bounds/Ray.hpp"
#include "Math/Bounds/BoundsSphere.hpp"
#include "Math/Bounds/BoundsAABB.hpp"
#include "Math/Bounds/BoundsOBB.hpp"
#include "Math/Geometry/Frustum.hpp"

#include <vector>
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
            
            /**
             * Destroys the SceneTree and all nodes contained within. Does not destroy any SceneObjects.
             */
            virtual void destroy() = 0;

            /**
             * \param[in] checkNewObjects The container containing new objects not yet formally
             *                            added to the tree will be checked as well.
             *
             * \return TRUE if the SceneObject is found in the SceneTree
             */
            virtual bool containsObject(SceneObject* object, bool checkNewObjects) const = 0;

            /**
             * Adds the object to the scene tree.
             *
             * \note The object will not be instantly added to the tree proper. Instead, they will be added next time
             *       the restructure method is invoked. The restructure method is automatically called by the
             *       engine periodically. If one needs the object to be immediately available in the tree, then
             *       they must manually call the restructure method themselves.
             *
             * \param[in] object
             */
            virtual void addObject(SceneObject* object) = 0;

            /**
             * Adds a collection of objects to the scene tree.
             *
             * \note The objects will not be instantly added to the tree proper. Instead, they will be added next time
             *       the restructure method is invoked. The restructure method is automatically called by the
             *       engine periodically. If one needs the object to be immediately available in the tree, then
             *       they must manually call the restructure method themselves.
             *
             * \param[in] objects
             */
            virtual void addObjects(std::vector<SceneObject*> const& objects) = 0;

            /**
             * Removes the object from the scene tree.
             *
             * Note that this simply removes the reference to the object and 
             * does not actually delete/deallocate the object as that should
             * be handled by the scene manager.
             *
             * \param[in] object
             */
            virtual bool removeObject(SceneObject* object) = 0;

            /**
             * Removes all objects from the scene tree.
             *
             * Note that this simply removes the reference to the object and 
             * does not actually delete/deallocate the object as that should
             * be handled by the scene manager.
             *
             * \param[in] object
             */
            virtual void removeObjects(std::vector<SceneObject*> const& objects) = 0;

            /**
             * Returns a flat list of all objects in the scene tree.
             * No order is guaranteed for the returned objects.
             *
             * \param[out] objects List of all objects in the scene tree.
             */
            virtual void getAllObjects(std::vector<SceneObject*>& objects) const = 0;

            /**
             * Returns a flat list of all visbile objects in the scene tree.
             * No order is guaranteed for the returned objects.
             *
             * \param[in]  frustum Viewing frustum to check visibility against.
             * \param[out] objects List of all visible objects in the scene tree.
             */
            virtual void getAllVisibleObjects(Math::Frustum const& frustum, std::vector<SceneObject*>& objects) const = 0;

            /**
             * Returns a list of all scene objects that intersect with the specified ray. 
             * The objects are given in the order they are encountered along the ray.
             *
             * For example, if a ray is created with the origin at the camera and extends along
             * the view direction, then objects[0] will be the object closest to the camera and
             * objects[size-1] will be the object farthest away from the camera.
             *
             * \param[in]  ray
             * \param[out] objects List of objects intersected by the specified ray.
             */
            virtual void getIntersections(Math::Ray const& ray, std::vector<std::pair<SceneObject*, float>>& objects) const = 0;

            /**
             * Returns a list of all scene objects that intersect with the sphere.
             * An intersection occurs if a SceneObject either partially intersects or is entirely contained within the bounds.
             *
             * \param[in]  bounds
             * \param[out] objects List of objects intersected by the specified bounds.
             */
            virtual void getIntersections(Math::BoundsSphere const& bounds, std::vector<SceneObject*>& objects) const = 0;

            /**
             * Returns a list of all scene objects that intersect with the specified AABB.
             * An intersection occurs if a SceneObject either partially intersects or is entirely contained within the bounds.
             *
             * \param[in]  bounds
             * \param[out] objects List of objects intersected by the specified bounds.
             */
            virtual void getIntersections(Math::BoundsAABB const& bounds, std::vector<SceneObject*>& objects) const = 0;

            /**
             * Returns a list of all scene objects that intersect with the specified OBB.
             * An intersection occurs if a SceneObject either partially intersects or is entirely contained within the bounds.
             *
             * \param[in]  bounds
             * \param[out] objects List of objects intersected by the specified bounds.
             */
            virtual void getIntersections(Math::BoundsOBB const& bounds, std::vector<SceneObject*>& objects) const = 0;

            /**
             * Returns the type of SceneTree this implementation is.
             */
            virtual SceneTreeType getType() const = 0;

            /**
             * Indicates that the tree is dirty, and that the object with the given UUID was explicitly changed.
             */
            virtual void setDirty(UUID const& uuid) = 0;

        protected:

            std::vector<SceneObject*> m_NewObjects;    ///< Newly added objects that are waiting to be added to the tree.

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