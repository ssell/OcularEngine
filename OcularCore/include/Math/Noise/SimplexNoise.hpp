/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_MATH_SIMPLEX_NOISE__H__
#define __H__OCULAR_MATH_SIMPLEX_NOISE__H__

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
             * \class SimplexNoise
             *
             * Simplex Noise is an n-dimensional noise function that produces results
             * comparable to the class Perlin Noise, but has less computational overhead.
             *
             * Originally designed by Ken Perlin (2001), this implementation is adapted 
             * from the work done by Stefan Gustavson.
             *
             * Though there is no seeding of Simplex Noise like with PRNGs, once can achieve
             * a similar 'randomized' result by applying an offset to the provided x/y/z parameters.
             * For example:
             *
             *     int32_t seed = prng->next(0, 1000);
             *     
             *     for(uint32_t y = 0; y < 5; y++)
             *     {
             *         for(uint32_t x = 0; x < 5; x++)
             *         {
             *             float value = noise->getValue((x + seed), (y + seed));
             *         }
             *     }
             *
             * Just remember that this is a fake randomization. The value at (0,0) will always
             * be the same throughout all runs.
             *
             * Ken Perlin: Making Noise
             * http://www.noisemachine.com/talk1/32.html
             *
             * Stefan Gustavson: Simplex Noise Demystified
             * http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
             */
            class SimplexNoise : public ANoise
            {
            public:

                SimplexNoise();
                ~SimplexNoise();

                /** 
                 * Returns the noise value at the specified 2D coordinates.
                 *
                 * Note: To get the raw noise value (without octaves, etc.) set the
                 * octaves, scale, and persistence all to 1.
                 *
                 * \param[in] x
                 * \param[in] y
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x, float const y);

                /** 
                 * Returns the noise value at the specified 3D coordinates.
                 *
                 * Note: To get the raw noise value (without octaves, etc.) set the
                 * octaves, scale, and persistence all to 1.
                 *
                 * \param[in] x
                 * \param[in] y
                 * \param[in] z
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x, float const y, float const z);

                /**
                 * Sets the number of octaves to apply when generating noise values.
                 *
                 * For each octave, a higher frequency/lower amplitude function will
                 * be added to the original. Additional octaves increase the amount of
                 * time required to generate the final value, but increases the definition.
                 *
                 * \param octaves Number of octaves to apply (sane values are 0 to 15) (default 6)
                 */
                void setOctaves(uint32_t const octaves);

                /**
                 * Sets the persistence value for applied octaves.
                 *
                 * The higher the persistence, the more of each succeeding octave 
                 * will be added to the original. Very high persistence values can
                 * lead to output the resembles raw noise.
                 *
                 * \param[in] persistence Persistence value [0.0, 1.0] (default 0.5)
                 */
                void setPersistence(float const persistence);

                /**
                 * Sets the scale of the noise generator.
                 *
                 * Scale can be thought of as a zoom-level. The lower the
                 * scale, the closer in the zoom and vice versa.
                 *
                 * Extremely low values can result in a blobby or solid output.
                 * Extremely high values can result in output that resembles raw noise.
                 *
                 * \param[in] scale Scale value (sane values are 0.0001 to 1.0) (default 0.01)
                 */
                void setScale(float const scale);

            protected:

                float getRawNoise(float const x, float const y);
                float getRawNoise(float const x, float const y, float const z);

            private:

                uint32_t m_Octaves;
                float m_Persistence;
                float m_Scale;
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