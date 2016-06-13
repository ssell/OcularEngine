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
#ifndef __H__OCULAR_CORE_SCENE__H__
#define __H__OCULAR_CORE_SCENE__H__

#include "SceneTreeType.hpp"
#include "Math/Geometry/Frustum.hpp"

#include <vector>
#include <list>
#include <queue>
#include <functional>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class UniformBuffer;
    }

    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class SceneManager;
        class ISceneTree;
        class SceneObject;
        class ARoutine;
        class Renderer;

        /**
         * \class Scene
         *
         * A Scene owns the dual-SceneTrees which control all active SceneObjects. The system
         * of dual trees is used in order to separate static and dynamic objects, and to aid in
         * object caching and other performance improving techniques.
         *
         * By default, the static tree uses a (yet to be created) QuadTree implementation while 
         * the dynamic tree employs a BVH implementation.
         *
         * In addition to managing object addition, removal, and movement within the trees, the 
         * Scene is also responsible for retrieving the set of all non-culled SceneObjects and handing
         * them off to the dedicated renderer which will sort them and envoke their render methods.
         */
        class Scene
        {
            friend class SceneManager;

        public:

           virtual ~Scene();

           /**
            *
            */
           void initialize();

            /**
             * Adds the specified object to the scene's tree.
             * \param[in] object
             */
            void addObject(SceneObject* object);

            /**
             * Adds a collection of objects to the scene's tree.
             * \param[in] objects
             */
            void addObjects(std::vector<SceneObject*> const& objects);

            /**
             * Removes the specified object from the scene's tree.
             * 
             * \note This does not destroy the object itself. Only the SceneManager can/should
             *       perform object destruction.
             *
             * \param[in] object
             */
            void removeObject(SceneObject* object);

            /**
             * Removes a collection of objects from the scene's tree.
             *
             * \note This does not destroy any of the objects. Only the SceneManager can/should
             *       perform object destruction.
             *
             * \param[in] objects
             */
            void removeObjects(std::vector<SceneObject*> const& objects);

            /**
             * Removes all objects from the scene's tree.
             *
             * \note That this does not destroy any of the objects. Only the SceneManager can/should
             *       perform object destruction.
             */
            void removeAllObjects();

            /**
             * Updates the SceneTrees (calls their member restructure methods).
             */
            void update();

            /**
             * Retrieves all non-culled SceneObjects and passes them to the dedicated renderer.
             */
            void render();

            //------------------------------------------------------------------------------
            // Getters / Setters
            //------------------------------------------------------------------------------

            /**
             * Returns a collection of all SceneObjects visible to the specified view frustum (see Camera::getFrustum).
             *
             * The returned collection is a flat list meaning all visible SceneObjects are returned, not just
             * top-level parents. Thus there is no need to check child visibility, as visible children will also be
             * stored in the returned collection.
             *
             * \param[out] objects All visible SceneObjects
             * \param[in]  frustum View frustum to perform frustum-culling against
             */
            void getVisibleSceneObjects(std::vector<SceneObject*>& objects, Math::Frustum const& frustum);

            /**
             * \param[in] type
             */
            void setStaticTreeType(SceneTreeType type);

            /**
             *
             */
            SceneTreeType const& getStaticTreeType() const;

            /**
             * \param[in] type
             */
            void setDynamicTreeType(SceneTreeType type);
            
            /**
             *
             */
            SceneTreeType const& getDynamicTreeType() const;
            
            /**
             *
             */
            void setRendererType(std::string const& string);
            
            /**
             *
             */
            std::string const& getRendererType() const;

        protected:

            Scene();

            void updateTrees();

            void updateRoutines();
            void sortRoutines();

            //------------------------------------------------------------
            // Object State Change Methods

            /**
             * Alerts that the SceneObject needs to be placed in a different SceneTree.
             * This happens when the SceneObject::SetStatic() method is called.
             *
             * \param[in] object
             */
            void objectTreeChanged(SceneObject* object);

            /**
             * Alerts when the SceneObject's parent has been changed. 
             * This happens when the SceneObject::SetParent() method is called.
             *
             * \param[in] object
             * \param[in] oldParent
             */
            void objectParentChanged(SceneObject* object, SceneObject* oldParent);

            /**
             * Alerts when a new routine has been created and added to a SceneObject.
             * \param[in] routine
             */
            void routineAdded(ARoutine* routine);

            /**
             * Alerts when a routine is being destroyed and removed from a SceneObject.
             * \param[in] routine
             */
            void routineRemoved(ARoutine* routine);

        private:

            bool verifySceneTrees() const;

            //------------------------------------------------------------------------------

            Renderer* m_Renderer;
            std::string m_RendererType;

            Graphics::UniformBuffer* m_UniformBufferPerFrame;
            Graphics::UniformBuffer* m_UniformBufferPerObject;

            SceneTreeType m_StaticTreeType;
            SceneTreeType m_DynamicTreeType;

            ISceneTree* m_StaticSceneTree;
            ISceneTree* m_DynamicSceneTree;

            std::vector<ARoutine*> m_Routines;
            bool m_RoutinesAreDirty;

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