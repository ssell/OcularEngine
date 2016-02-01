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
    /**
     * \addtogroup Core
     * @{
     */
    namespace Editor
    {
        /**
         * \class EditorCameraController
         *
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

            void updateCameraMode();

            void handleMouseMovement();
            void handleMousePan();
            void handleMouseDrag();
            void handleMouseLook();

        private:

            int8_t m_Mode;

            float m_PanSensitivity;
            float m_ZoomSensitivity;
            float m_LookSensitivity;

            Math::Vector2i m_LastMousePos;
            Math::Vector3f m_DeltaVector;
            Math::Vector3f m_LookEuler;
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