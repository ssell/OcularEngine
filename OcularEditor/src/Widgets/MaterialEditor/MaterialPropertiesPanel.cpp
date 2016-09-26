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

#include "Widgets/MaterialEditor/MaterialPropertiesPanel.hpp"
#include "Widgets/MaterialEditor/UniformsDisplayBox.hpp"
#include "Widgets/MaterialEditor/TexturesDisplayBox.hpp"
#include "Widgets/MaterialEditor/RenderStatesDisplayBox.hpp"

#include "Events/MaterialSelectedEvent.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MaterialPropertiesPanel::MaterialPropertiesPanel(QWidget* parent)
            : QFrame(parent),
              m_Material(nullptr)
        {
            OcularEvents->registerListener(this, Core::Priority::Low);

            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setStyleSheet("QFrame { background-color: rgb(56, 56, 60); }");

            buildBaseWidgets();
        }

        MaterialPropertiesPanel::~MaterialPropertiesPanel()
        {
            m_Material = nullptr;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void MaterialPropertiesPanel::setMaterial(std::string const& mapping)
        {
            m_MaterialMapping = mapping;
            m_Material = OcularResources->getResource<Graphics::Material>(mapping);

            if(m_Material)
            {
                updateProperties();
            }
        }
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool MaterialPropertiesPanel::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            if(event->isType<MaterialSelectedEvent>())
            {
                MaterialSelectedEvent* materialEvent = dynamic_cast<MaterialSelectedEvent*>(event.get());

                if(materialEvent)
                {
                    setMaterial(materialEvent->mappingName);
                }
            }
            
            return true;    // Do not consume this event
        }
        
        void MaterialPropertiesPanel::buildBaseWidgets()
        {
            m_LayoutMain = new QVBoxLayout();
            m_LayoutMain->setAlignment(Qt::AlignTop);

            //------------------------------------------------------------
            // Default Properties

            m_PropertyMapping = OcularEditor.createPropertyWidget("Name", Utils::TypeName<std::string>::name);
            m_PropertyFile    = OcularEditor.createPropertyWidget("File", Utils::TypeName<Core::File>::name);

            m_PropertyMapping->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            m_PropertyFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            m_LayoutMain->addWidget(m_PropertyMapping);
            m_LayoutMain->addWidget(m_PropertyFile);

            //------------------------------------------------------------

            m_PropertyBoxUniforms     = new UniformsDisplayBox();
            m_PropertyBoxTextures     = new TexturesDisplayBox();
            m_PropertyBoxRenderStates = new RenderStatesDisplayBox();

            m_LayoutMain->addWidget(m_PropertyBoxUniforms);
            m_LayoutMain->addWidget(m_PropertyBoxTextures);
            m_LayoutMain->addWidget(m_PropertyBoxRenderStates);

            //------------------------------------------------------------

            setLayout(m_LayoutMain);
        }

        void MaterialPropertiesPanel::updateProperties()
        {
            //------------------------------------------------------------
            // Update Default Properties

            const std::string mappingName = m_Material->getMappingName();
            const Core::File sourceFile = m_Material->getSourceFile();

            m_PropertyMapping->setValue(void_cast<std::string>(mappingName), 0);
            m_PropertyFile->setValue(void_cast<std::string>(sourceFile.getFullPath()), 0);

            //------------------------------------------------------------

            if(m_PropertyBoxUniforms)
            {
                m_PropertyBoxUniforms->setMaterial(m_Material);
            }

            if(m_PropertyBoxTextures)
            {
                m_PropertyBoxTextures->setMaterial(m_Material);
            }

            if(m_PropertyBoxRenderStates)
            {
                m_PropertyBoxRenderStates->setMaterial(m_Material);
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}