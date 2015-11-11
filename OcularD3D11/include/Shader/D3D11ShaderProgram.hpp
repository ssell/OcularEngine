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
#ifndef __H__OCULAR_D3D11_GRAPHICS_SHADER_PROGRAM__H__
#define __H__OCULAR_D3D11_GRAPHICS_SHADER_PROGRAM__H__

#include "Resources/Resource.hpp"
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
        class D3D11VertexShader;
        class D3D11GeometryShader;
        class D3D11FragmentShader;
        class D3D11PreTesselationShader;
        class D3D11PostTesselationShader;

        /**
         * \class D3D11ShaderProgram
         *
         * A complete Direct3D 11 shader program with the following components:
         *
         *     Vertex Shader
         *     Geometry Shader (optional)
         *     Fragment/Pixel Shader 
         *     PreTesselation/Hull Shader (optional)
         *     PostTesselation/Domain Shader (optional)
         *
         * The D3D11ShaderProgram represents the contents of a single .hlsl file...
         * Need more thoughts on this...
         */
        class D3D11ShaderProgram : public Core::Resource 
        {
        public:

            D3D11ShaderProgram();
            ~D3D11ShaderProgram();

            virtual void unload() override;

        protected:
            
            D3D11VertexShader*          m_VertexShader;
            D3D11GeometryShader*        m_GeometryShader;
            D3D11FragmentShader*        m_FragmentShader;
            D3D11PreTesselationShader*  m_PreTesselationShader;
            D3D11PostTesselationShader* m_PostTesselationShader;

        private:
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