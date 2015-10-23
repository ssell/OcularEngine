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
#ifndef __H__OCULAR_DX11_GRAPHICS_DRIVER__H__
#define __H__OCULAR_DX11_GRAPHICS_DRIVER__H__

#include "Graphics/GraphicsDriver.hpp"

//------------------------------------------------------------------------------------------

struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class AWindow;
    }

    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class GraphicsDriver
         */
        class GraphicsDriverDX11 : public GraphicsDriver
        {
        public:

            GraphicsDriverDX11();
            ~GraphicsDriverDX11();

            //------------------------------------------------------------
            // Inherited Methods

            virtual bool initialize() override;

            //------------------------------------------------------------
            // DX Specific Methods

            ID3D11Device* getDevice() const;
            ID3D11DeviceContext* getDeviceContext() const;

        protected:

            bool validateWindow(std::shared_ptr<Core::AWindow> window, HWND& hwnd) const;
            bool createDeviceAndSwapChain(std::shared_ptr<Core::AWindow> window, HWND hwnd);

        private:

            ID3D11Device* m_Device;
            ID3D11DeviceContext* m_DeviceContext;
            IDXGISwapChain* m_SwapChain;
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