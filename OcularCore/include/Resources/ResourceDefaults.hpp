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

#pragma once
#ifndef __H__OCULAR_RESOURCES_RESOURCE_DEFAULTS__H__
#define __H__OCULAR_RESOURCES_RESOURCE_DEFAULTS__H__

#include "Resource.hpp"
#include "ResourceType.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        class ResourceDefaults
        {
        public:

            ResourceDefaults();
            ~ResourceDefaults();

            void initialize();

            Resource* getEmptyResource(ResourceType type);
            Resource* getMissingResource(ResourceType type);

        protected:

            void initializeTextureDefaults();
            void initializeMeshDefaults();
            void initializeMaterialDefaults();
            void initializeShaderDefaults();
            void initializeShaderProgramDefaults();
            void initializeDataDefaults();

        private:

            Resource* m_TextureEmpty;
            Resource* m_TextureMissing;

            Resource* m_MeshEmpty;
            Resource* m_MeshMissing;

            Resource* m_MaterialEmpty;
            Resource* m_MaterialMissing;

            Resource* m_ShaderEmpty;
            Resource* m_ShaderMissing;

            Resource* m_ShaderProgramEmpty;
            Resource* m_ShaderProgramMissing;

            Resource* m_DataEmpty;
            Resource* m_DataMissing;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif