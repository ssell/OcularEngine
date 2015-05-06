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
#ifndef __H__OCULAR_MATH_WAVELET_NOISE__H__
#define __H__OCULAR_MATH_WAVELET_NOISE__H__

#include "ANoise.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Math
     * @{
     */
    namespace Math
    {
        /**
         * \addtogroup Noise
         * @{
         */
        namespace Noise
        {
            /**
             * \class WaveletNoise
             *
             * Wavelet Noise is a coherent gradient noise generation algorithm developed by Pixar. 
             * Compared to Perlin and Simplex noise it suffers less from aliasing and detail loss,
             * especially at extreme angles.
             *
             * Robert L. Cook & Tony DeRose, Pixar Animation Studios: Wavelet Noise
             * http://graphics.pixar.com/library/WaveletNoise/paper.pdf
             */
            class WaveletNoise : public ANoise
            {
            public:

                WaveletNoise();
                ~WaveletNoise();

                /** 
                 * \param[in] x
                 * \param[in] y
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x, float const y);

            protected:

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
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif