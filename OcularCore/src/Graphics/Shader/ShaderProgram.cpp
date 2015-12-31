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

#include "Graphics/Shader/ShaderProgram.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ShaderProgram::ShaderProgram()
            : Resource(),
              m_VertexShader(nullptr),
              m_GeometryShader(nullptr),
              m_FragmentShader(nullptr),
              m_PreTessellationShader(nullptr),
              m_PostTessellationShader(nullptr)
        {
            
        }

        ShaderProgram::~ShaderProgram()
        {
            unload();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ShaderProgram::unload()
        {
            if(m_VertexShader)
            {
                m_VertexShader->unload();
            }
            
            if(m_GeometryShader)
            {
                m_GeometryShader->unload();
            }
            
            if(m_FragmentShader)
            {
                m_FragmentShader->unload();
            }
            
            if(m_PreTessellationShader)
            {
                m_PreTessellationShader->unload();
            }
            
            if(m_PostTessellationShader)
            {
                m_PostTessellationShader->unload();
            }
        }

        void ShaderProgram::setVertexShader(VertexShader* shader)
        {
            m_VertexShader = shader;
            m_VertexShader->m_Parent = this;
        }

        VertexShader* ShaderProgram::getVertexShader()
        {
            return m_VertexShader;
        }

        void ShaderProgram::setGeometryShader(GeometryShader* shader)
        {
            m_GeometryShader = shader;
            m_GeometryShader->m_Parent = this;
        }

        GeometryShader* ShaderProgram::getGeometryShader()
        {
            return m_GeometryShader;
        }

        void ShaderProgram::setFragmentShader(FragmentShader* shader)
        {
            m_FragmentShader = shader;
            m_FragmentShader->m_Parent = this;
        }

        FragmentShader* ShaderProgram::getFragmentShader()
        {
            return m_FragmentShader;
        }

        void ShaderProgram::setPixelShader(PixelShader* shader)
        {
            m_FragmentShader = shader;
            m_FragmentShader->m_Parent = this;
        }

        PixelShader* ShaderProgram::getPixelShader()
        {
            return m_FragmentShader;
        }

        void ShaderProgram::setPreTessellationShader(PreTessellationShader* shader)
        {
            m_PreTessellationShader = shader;
            m_PreTessellationShader->m_Parent = this;
        }

        PreTessellationShader* ShaderProgram::getPreTessellationShader()
        {
            return m_PreTessellationShader;
        }

        void ShaderProgram::setHullShader(HullShader* shader)
        {
            m_PreTessellationShader = shader;
            m_PreTessellationShader->m_Parent = this;
        }

        HullShader* ShaderProgram::getHullShader()
        {
            return m_PreTessellationShader;
        }

        void ShaderProgram::setPostTessellationShader(PostTessellationShader* shader)
        {
            m_PostTessellationShader = shader;
            m_PostTessellationShader->m_Parent = this;
        }

        PostTessellationShader* ShaderProgram::getPostTessellationShader()
        {
            return m_PostTessellationShader;
        }

        void ShaderProgram::setDomainShader(DomainShader* shader)
        {
            m_PostTessellationShader = shader;
            m_PostTessellationShader->m_Parent = this;
        }

        DomainShader* ShaderProgram::getDomainShader()
        {
            return m_PostTessellationShader;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}