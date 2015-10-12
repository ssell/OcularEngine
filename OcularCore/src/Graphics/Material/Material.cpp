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

        void Material::setMainTexture(std::string const& name)
        {
        
        }

        void Material::setMainTexture(Texture* texture)
        {
        
        }

        void Material::setTexture(std::string const& identifier, std::string const& name)
        {
        
        }

        void Material::setTexture(std::string const& identifier, Texture* texture)
        {
        
        }

        Texture* Material::getMainTexture() const
        {
            return nullptr;
        }

        Texture* Material::getTexture(std::string const& identifier) const
        {
            return nullptr;
        }

        //--------------------------------------------
        // Shader Methods
        //--------------------------------------------

        void Material::setVertexShader(std::string const& name)
        {
        
        }

        void Material::setVertexShader(VertexShader* shader)
        {
            m_VertexShader = shader;
        }

        void Material::setGeometryShader(std::string const& name)
        {
        
        }

        void Material::setGeometryShader(GeometryShader* shader)
        {
            m_GeometryShader = shader;
        }

        void Material::setFragmentShader(std::string const& name)
        {
        
        }

        void Material::setFragmentShader(FragmentShader* shader)
        {
            m_FragmentShader = shader;
        }

        void Material::setPreTesselationShader(std::string const& name)
        {
        
        }

        void Material::setPreTesselationShader(PreTesselationShader* shader)
        {
            m_PreTesselationShader = shader;
        }

        void Material::setPostTesselationShader(std::string const& name)
        {
        
        }

        void Material::setPostTesselationShader(PostTesselationShader* shader)
        {
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