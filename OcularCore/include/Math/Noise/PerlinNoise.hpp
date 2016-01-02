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
#ifndef __H__OCULAR_MATH_PERLIN_NOISE__H__
#define __H__OCULAR_MATH_PERLIN_NOISE__H__

#include "ANoise.hpp"
#include "Math/Random/ARandom.hpp"

#include <memory>

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
             * \class PerlinNoise
             *
             * Perlin Noise is a type of gradient noise. It was designed in 1983 by Ken Perlin, and
             * is very similar to Simplex Noise. 
             *
             * Compared to Simplex Noise, Perlin Noise is more computationally expensive and suffers
             * from directional artifacts. Perlin Noise also has the behaviour that values on integer
             * coordinates will always be equal to 0.
             */
            class PerlinNoise : public ANoise
            {
            public:

                PerlinNoise();
                ~PerlinNoise();

                /**
                 * Returns the noise value at the specified point.
                 *
                 * Note: To get the raw noise value (without octaves, etc.) set the
                 * octaves, scale, and persistence all to 1.
                 *
                 * \param[in] x
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x);

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
                 * \return Value on range [0.0, 1.0]
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

                /**
                 * Reseeds the lookup tables used to generate noise values.
                 * \param[in] seed
                 */
                void seed(int64_t seed);

            protected:

                float getInterpolatedNoise(float const x);
                float getInterpolatedNoise(float const x, float const y);
                float getInterpolatedNoise(float const x, float const y, float const z);

                float getSmoothNoise(float const x, float const y);

                float getRandom(float const x, float const y);

            private:

                uint32_t m_Octaves;
                float    m_Persistence;
                float    m_Scale;

                uint32_t m_Permutations[514];
                float    m_Gradient1[514];
                float    m_Gradient2[514][2];
                float    m_Gradient3[514][3];

                int64_t  m_Seed;

                std::shared_ptr<Random::ARandom> m_PRNG;
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