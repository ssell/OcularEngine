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

#include "stdafx.hpp"
#include "Shader/D3D11UncompiledShaderResourceLoader.hpp"
#include "D3D11GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11UncompiledShaderResourceLoader::D3D11UncompiledShaderResourceLoader()
            : Core::AResourceLoader(".hlsl"),
              m_D3DDevice(nullptr)
        {
        
        }

        D3D11UncompiledShaderResourceLoader::~D3D11UncompiledShaderResourceLoader()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool D3D11UncompiledShaderResourceLoader::loadResource(Core::Resource* &resource, Core::File const& file)
        {
            bool result = false;

            if(getD3DDevice())
            {
                // ...
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11UncompiledShaderResourceLoader::getD3DDevice()
        {
            bool result = true;

            if(m_D3DDevice == nullptr)
            {
                D3D11GraphicsDriver* driver = dynamic_cast<D3D11GraphicsDriver*>(OcularGraphics.get());

                if(driver)
                {
                    m_D3DDevice = driver->getD3DDevice();

                    if(m_D3DDevice == nullptr)
                    {
                        // Still null?
                        result = false;
                    }
                }
                else
                {
                    result = false;
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}