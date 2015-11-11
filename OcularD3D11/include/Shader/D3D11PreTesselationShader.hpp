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
#ifndef __H__OCULAR_D3D11_GRAPHICS_PRETESSELATION_SHADER__H__
#define __H__OCULAR_D3D11_GRAPHICS_PRETESSELATION_SHADER__H__

#include "Graphics/Shader/PreTesselationShader.hpp"
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
         * \class D3D11PreTesselationShader 
         */
        class D3D11PreTesselationShader : public PreTesselationShader 
        {
        public:

            D3D11PreTesselationShader(ID3D11Device* device);
            ~D3D11PreTesselationShader();

            virtual void unload() override;
            virtual void bind() override;
            virtual void unbind() override;

            ID3D11HullShader* getD3DShader();

        protected:
            
            ID3D11Device* m_D3DDevice;
            ID3D11HullShader* m_D3DShader;

        private:
        };

        typedef D3D11PreTesselationShader D3D11HullShader;
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