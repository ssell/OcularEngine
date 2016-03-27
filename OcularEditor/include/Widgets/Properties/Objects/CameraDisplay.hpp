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
#ifndef __H__OCULAR_EDITOR_CAMERA_DISPLAY__H__
#define __H__OCULAR_EDITOR_CAMERA_DISPLAY__H__

#include "Widgets/Properties/PropertiesDisplayBox.hpp"
#include "Widgets/Properties/Types/ColorProperty.hpp"
#include "Widgets/Standard/LineEdit.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class Camera;
    }

    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        class ComboBox;
        class FloatProperty;
        class MultiProperty;

        /**
         * \class CameraDisplay
         *
         * Custom properties display widget specifically for Camera object instances.
         */
        class CameraDisplay : public PropertiesDisplayBox
        {
        public:

            CameraDisplay(QWidget* parent = nullptr);
            ~CameraDisplay();

            //------------------------------------------------------------

            virtual void setObject(Core::SceneObject* object) override;
            virtual void updateProperties() override;

        protected:

            void updateProjection();
            void updateClearColor();
            void updateFrustum();

            void togglePerspective();
            void toggleOrthographic();

        private:

            Core::Camera* m_Camera;
            Math::Frustum m_Frustum;

            //------------------------------------------------------------
            // General Properties
            
            ComboBox* m_ComboProjection;

            PropertyWidget* m_PropertyProjection;
            PropertyWidget* m_PropertyClearColor;

            //------------------------------------------------------------
            // Frustum Properties
            
            MultiProperty* m_PropertyClipping;
            MultiProperty* m_PropertyXSize;
            MultiProperty* m_PropertyYSize;
            FloatProperty* m_PropertyFieldOfView;
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