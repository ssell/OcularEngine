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
#ifndef __H__OCULAR_CORE_SCENE_CAMERA_MANAGER__H__
#define __H__OCULAR_CORE_SCENE_CAMERA_MANAGER__H__

#include "Scene/Camera/Camera.hpp"
#include "Graphics/Shader/Uniform/UniformBuffer.hpp"
#include "Graphics/Shader/Uniform/UniformPerCamera.hpp"
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
         * \class CameraManager
         *
         * Responsible for providing quick access to all Camera instances.
         * Also handles Camera rendering and the setting of UniformBuffer values.
         */
        class CameraManager
        {
            friend class Camera;

        public:

            CameraManager();
            ~CameraManager();

            /**
             * Returns a pointer to the main camera.
             * By default, this is the camera that renders to the primary display's backbuffer.
             *
             * \return Pointer to the main camera. May return NULL if no cameras exist
             */
            Camera* getMainCamera() const;

            /**
             * Returns a pointer to the camera that is actively rendering.
             * \return Pointer to the active camera. May return NULL if no cameras exist or none are current rendering.
             */
            Camera* getActiveCamera() const;

            /**
             * Sets the main camera.
             *
             * \note As the main camera typically has the connotation of being the camera rendering to the primary
             *       window's backbuffer, care should be taken when manually setting the main camera.
             *
             * \param[in] camera/
             */
            void setMainCamera(Camera* camera);

            /**
             *
             */
            void setActiveCamera(Camera* camera);

            /**
             * \return A reference to a vector of all cameras that currently exist. This includes cameras that may
             *         not be currently active or in use.
             */
            std::vector<Camera*> const& getCameras() const;

        protected:

            /**
             * Adds a camera to the internal tracking container. This is called automatically each time 
             * that a new camera is created. If it is the only camera tracked, it will be set as the main camera.
             */
            void addCamera(Camera* camera);

            /**
             * Removes a camera from the internal tracking container. This is called automatically each time 
             * that a camera is destroyed. If the camera being removed is the main camera, then a new main
             * camera is set (by default, whichever camera no inhabits index 0 of the container). If the
             * camera is marked as the active camera, then m_ActiveCamera is set to NULL.
             */
            void removeCamera(Camera* camera);

            //------------------------------------------------------------

            std::vector<Camera*> m_Cameras;

            Camera* m_MainCamera;
            Camera* m_ActiveCamera;

            Graphics::UniformBuffer*   m_UniformBuffer;
            Graphics::UniformPerCamera m_UniformPerCamera;

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