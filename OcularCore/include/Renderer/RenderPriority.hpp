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
#ifndef __H__OCULAR_CORE_RENDER_PRIORITY__H__
#define __H__OCULAR_CORE_RENDER_PRIORITY__H__

#include <cstdint>

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
         * \enum RenderPriority
         *
         * Used to determine render order of Renderables and their Materials.
         *
         * Lower priority values are rendered before higher priority values.
         *
         * Generally, if two objects have the same priority they will be sorted 
         * according to their render property (back-to-front for transparent objects, 
         * and front-to-back for everything else).
         *
         * Incremental priorities can be assigned. For example, if we have an
         * opaque material but we wish to render after all other opaques, we
         * can use the value of (RenderPriority::AlphaTest - 1).
         */
        enum class RenderPriority : uint32_t
        {
            Background = 1000,              ///< Used for objects that either must be rendered first, or exist only in the background (ie skyboxes)
            Opaque = 2000,                  ///< Used for the majority of objects
            AlphaTest = 3000,               ///< Used for objects that need to perform alpha-testing
            Transparent = 4000,             ///< Used for objects with transparency (rendered back-to-front)
            Overlay = 5000                  ///< Used for objects tjat either must be rendered last, or exist only in the foreground (ie UI elements) (rendered back-to-front)
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
