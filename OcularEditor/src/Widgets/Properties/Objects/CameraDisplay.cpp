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

#include "stdafx.h"

#include "Widgets/Properties/Objects/CameraDisplay.hpp"
#include "Widgets/Properties/Types/Arithmetic/FloatProperty.hpp"
#include "Widgets/Properties/Types/Vector2Property.hpp"
#include "Widgets/Properties/CustomDisplayRegistrar.hpp"
#include "Widgets/Standard/ComboBox.hpp"

#include "Scene/Camera/Camera.hpp"

OCULAR_REGISTER_CUSTOM_DISPLAY(Ocular::Editor::CameraDisplay, "Camera");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CameraDisplay::CameraDisplay(QWidget* parent)
            : PropertiesDisplayBox("Camera", parent),
              m_Camera(nullptr)
        {
            m_LabelFrustum = new QLabel("Frustum");

            //------------------------------------------------------------
            // Projection ComboBox
            //------------------------------------------------------------

            m_ComboProjection = new ComboBox();
            m_ComboProjection->insertItem(0, "Perspective");
            m_ComboProjection->insertItem(1, "Orthographic");

            m_PropertyProjection = new PropertyWidget();
            m_PropertyProjection->setDisplayName("Projection");
            m_PropertyProjection->addWidgetRightSide(m_ComboProjection);

            //------------------------------------------------------------
            // Clear Color
            //------------------------------------------------------------

            m_PropertyClearColor = OcularEditor.createPropertyWidget("Clear Color", Utils::TypeName<Core::Color>::name);

            //------------------------------------------------------------
            // Clipping Planes
            //------------------------------------------------------------

            m_PropertyClipping = new Vector2Property();
            
            m_PropertyClipping->setDisplayName("Clip Distance");
            m_PropertyClipping->m_LabelX->setText("Min");
            m_PropertyClipping->m_LabelY->setText("Max");

            //------------------------------------------------------------
            // Field of View
            //------------------------------------------------------------

            m_PropertyFieldOfView = new FloatProperty();

            //------------------------------------------------------------
            // Orthographic Dimensions
            //------------------------------------------------------------

            m_PropertyXSize = new Vector2Property();
            m_PropertyYSize = new Vector2Property();

            m_PropertyFieldOfView->setDisplayName("Field of View");

            m_PropertyXSize->setDisplayName("X Size");
            m_PropertyXSize->m_LabelX->setText("Min");
            m_PropertyXSize->m_LabelY->setText("Max");

            m_PropertyYSize->setDisplayName("Y Size");
            m_PropertyYSize->m_LabelX->setText("Min");
            m_PropertyYSize->m_LabelY->setText("Max");
            
            //------------------------------------------------------------
            // Layout
            //------------------------------------------------------------

            m_Layout->addWidget(m_PropertyProjection);
            m_Layout->addWidget(m_PropertyClearColor);
            m_Layout->addWidget(m_LabelFrustum);
            m_Layout->addWidget(m_PropertyClipping);
            m_Layout->addWidget(m_PropertyFieldOfView);
            m_Layout->addWidget(m_PropertyXSize);
            m_Layout->addWidget(m_PropertyYSize);
        }

        CameraDisplay::~CameraDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void CameraDisplay::setObject(Core::SceneObject* object)
        {
            m_Camera = dynamic_cast<Core::Camera*>(object);

            if(m_Camera)
            {

                //--------------------------------------------------------
                // Set Projection Type
                //--------------------------------------------------------

                if(m_Camera->getProjectionType() == Core::ProjectionType::Orthographic)
                {
                    m_ComboProjection->setCurrentIndex(1);
                    toggleOrthographic();
                }
                else
                {
                    m_ComboProjection->setCurrentIndex(0);
                    togglePerspective();
                }
                
                //--------------------------------------------------------
                // Set Clear Color
                //--------------------------------------------------------
                
                Core::ExposedVariable exposed;

                if(m_PropertyClearColor)
                {
                    m_Camera->getVariable("m_ClearColor", exposed);
                    m_PropertyClearColor->setVariable(exposed);
                }

                //--------------------------------------------------------
                // Set Frustum Values
                //--------------------------------------------------------

                m_Frustum = m_Camera->getFrustum();
                
                m_PropertyClipping->m_EditX->setText(OcularString->toString<float>(m_Frustum.getNearClipDistance()).c_str());
                m_PropertyClipping->m_EditY->setText(OcularString->toString<float>(m_Frustum.getFarClipDistance()).c_str());

                m_PropertyFieldOfView->setValue(m_Frustum.getFieldOfView());
            }
        }

        void CameraDisplay::updateProperties()
        {
            if(m_Camera)
            {
                updateProjection();
                updateClearColor();
                updateFrustum();
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void CameraDisplay::updateProjection()
        {
            if(m_ComboProjection->wasEdited())
            {
                if(m_Camera->getProjectionType() == Core::ProjectionType::Perspective)
                {
                    m_Camera->setProjectionOrthographic(m_Frustum.getXMin(), m_Frustum.getXMax(), m_Frustum.getYMin(), m_Frustum.getYMax(), m_Frustum.getNearClipDistance(), m_Frustum.getFarClipDistance());
                    toggleOrthographic();
                }
                else
                {
                    m_Camera->setProjectionPerspective(m_Frustum.getFieldOfView(), m_Frustum.getAspectRatio(), m_Frustum.getNearClipDistance(), m_Frustum.getFarClipDistance());
                    togglePerspective();
                }

                m_Frustum = m_Camera->getFrustum();
            }
            else if(!m_ComboProjection->hasFocus())
            {
                
            }
        }

        void CameraDisplay::updateClearColor()
        {
            if(m_PropertyClearColor)
            {
                m_PropertyClearColor->updateProperties();
            }
        }

        void CameraDisplay::updateFrustum()
        {
            float nearClip    = m_Frustum.getNearClipDistance();
            float farClip     = m_Frustum.getFarClipDistance();
            float fieldOfView = m_Frustum.getFieldOfView();
            float xMin        = m_Frustum.getXMin();
            float xMax        = m_Frustum.getXMax();
            float yMin        = m_Frustum.getYMin();
            float yMax        = m_Frustum.getYMax();

            bool frustumEdited = false;
            
            //------------------------------------------------------------
            // Clipping Distances
            //------------------------------------------------------------

            if(m_PropertyClipping->m_EditX->wasEdited())
            {
                nearClip = OcularString->fromString<float>(m_PropertyClipping->m_EditX->text().toStdString());
                frustumEdited = true;
            }
            else if(!m_PropertyClipping->m_EditX->hasFocus())
            {
                m_PropertyClipping->m_EditX->setText(OcularString->toString<float>(nearClip).c_str());
            }
            
            if(m_PropertyClipping->m_EditY->wasEdited())
            {
                farClip = OcularString->fromString<float>(m_PropertyClipping->m_EditY->text().toStdString());
                frustumEdited = true;
            }
            else if(!m_PropertyClipping->m_EditY->hasFocus())
            {
                m_PropertyClipping->m_EditY->setText(OcularString->toString<float>(farClip).c_str());
            }

            if(m_Camera->getProjectionType() == Core::ProjectionType::Perspective)
            {
                //--------------------------------------------------------
                // Perspective Specific Variables
                //--------------------------------------------------------

                if(m_PropertyFieldOfView->wasEdited())
                {
                    fieldOfView = m_PropertyFieldOfView->getValue();
                    frustumEdited = true;
                }
                else if(!m_PropertyFieldOfView->m_EditValue->hasFocus())
                {
                    m_PropertyFieldOfView->setValue(fieldOfView);
                }

                if(frustumEdited)
                {
                    m_Camera->setProjectionPerspective(fieldOfView, m_Frustum.getAspectRatio(), nearClip, farClip);
                }
            }
            else
            {
                //--------------------------------------------------------
                // Orthographic Specific Variables
                //--------------------------------------------------------

                //--------------------------------------------------------
                // X Size
                //--------------------------------------------------------

                if(m_PropertyXSize->m_EditX->wasEdited())
                {
                    xMin = OcularString->fromString<float>(m_PropertyXSize->m_EditX->text().toStdString());
                    frustumEdited = true;
                }
                else if(!m_PropertyXSize->m_EditX->hasFocus())
                {
                    m_PropertyXSize->m_EditX->setText(OcularString->toString<float>(xMin).c_str());
                }

                if(m_PropertyXSize->m_EditY->wasEdited())
                {
                    xMax = OcularString->fromString<float>(m_PropertyXSize->m_EditY->text().toStdString());
                    frustumEdited = true;
                }
                else if(!m_PropertyXSize->m_EditY->hasFocus())
                {
                    m_PropertyXSize->m_EditY->setText(OcularString->toString<float>(xMax).c_str());
                }

                //--------------------------------------------------------
                // Y Size
                //--------------------------------------------------------

                if(m_PropertyYSize->m_EditX->wasEdited())
                {
                    yMin = OcularString->fromString<float>(m_PropertyYSize->m_EditX->text().toStdString());
                    frustumEdited = true;
                }
                else if(!m_PropertyYSize->m_EditX->hasFocus())
                {
                    m_PropertyYSize->m_EditX->setText(OcularString->toString<float>(yMin).c_str());
                }

                if(m_PropertyYSize->m_EditY->wasEdited())
                {
                    yMax = OcularString->fromString<float>(m_PropertyYSize->m_EditY->text().toStdString());
                    frustumEdited = true;
                }
                else if(!m_PropertyYSize->m_EditY->hasFocus())
                {
                    m_PropertyYSize->m_EditY->setText(OcularString->toString<float>(yMax).c_str());
                }

                if(frustumEdited)
                {
                    m_Camera->setProjectionOrthographic(xMin, xMax, yMin, yMax, nearClip, farClip);
                }
            }

            m_Frustum = m_Camera->getFrustum();
        }

        void CameraDisplay::togglePerspective()
        {
            m_PropertyFieldOfView->setVisible(true);
            m_PropertyXSize->setVisible(false);
            m_PropertyYSize->setVisible(false);
        }

        void CameraDisplay::toggleOrthographic()
        {
            m_PropertyFieldOfView->setVisible(false);
            m_PropertyXSize->setVisible(true);
            m_PropertyYSize->setVisible(true);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}