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
#ifndef __H__OCULAR_ENGINE_MATH_MORTON_CODE__H__
#define __H__OCULAR_ENGINE_MATH_MORTON_CODE__H__

#include "MathCommon.hpp"
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
        template<typename T> class Vector3;

        class MortonCode
        {
        public:

            /**
             * Calculates the Morton Code index value from a vector.
             *
             * The individual components are expected to be in the range of [0,1].
             *
             * \param[in] vector
             */
            static uint64_t calculate(Vector3<float> vector);

            /** 
             * Calculates the Morton Code index value from a three-component point.
             * 
             * The values are expected to be in the range of [0,1].
             *
             * \param[in] x
             * \param[in] y
             * \param[in] z
             */
            static uint64_t calculate(float x, float y, float z);

            /**
             * Calculates the Morton Code index value from a three-component integer point.
             *
             * Only the first 21-bits (counting from the right) are used in calculating the Morton Code.
             * This is due to the interleaving of the three integers resulting in a maximum accuracy of
             * (3 * 21 = 63) bits being stored within the resulting 64-bit integer.
             *
             * \param[in] x
             * \param[in] y
             * \param[in] z
             */
            static uint64_t calculate(uint32_t x, uint32_t y, uint32_t z);

            /**
             * Calculates a collection of Morton Codes for a number of vectors.
             *
             * Using this method is advantageous to calling the individual calculation methods because:
             *
             *     - Less calls (obvious)
             *     - Can perform range-setting if the input values are not already on the range [0,1]
             *     - Automatically handles instances of duplicate Morton Codes
             *     - Can automatically handle value sorting 
             *
             * \param[in]  vectors     Container will all input Vectors to calculate the Morton Codes of.
             * \param[out] mortonCodes Output container filled will all of the Morton Codes.
             * \param[in]  areInRange  If true, the input values are already on the range [0,1].
             * \param[in]  sortCodes   If true, the output codes will be sorted in ascending order.
             */
            static void calculate(std::vector<Vector3<float>> const& vectors, std::vector<uint64_t>& mortonCodes, bool areInRange = false, bool sortCodes = true);

        protected:

            /**
             * Calculates the transformation factors for the collection of vectors. 
             *
             * The offset factor is used to ensure that all values are positive. <br/>
             * The scale factor is used to map all values to the [0,1] range.
             *
             * \param[in]  vectors
             * \param[out] scaleFactor
             * \param[out] offsetFactor
             */
            static void getTransformFactors(std::vector<Vector3<float>> const& vectors, float& scaleFactor, float& offsetFactor);

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

//------------------------------------------------------------------------------------------

#endif