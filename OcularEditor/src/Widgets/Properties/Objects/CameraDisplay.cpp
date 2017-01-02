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

#include "stdafx.h"

#include "Widgets/Properties/Objects/CameraDisplay.hpp"
#include "Widgets/Properties/Types/Arithmetic/FloatProperty.hpp"
#include "Widgets/Properties/Types/MultiProperty.hpp"
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
            //------------------------------------------------------------
            // Projection ComboBox
            //------------------------------------------------------------

            m_ComboProjection = new ComboBox();
            m_ComboProjection->insertItem(0, "Perspective");
            m_ComboProjection->insertItem(1, "Orthographic");

            m_PropertyProjection = new PropertyWidget("Projection");
            m_PropertyProjection->setDisplayName("Projection");
            m_PropertyProjection->addWidgetRightSide(m_ComboProjection);

            //------------------------------------------------------------
            // Clear Color
            //------------------------------------------------------------

            m_PropertyClearColor = OcularEditor.createPropertyWidget("Clear Color", OCULAR_TYPE_NAME(Core::Color));

            //------------------------------------------------------------
            // Clipping Planes
            //------------------------------------------------------------

            m_PropertyClipping = new MultiProperty();
            
            m_PropertyClipping->setDisplayName("Clip Distance");
            m_PropertyClipping->addProperty("Min", LineType::Float);
            m_PropertyClipping->addProperty("Max", LineType::Float);

            //------------------------------------------------------------
            // Field of View
            //------------------------------------------------------------

            m_PropertyFieldOfView = new FloatProperty();

            //------------------------------------------------------------
            // Orthographic Dimensions
            //------------------------------------------------------------

            m_PropertyXSize = new MultiProperty();
            m_PropertyYSize = new MultiProperty();

            m_PropertyFieldOfView->setDisplayName("Field of View");

            m_PropertyXSize->setDisplayName("X Size");
            m_PropertyXSize->addProperty("Min", LineType::Float);
            m_PropertyXSize->addProperty("Min", LineType::Float);

            m_PropertyYSize->setDisplayName("Y Size");
            m_PropertyYSize->addProperty("Min", LineType::Float);
            m_PropertyYSize->addProperty("Min", LineType::Float);
            
            //------------------------------------------------------------
            // Layout
            //------------------------------------------------------------

            m_Layout->addWidget(m_PropertyProjection);
            m_Layout->addWidget(m_PropertyClearColor);
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
                
                m_PropertyClipping->getLineEdit(0)->setText(OcularString->toString<float>(m_Frustum.getNearClipDistance()).c_str());
                m_PropertyClipping->getLineEdit(1)->setText(OcularString->toString<float>(m_Frustum.getFarClipDistance()).c_str());
                m_PropertyFieldOfView->getLineEdit()->setText(OcularString->toString<float>(m_Frustum.getFieldOfView()).c_str());
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

            LineEdit* propClipMin = m_PropertyClipping->getLineEdit(0);
            LineEdit* propClipMax = m_PropertyClipping->getLineEdit(1);

            if(propClipMin->wasEdited())
            {
                nearClip = OcularString->fromString<float>(propClipMin->text().toStdString());
                frustumEdited = true;
            }
            else if(!propClipMin->hasFocus())
            {
                propClipMin->setText(OcularString->toString<float>(nearClip).c_str());
            }
            
            if(propClipMax->wasEdited())
            {
                farClip = OcularString->fromString<float>(propClipMax->text().toStdString());
                frustumEdited = true;
            }
            else if(!propClipMax->hasFocus())
            {
                propClipMax->setText(OcularString->toString<float>(farClip).c_str());
            }

            if(m_Camera->getProjectionType() == Core::ProjectionType::Perspective)
            {
                //--------------------------------------------------------
                // Perspective Specific Variables
                //--------------------------------------------------------

                if(m_PropertyFieldOfView->getLineEdit()->wasEdited())
                {
                    fieldOfView = OcularString->fromString<float>(m_PropertyFieldOfView->getLineEdit()->text().toStdString());
                    frustumEdited = true;
                }
                else if(!m_PropertyFieldOfView->getLineEdit()->hasFocus())
                {
                    m_PropertyFieldOfView->getLineEdit()->setText(OcularString->toString<float>(fieldOfView).c_str());
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

                LineEdit* propXMin = m_PropertyXSize->getLineEdit(0);
                LineEdit* propXMax = m_PropertyXSize->getLineEdit(1);

                LineEdit* propYMin = m_PropertyYSize->getLineEdit(0);
                LineEdit* propYMax = m_PropertyYSize->getLineEdit(1);

                //--------------------------------------------------------
                // X Size
                //--------------------------------------------------------

                if(propXMin->wasEdited())
                {
                    xMin = OcularString->fromString<float>(propXMin->text().toStdString());
                    frustumEdited = true;
                }
                else if(!propXMin->hasFocus())
                {
                    propXMin->setText(OcularString->toString<float>(xMin).c_str());
                }

                if(propXMax->wasEdited())
                {
                    xMax = OcularString->fromString<float>(propXMax->text().toStdString());
                    frustumEdited = true;
                }
                else if(!propXMax->hasFocus())
                {
                    propXMax->setText(OcularString->toString<float>(xMax).c_str());
                }

                //--------------------------------------------------------
                // Y Size
                //--------------------------------------------------------

                if(propYMin->wasEdited())
                {
                    yMin = OcularString->fromString<float>(propYMin->text().toStdString());
                    frustumEdited = true;
                }
                else if(!propYMin->hasFocus())
                {
                    propYMin->setText(OcularString->toString<float>(yMin).c_str());
                }

                if(propYMax->wasEdited())
                {
                    yMax = OcularString->fromString<float>(propYMax->text().toStdString());
                    frustumEdited = true;
                }
                else if(!propYMax->hasFocus())
                {
                    propYMax->setText(OcularString->toString<float>(yMax).c_str());
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