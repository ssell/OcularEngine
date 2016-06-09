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
#ifndef __H__OCULAR_CORE_SCENE_ARENDERABLE__H__
#define __H__OCULAR_CORE_SCENE_ARENDERABLE__H__

#include "Object.hpp"
#include <string>

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
        class SceneObject;

        /**
         * \class ARenderable
         */
        class ARenderable : public Object
        {
            friend class SceneObject;

        public:

            ARenderable(std::string const& name = "ARenderable", std::string const& type = "ARenderable", SceneObject* parent = nullptr);
            virtual ~ARenderable();

            virtual bool initialize();

            /**
             * Called prior to the render method. 
             *
             * Should handle any setup required for rendering to be successful,
             * such as Material binding, etc.
             *
             * \return If return FALSE, rendering will be cancelled.
             */
            virtual bool preRender();

            /**
             * Performs any necessary rendering calls such as GraphicsDriver::renderMesh.
             */
            virtual void render();

            /**
             * Performs any post-render cleanup or state resetting.
             *
             * For example, if a particular Renderable should be drawn as lines then
             * the RenderState should be returned to triangle list or whatever else
             * the default for that application may be.
             *
             * Note that manual state changes should be kept to a minimal, and where
             * possible, they should be specified via Materials so that any active
             * renderers may best optimize and reduce the number of state changes.
             */
            virtual void postRender();

            /**
             *
             */
            virtual void updateBounds();

            //------------------------------------------------------------
            // Getters and Setters
            //------------------------------------------------------------

            /**
             * Returns the SceneObject that this Renderable belongs to.
             */
            SceneObject* getParent() const;

            /**
             * Returns the non-unique name assigned to this Renderable.
             */
            std::string const& getName() const;

            /**
             * \return The render priority of the Renderable.
             */
            virtual uint32_t getRenderPriority() const;

        protected:

            SceneObject* m_Parent;

        private:
        };
    }
}

//------------------------------------------------------------------------------------------

#endif