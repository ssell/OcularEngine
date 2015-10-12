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

#include "Graphics/Material/Material.hpp"

#include "OcularEngine.hpp"
#include "Graphics/Texture/Texture.hpp"
#include "Graphics/Shader/VertexShader.hpp"
#include "Graphics/Shader/GeometryShader.hpp"
#include "Graphics/Shader/FragmentShader.hpp"
#include "Graphics/Shader/PreTesselationShader.hpp"
#include "Graphics/Shader/PostTesselationShader.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Material::Material()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Material::bind()
        {
        
        }

        void Material::unbind()
        {
        
        }

        //--------------------------------------------
        // Texture Methods
        //--------------------------------------------

        void Material::setTexture(std::string const& identifier, std::string const& name)
        {
            Texture* texture = OcularResources->getResource<Texture>(name);

            if(texture)
            {
                // Do not accept null here as we assume they are trying to use a valid identifier.
                m_TextureMap[identifier] = texture;
            }
        }

        void Material::setTexture(std::string const& identifier, Texture* texture)
        {
            // Allow to set for null here to 'disable' the texture.
            m_TextureMap[identifier] = texture;
        }

        Texture* Material::getTexture(std::string const& identifier) const
        {
            Texture* result = nullptr;
            const auto findTexture = m_TextureMap.find(identifier);

            if(findTexture != m_TextureMap.end())
            {
                result = findTexture->second;
            }

            return result;
        }

        //--------------------------------------------
        // Shader Methods
        //--------------------------------------------

        void Material::setVertexShader(std::string const& name)
        {
            VertexShader* shader = OcularResources->getResource<VertexShader>(name);

            if(shader)
            {
                // Do not accept null here as we assume they are trying to use a valid identifier.
                m_VertexShader = shader;
            }
        }

        void Material::setVertexShader(VertexShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_VertexShader = shader;
        }

        void Material::setGeometryShader(std::string const& name)
        {
            GeometryShader* shader = OcularResources->getResource<GeometryShader>(name);

            if(shader)
            {
                // Do not accept null here as we assume they are trying to use a valid identifier.
                m_GeometryShader = shader;
            }
        }

        void Material::setGeometryShader(GeometryShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_GeometryShader = shader;
        }

        void Material::setFragmentShader(std::string const& name)
        {
            FragmentShader* shader = OcularResources->getResource<FragmentShader>(name);

            if(shader)
            {
                // Do not accept null here as we assume they are trying to use a valid identifier.
                m_FragmentShader = shader;
            }
        }

        void Material::setFragmentShader(FragmentShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_FragmentShader = shader;
        }

        void Material::setPreTesselationShader(std::string const& name)
        {
            PreTesselationShader* shader = OcularResources->getResource<PreTesselationShader>(name);

            if(shader)
            {
                // Do not accept null here as we assume they are trying to use a valid identifier.
                m_PreTesselationShader = shader;
            }
        }

        void Material::setPreTesselationShader(PreTesselationShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_PreTesselationShader = shader;
        }

        void Material::setPostTesselationShader(std::string const& name)
        {
            PostTesselationShader* shader = OcularResources->getResource<PostTesselationShader>(name);

            if(shader)
            {
                // Do not accept null here as we assume they are trying to use a valid identifier.
                m_PostTesselationShader = shader;
            }
        }

        void Material::setPostTesselationShader(PostTesselationShader* shader)
        {
            // Allow to set for null here to 'disable' the shader.
            m_PostTesselationShader = shader;
        }

        VertexShader* Material::getVertexShader() const
        {
            return m_VertexShader;
        }

        GeometryShader* Material::getGeometryShader() const
        {
            return m_GeometryShader;
        }

        FragmentShader* Material::getFragmentShader() const
        {
            return m_FragmentShader;
        }

        PreTesselationShader* Material::getPreTesselationShader() const
        {
            return m_PreTesselationShader;
        }

        PostTesselationShader* Material::getPostTesselationShader() const
        {
            return m_PostTesselationShader;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}