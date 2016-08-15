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
#ifndef __H__OCULAR_CORE_GPU_LIGHT__H__
#define __H__OCULAR_CORE_GPU_LIGHT__H__

#include "Math/Vector4.hpp"

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
        class LightSource;

        /**
         * \struct GPULight
         * \brief Structure of generic light data passed to the GPU.
         * \note Must be 16 byte aligned to avoid buffer creation issues and/or performance penalties.
         */
        struct GPULight
        {
            GPULight();

            void operator()(LightSource const* light);

            Math::Vector4f position;
            Math::Vector4f direction;
            Math::Vector4f color;
            Math::Vector4f parameters;  ///< .x = intensity; .y = range; .z = angle (spotlight); .w = type (1 = point, 2 = spot, 3 = directional (0 indicates unused light))
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
