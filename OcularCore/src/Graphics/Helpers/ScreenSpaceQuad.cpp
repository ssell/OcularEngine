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

#include "OcularEngine.hpp"

#include "Graphics/Helpers/ScreenSpaceQuad.hpp"
#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Material/Material.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // Constructors
        //----------------------------------------------------------------------------------
        
        ScreenSpaceQuad::ScreenSpaceQuad()
            : m_Material{ nullptr },
              m_VertexBuffer{ nullptr }
        {

        }

        ScreenSpaceQuad::~ScreenSpaceQuad()
        {

        }

        //----------------------------------------------------------------------------------
        // Public Methods
        //----------------------------------------------------------------------------------

        bool ScreenSpaceQuad::initialize()
        {
            bool result = false;

            m_VertexBuffer.reset(OcularGraphics->createVertexBuffer());    // Create empty vertex buffer
            m_Material.reset(OcularGraphics->createMaterial());

            if(m_Material)
            {
                auto shaders = OcularResources->getResource<ShaderProgram>("OcularCore/Shaders/ScreenSpaceQuad");

                if(shaders)
                {
                    m_Material->setVertexShader(shaders->getVertexShader());
                    m_Material->setGeometryShader(shaders->getGeometryShader());
                    m_Material->setFragmentShader(shaders->getFragmentShader());

                    result = true;
                }
            }

            return result;
        }

        void ScreenSpaceQuad::render()
        {
            if(m_Material && m_VertexBuffer)
            {
                m_Material->bind();
                m_VertexBuffer->bind();

                // Draw a single vertex. 
                // This vertex is turned into a screen-space quad (two triangles) in the geometry shader.

                OcularGraphics->render(1, 0);
            }
        }

        void ScreenSpaceQuad::setTexture(uint32_t const index, std::string const& name, Texture* texture)
        {
            if(m_Material)
            {
                m_Material->setTexture(index, name, texture);
            }
        }
        
        //----------------------------------------------------------------------------------
        // Protected Methods
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // Private Methods
        //----------------------------------------------------------------------------------
    }
}