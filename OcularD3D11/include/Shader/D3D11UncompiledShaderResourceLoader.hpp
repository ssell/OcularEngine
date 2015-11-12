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
        /**
         * \class D3D11ShaderResourceLoader
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
         *     Pre-Tesselation (Hull)
         *     Post-Tesselation (Domain)
         *
         * When checking for the presence of particular shaders, the
         * following entry points are tested:
         *
         * <table>
         *     <tr>
         *         <td>Shader Type</td>
         *         <td>Entry Points</td>
         *     </tr>
         *     <tr>
         *         <td>Vertex</td>
         *         <td>VertexMain, VertMain, VSMain, MainVS</td>
         *     </tr>
         *     <tr>
         *         <td>Geometry</td>
         *         <td>GeometryMain, GSMain, MainGS</td>
         *     </tr>
         *     <tr>
         *         <td>Fragment</td>
         *         <td>FragmentMain, FSMain, MainFS, PixelMain, PSMain, MainPS</td>
         *     </tr>
         *     <tr>
         *         <td>Pre-Tesselation</td>
         *         <td>PreTesselationMain, PreTessMain, HullMain, HSMain, MainHS</td>
         *     </tr>
         *     <tr>
         *         <td>Post-Tesselation</td>
         *         <td>PostTesselationMain, PostTessMain, DomainMain, DSMain, MainDS</td>
         *     </tr>
         * </table>
         * </table>
         *
         * For pre-compiled binary shaders (.cso), see the 
         * D3D11CompiledShaderResourceLoader class.
         */
        class D3D11UncompiledShaderResourceLoader : public Core::AResourceLoader
        {
        public:

            D3D11UncompiledShaderResourceLoader();
            ~D3D11UncompiledShaderResourceLoader();

            virtual bool loadResource(Core::Resource* &resource, Core::File const& file) override;

        protected:

            bool getD3DDevice();

        private:

            ID3D11Device* m_D3DDevice;
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