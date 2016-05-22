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
#include "Widgets/Properties/Renderables/MeshRenderableDisplayMaterial.hpp"
#include "Widgets/Standard/LineEdit.hpp"
#include "Widgets/Standard/ButtonResourceBrowse.hpp"

#include "Graphics/Material/Material.hpp"
#include "Utilities/StringComposer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MeshRenderableDisplayMaterial::MeshRenderableDisplayMaterial(uint32_t index, QWidget* parent)
            : QFrame(parent),
              m_Material(nullptr),
              m_MaterialIndex(index)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setStyleSheet("QFrame { background-color: rgb(56, 56, 60); }");

            createLeftSide();
            createRightSide();
            createLayout();
        }

        MeshRenderableDisplayMaterial::~MeshRenderableDisplayMaterial()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize MeshRenderableDisplayMaterial::sizeHint() const
        {
            return QSize(275, 5);
        }

        void MeshRenderableDisplayMaterial::setMaterial(Graphics::Material* material)
        {
            m_Material = material;

            if(m_Material)
            {
                
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MeshRenderableDisplayMaterial::createLeftSide()
        {
            m_LabelName = new QLabel();
            m_LabelName->setText(OCULAR_STRING_COMPOSER("Material ", m_MaterialIndex).c_str());
            
            m_LayoutLeft = new QHBoxLayout();
            m_LayoutLeft->addWidget(m_LabelName);
            
            m_FrameLeftSide = new QFrame();
            m_FrameLeftSide->setLayout(m_LayoutLeft);
            m_FrameLeftSide->setFixedWidth(100);
        }

        void MeshRenderableDisplayMaterial::createRightSide()
        {
            m_LayoutRight = new QHBoxLayout();
            m_FrameRightSide = new QFrame();
            m_FrameRightSide->setLayout(m_LayoutRight);

            m_LineValue = new LineEdit(LineType::String);
            m_ButtonBrowse = new ButtonResourceBrowse();

            m_LayoutRight->addWidget(m_LineValue);
            m_LayoutRight->addWidget(m_ButtonBrowse);
        }

        void MeshRenderableDisplayMaterial::createLayout()
        {
            m_Layout = new QHBoxLayout();
            m_Layout->setContentsMargins(5, 0, 5, 0);
            m_Layout->addWidget(m_FrameLeftSide);
            m_Layout->addWidget(m_FrameRightSide);

            setLayout(m_Layout);
        }
    }
}