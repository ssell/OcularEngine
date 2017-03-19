/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Widgets/MaterialEditor/ShadersDisplayBox.hpp"
#include "Widgets/Properties/Types/ResourceProperty.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ShadersDisplayBox::ShadersDisplayBox(QWidget* parent)
            : MaterialPropertiesDisplayBox("Shaders", parent)
        {
            buildWidgets();
        }

        ShadersDisplayBox::~ShadersDisplayBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ShadersDisplayBox::setMaterial(Graphics::Material* material)
        {
            MaterialPropertiesDisplayBox::setMaterial(material);

            if(material)
            {
                auto vertex   = material->getVertexShader();
                auto geometry = material->getGeometryShader();
                auto fragment = material->getFragmentShader();
                auto preTess  = material->getPreTessellationShader();
                auto postTess = material->getPostTessellationShader();

                if(vertex)
                {
                    m_PropertyVertexShader->setValue(void_cast<std::string>(vertex->getMappingName()), 0);
                }
                
                if(geometry)
                {
                    m_PropertyGeometryShader->setValue(void_cast<std::string>(geometry->getMappingName()), 0);
                }
                
                if(fragment)
                {
                    m_PropertyFragmentShader->setValue(void_cast<std::string>(fragment->getMappingName()), 0);
                }
                
                if(preTess)
                {
                    m_PropertyPreTessShader->setValue(void_cast<std::string>(preTess->getMappingName()), 0);
                }
                
                if(postTess)
                {
                    m_PropertyPostTessShader->setValue(void_cast<std::string>(postTess->getMappingName()), 0);
                }
            }
        }

        void ShadersDisplayBox::updateProperties()
        {

        }

        void ShadersDisplayBox::onApply()
        {
            if(m_Material)
            {
                const std::string vertex   = m_PropertyVertexShader->getValue();
                const std::string geometry = m_PropertyGeometryShader->getValue();
                const std::string fragment = m_PropertyFragmentShader->getValue();
                const std::string preTess  = m_PropertyPreTessShader->getValue();
                const std::string postTess = m_PropertyPostTessShader->getValue();

                //--------------------------------------------------------
                // Vertex
                //--------------------------------------------------------

                if(vertex.size())
                {
                    if(m_PropertyVertexShader->validateResource())
                    {
                        m_Material->setVertexShader(vertex);
                    }
                }
                else
                {
                    m_Material->setVertexShader(nullptr);
                }

                //--------------------------------------------------------
                // Geometry
                //--------------------------------------------------------

                if(geometry.size())
                {
                    if(m_PropertyGeometryShader->validateResource())
                    {
                        m_Material->setGeometryShader(geometry);
                    }
                }
                else
                {
                    m_Material->setGeometryShader(nullptr);
                }

                //--------------------------------------------------------
                // Fragment
                //--------------------------------------------------------

                if(fragment.size())
                {
                    if(m_PropertyFragmentShader->validateResource())
                    {
                        m_Material->setFragmentShader(fragment);
                    }
                }
                else
                {
                    m_Material->setFragmentShader(nullptr);
                }

                //--------------------------------------------------------
                // Pre Tessellation
                //--------------------------------------------------------

                if(preTess.size())
                {
                    if(m_PropertyPreTessShader->validateResource())
                    {
                        m_Material->setPreTessellationShader(preTess);
                    }
                }
                else
                {
                    m_Material->setPreTessellationShader(nullptr);
                }

                //--------------------------------------------------------
                // Post Tessellation
                //--------------------------------------------------------

                if(postTess.size())
                {
                    if(m_PropertyPostTessShader->validateResource())
                    {
                        m_Material->setPostTessellationShader(postTess);
                    }
                }
                else
                {
                    m_Material->setPostTessellationShader(nullptr);
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ShadersDisplayBox::buildWidgets()
        {
            m_PropertyVertexShader = new ResourceProperty();
            m_PropertyVertexShader->setDisplayName("Vertex");
            m_PropertyVertexShader->setResourceType(Core::ResourceType::ShaderProgram);
            m_Layout->addWidget(m_PropertyVertexShader);

            m_PropertyGeometryShader = new ResourceProperty();
            m_PropertyGeometryShader->setDisplayName("Geometry");
            m_PropertyGeometryShader->setResourceType(Core::ResourceType::ShaderProgram);
            m_Layout->addWidget(m_PropertyGeometryShader);

            m_PropertyFragmentShader = new ResourceProperty();
            m_PropertyFragmentShader->setDisplayName("Fragment");
            m_PropertyFragmentShader->setResourceType(Core::ResourceType::ShaderProgram);
            m_Layout->addWidget(m_PropertyFragmentShader);

            m_PropertyPreTessShader = new ResourceProperty();
            m_PropertyPreTessShader->setDisplayName("PreTessellation");
            m_PropertyPreTessShader->setResourceType(Core::ResourceType::ShaderProgram);
            m_Layout->addWidget(m_PropertyPreTessShader);

            m_PropertyPostTessShader = new ResourceProperty();
            m_PropertyPostTessShader->setDisplayName("PostTessellation");
            m_PropertyPostTessShader->setResourceType(Core::ResourceType::ShaderProgram);
            m_Layout->addWidget(m_PropertyPostTessShader);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}