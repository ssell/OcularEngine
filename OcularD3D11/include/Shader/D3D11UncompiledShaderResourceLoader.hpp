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
#ifndef __H__OCULAR_D3D11_UNCOMPILED_SHADER_RESOURCE_LOADER__H__
#define __H__OCULAR_D3D11_UNCOMPILED_SHADER_RESOURCE_LOADER__H__

#include "Resources/ResourceLoader.hpp"
#include <d3d11.h>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        class ShaderProgram;

        /**
         * \class D3D11UncompiledShaderResourceLoader
         *
         * Resource loader for all uncompiled D3D11 shader files. This
         * loader maps to the '.hlsl' extension.
         *
         * Each file is checked for individual shader programs (one of
         * each type), and then the individual shaders are combined
         * into a single ShaderProgram resource.
         *
         * A file may have all shader types present, or only one. For
         * any non-present shaders, the ShaderProgram will be assigned
         * a NULL value. The supported shader types for D3D11 are:
         *
         *     Vertex
         *     Geometry
         *     Fragment (Pixel)
         *     Pre-Tessellation (Hull)
         *     Post-Tessellation (Domain)
         *
         * When checking for the presence of particular shaders, the
         * following entry points are tested:
         *
         * | Shader Type      | Entry Points
         * | ---------------- | ---------------------------------------------------------------------------
         * | Vertex           | VertexMain, VertMain, VSMain, MainVS
         * | Geometry         | GeometryMain, GSMain, MainGS
         * | Fragment         | FragmentMain, FragMain, FSMain, MainFS, PixelMain, PixMain, PSMain, MainPS
         * | Pre-Tessellation  | PreTessellationMain, PreTessMain, HullMain, HSMain, MainHS
         * | Post-Tessellation | PostTessellationMain, PostTessMain, DomainMain, DSMain, MainDS
         *
         * All shaders are assumed to be valid Shader Model 5 (D3D 11 and 11.1).
         *
         * For pre-compiled binary shaders (.cso), see the 
         * D3D11CompiledShaderResourceLoader class.
         */
        class D3D11UncompiledShaderResourceLoader : public Core::AResourceLoader
        {
        public:

            D3D11UncompiledShaderResourceLoader();
            virtual ~D3D11UncompiledShaderResourceLoader();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file) override;

        protected:

            bool getD3DDevice();
            
            // Notice that compileVertexShader returns bool while all others return void.
            // If there is a real compilation error with the file (not just an entrypoint error)
            // then the same compilation error will be reported for all shader compilation attempts.

            // So when compileVertexShader fails, we know there is a real issue with the file and
            // that no shaders can be compiled from it. It would be pointless to continue the other
            // shader compilations if vertex fails from an error. 

            // But if compileVertexShader experiences success or an entrypoint error, then we can
            // continue with attempting the other shader types.

            bool compileVertexShader(Core::File const& file, LPCWSTR source, ShaderProgram* program);
            void compileGeometryShader(Core::File const& file, LPCWSTR source, ShaderProgram* program);
            void compileFragmentShader(Core::File const& file, LPCWSTR source, ShaderProgram* program);
            void compilePreTessellationShader(Core::File const& file, LPCWSTR source, ShaderProgram* program);
            void compilePostTessellationShader(Core::File const& file, LPCWSTR source, ShaderProgram* program);

            bool isEntryPointError(ID3DBlob* errorLog) const;

        private:

            ID3D11Device* m_D3DDevice;
            ID3D11DeviceContext* m_D3DDeviceContext;
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