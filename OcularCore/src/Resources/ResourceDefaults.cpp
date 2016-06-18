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

#include "Resources/ResourceDefaults.hpp"

#include "Graphics/Texture/Texture2D.hpp"
#include "Graphics/Shader/Shader.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"

#include "Graphics/Mesh/MeshEmpty.hpp"
#include "Graphics/Mesh/MeshMissing.hpp"

#include "Graphics/Material/MaterialEmpty.hpp"
#include "Graphics/Material/MaterialMissing.hpp"

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ResourceDefaults::ResourceDefaults()
            : m_TextureEmpty(nullptr),
              m_TextureMissing(nullptr),
              m_MeshEmpty(nullptr),
              m_MeshMissing(nullptr),
              m_MaterialEmpty(nullptr),
              m_MaterialMissing(nullptr),
              m_ShaderEmpty(nullptr),
              m_ShaderMissing(nullptr),
              m_ShaderProgramEmpty(nullptr),
              m_ShaderProgramMissing(nullptr),
              m_DataEmpty(nullptr),
              m_DataMissing(nullptr)
        {

        }

        ResourceDefaults::~ResourceDefaults()
        {
            delete m_TextureEmpty;
            delete m_TextureMissing;
            delete m_MeshEmpty;
            delete m_MeshMissing;
            delete m_MaterialEmpty;
            delete m_MaterialMissing;
            delete m_ShaderEmpty;
            delete m_ShaderMissing;
            delete m_ShaderProgramEmpty;
            delete m_ShaderProgramMissing;
            delete m_DataEmpty;
            delete m_DataMissing;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ResourceDefaults::initialize()
        {
            delete m_TextureEmpty;
            delete m_TextureMissing;
            delete m_MeshEmpty;
            delete m_MeshMissing;
            delete m_MaterialEmpty;
            delete m_MaterialMissing;
            delete m_ShaderEmpty;
            delete m_ShaderMissing;
            delete m_ShaderProgramEmpty;
            delete m_ShaderProgramMissing;
            delete m_DataEmpty;
            delete m_DataMissing;

            initializeTextureDefaults();
            initializeMeshDefaults();
            initializeMaterialDefaults();
            initializeShaderDefaults();
            initializeShaderProgramDefaults();
            initializeDataDefaults();
        }

        Resource* ResourceDefaults::getEmptyResource(ResourceType const type)
        {
            Resource* result = nullptr;

            switch(type)
            {
            case ResourceType::Texture:
                result = m_TextureEmpty;
                break;

            case ResourceType::Mesh:
                result = m_MeshEmpty;
                break;

            case ResourceType::Material:
                result = m_MaterialEmpty;
                break;

            case ResourceType::Shader:
                result = m_ShaderEmpty;
                break;

            case ResourceType::ShaderProgram:
                result = m_ShaderProgramEmpty;
                break;

            case ResourceType::Data:
                result = m_DataEmpty;
                break;

            default:
                break;
            }

            return result;
        }

        Resource* ResourceDefaults::getMissingResource(ResourceType const type)
        {
            Resource* result = nullptr;

            switch(type)
            {
            case ResourceType::Texture:
                result = m_TextureMissing;
                break;

            case ResourceType::Mesh:
                result = m_MeshMissing;
                break;

            case ResourceType::Material:
                result = m_MaterialMissing;
                break;

            case ResourceType::Shader:
                result = m_ShaderMissing;
                break;

            case ResourceType::ShaderProgram:
                result = m_ShaderProgramMissing;
                break;

            case ResourceType::Data:
                result = m_DataMissing;
                break;

            default:
                break;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ResourceDefaults::initializeTextureDefaults()
        {

        }

        void ResourceDefaults::initializeMeshDefaults()
        {
            m_MeshEmpty = new Graphics::MeshEmpty();
            m_MeshMissing = new Graphics::MeshMissing();
        }

        void ResourceDefaults::initializeMaterialDefaults()
        {
            m_MaterialEmpty = new Graphics::MaterialEmpty();

            const std::string missingPath = OcularConfig->get("ResourceDirectory") + "/OcularCore/Materials/Missing.omat";
            m_MaterialMissing = OcularResources->loadUnmanagedFile(File(missingPath));

            if(m_MaterialMissing == nullptr)
            {
                // The 'Missing' material is missing ...
                m_MaterialMissing = new Graphics::MaterialMissing();
                OcularLogger->warning("Missing material is missing (ironic)", OCULAR_INTERNAL_LOG("ResourceDefaults", "initializeMaterialDefaults"));
            }
        }

        void ResourceDefaults::initializeShaderDefaults()
        {

        }

        void ResourceDefaults::initializeShaderProgramDefaults()
        {

        }

        void ResourceDefaults::initializeDataDefaults()
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}