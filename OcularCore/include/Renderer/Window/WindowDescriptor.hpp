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
#ifndef __H__OCULAR_RENDERER_WINDOW_DESCRIPTOR__H__
#define __H__OCULAR_RENDERER_WINDOW_DESCRIPTOR__H__

#include "WindowDisplay.hpp"
#include <string>

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
        /**
         * \struct WindowDescriptor
         *
         * Default values: <br/><br/>
         *
         * <table>
         *     <tr>
         *         <td>Dispay Name</td>
         *         <td>"Window"</td>
         *     </tr>
         *     <tr>
         *         <td>Width</td>
         *         <td>800</td>
         *     </tr>
         *     <tr>
         *         <td>Height</td>
         *         <td>600</td>
         *     </tr>
         *     <tr>
         *         <td>Color Bits</td>
         *         <td>8</td>
         *     </tr>
         *     <tr>
         *         <td>Depth Bits</td>
         *         <td>8</td>
         *     </tr>
         *     <tr>
         *         <td>Stencil Bits</td>
         *         <td>8</td>
         *     </tr>
         *     <tr>
         *         <td>Display Mode</td>
         *         <td>WindowedBordered</td>
         *     </tr>
         *     <tr>
         *         <td>Exclusive Mode</td>
         *         <td>false</td>
         *     </tr>
         * </table>
         */
        struct WindowDescriptor
        {
            WindowDescriptor()
            {
                displayName = "Window";

                width  = 800;
                height = 600;
                
                colorBits   = 8;
                depthBits   = 8;
                stencilBits = 8;

                displayMode = WindowDisplayMode::WindowedBordered;

                exclusiveMode = false;
            }

            ~WindowDescriptor()
            {

            }

            //----------------------------------------

            std::string displayName;  ///< Name used for display purposes (such as the title bar)

            union {uint32_t width, xResolution; };
            union {uint32_t height, yResolution; };

            uint32_t colorBits;
            uint32_t depthBits;
            uint32_t stencilBits;

            WindowDisplayMode displayMode;
            
            bool exclusiveMode;
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