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
#ifndef __H__OCULAR_MATH_WORLEY_NOISE__H__
#define __H__OCULAR_MATH_WORLEY_NOISE__H__

#include "ANoise.hpp"
#include "Math/Random/Random.hpp"

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
             * \class WorleyNoise
             */
            class WorleyNoise : public ANoise
            {
            public:

                WorleyNoise();
                ~WorleyNoise();

                /**
                 *
                 * \param[in] x
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x);

                /** 
                 *
                 * \param[in] x
                 * \param[in] y
                 *
                 * \return Value on range [-1.0, 1.0]
                 */
                virtual float getValue(float const x, float const y);

                /** 
                 *
                 * \param[in] x
                 * \param[in] y
                 * \param[in] z
                 *
                 * \return Value on range [0.0, 1.0]
                 */
                virtual float getValue(float const x, float const y, float const z);

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