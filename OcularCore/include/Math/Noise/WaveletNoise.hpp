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
#include "Math/Vector3.hpp"
#include <vector>

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
             * Whereas with Perlin and Simplex noise, the generated output could be customized by
             * setting octave/scale/persistence, with Wavelet noise one can set the weight values
             * of the individual bands of noise and a scaling factor.
             *
             * Robert L. Cook & Tony DeRose, Pixar Animation Studios: Wavelet Noise
             * http://graphics.pixar.com/library/WaveletNoise/paper.pdf
             */
            class WaveletNoise : public ANoise
            {
            public:

                /**
                 * \param[in] dimensions Size of the internal noise tile. Suggested values are on the range [32, 256].
                 */
                WaveletNoise(int32_t dimensions = 64);
                ~WaveletNoise();

                /** 
                 * 1D slice of unprojected 3D Wavelet Noise.
                 *
                 * \param[in] x
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x);

                /** 
                 * 2D slice of unprojected 3D Wavelet Noise.
                 *
                 * \param[in] x
                 * \param[in] y
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x, float const y);

                /** 
                 * Unprojected 3D Wavelet Noise.
                 *
                 * \param[in] x
                 * \param[in] y
                 * \param[im] z
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x, float const y, float const z);

                /**
                 * 3D Wavelet Noise projected onto a 2D surface.
                 *
                 * \param[in] pX Position X
                 * \param[in] pY Position Y
                 * \param[in] pZ Position Z
                 * \param[in] nX Normal X
                 * \param[in] nY Normal Y
                 * \param[in] nZ Normal Z
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                float getValue(float const pX, float const pY, float const pZ, float const nX, float const nY, float const nZ);

                /**
                 * Sets the band weights for multibanded Wavelet Noise. 
                 * Pass in a vector with length 0 to get the raw Wavelet Noise.
                 *
                 * \param[in] weights Individual weights for each band of noise. Number of bands is suggested
                 * to be anywhere from 0 (Raw) to as high as 15. See Figure 10 in the source paper linked in this
                 * class' description for sample bands.
                 */
                void setBandWeights(std::vector<float> const& weights);

                /**
                 * Sets the scaling factor of the noise.
                 * \param[in] scale
                 */
                void setScale(float const scale);

            protected:

                void generate();
                void downsample(float* from, float* to, int32_t n, int32_t stride);
                void upsample(float* from, float* to, int32_t n, int32_t stride);

                float getRawNoise(Vector3f const& position);
                float getRawProjectedNoise(Vector3f const& position, Vector3f const& normals);

            private:

                int32_t m_Dimensions;
                int32_t m_NoiseSize;
                
                float m_Scale;
                std::vector<float> m_BandWeights;
                
                float* m_Noise;
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