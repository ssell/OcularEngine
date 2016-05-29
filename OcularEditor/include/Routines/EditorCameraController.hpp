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
#ifndef __H__OCULAR_EDITOR_ROUTINE_EDITOR_CAMERA_CONTROLLER__H__
#define __H__OCULAR_EDITOR_ROUTINE_EDITOR_CAMERA_CONTROLLER__H__

#include "Scene/ARoutine.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class MouseScrollInputEvent;
    }

    /**
     * \addtogroup Core
     * @{
     */
    namespace Editor
    {
        class SceneObjectFocusedEvent;

        /**
         * \class EditorCameraController
         *
         * Supports a variety of camera controls:
         *
         *     - Looking around via right-mouse button + mouse movement
         *     - Panning via middle-mouse button + mouse movement
         *     - Orbiting via alt + left-mouse button + mouse movement
         *     - Zooming via scroll wheel
         *     - Focusing via SceneObjectFocusedEvent
         */
        class EditorCameraController : public Core::ARoutine
        {
        public:

            EditorCameraController();
            virtual ~EditorCameraController();

            //------------------------------------------------------------
            // Inherited Methods
            //------------------------------------------------------------

            virtual void onUpdate(float const delta) override;
            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;

            //------------------------------------------------------------
            // Controller Specific Methods
            //------------------------------------------------------------
            
            void setLookSensitivity(float sensitivity);
            float getLookSensitivity() const;

            void setPanSensitivity(float sensitivity);
            float getPanSensitivity() const;

            void setZoomSensitivity(float sensitivity);
            float getZoomSensitivity() const;

        protected:

            void updateFocusMove(float const delta);
            void updateCameraMode();

            void handleEventMouseScroll(Core::MouseScrollInputEvent* event);
            void handleEventObjectFocused(SceneObjectFocusedEvent* event);

            void handleMouseMovement();
            void handleMousePan();
            void handleMouseDrag();
            void handleMouseLook();
            void handleMouseOrbit();

        private:

            int8_t m_Mode;

            float m_PanSensitivity;
            float m_ZoomSensitivity;
            float m_LookSensitivity;
            float m_OrbitSensitivity;

            Math::Vector2i m_LastMousePos;
            Math::Vector3f m_DeltaVector;
            Math::Vector3f m_LookEuler;

            //------------------------------------------------------------
            // Focus Update Variables

            bool m_IsMovingFocus;              ///< If true, we are in the process of moving the camera for a focus event
            float m_FocusElapsed;              ///< The amount of time left to finish moving the camera for a focus event

            Math::Vector3f m_FocusStartPos;    ///< The position that the focus move started at
            Math::Vector3f m_FocusEndPos;      ///< The position that the focus move will end at

            float m_OrbitDistance;             ///< Distance to orbit the camera 
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