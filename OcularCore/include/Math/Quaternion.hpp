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

#ifndef __H__OCULAR_MATH_QUATERNION_H__
#define __H__OCULAR_MATH_QUATERNION_H__

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
        //----------------------------------------------------------------
        // Forward Declarations

        template<typename T> class Matrix3x3;
        class Euler;

        //----------------------------------------------------------------

        /**
         * \class Quaternion
         */
        class Quaternion
        {
        public:

            /**
             *
             */
            Quaternion();

            /**
             * \param[in] pW
             * \param[in] pX
             * \param[in] pY
             * \param[in] pZ
             */
            Quaternion(float const pW, float const pX, float const pY, float const pZ);

            /**
             * Initializes the Quaternion from a rotation matrix.
             *
             * \param[in] rotationMatrix
             */
            Quaternion(Matrix3x3<float> const& rotationMatrix);

            /**
             * Initializes the Quaternion from a Euler angles.
             *
             * \param[in] quaternion
             */
            Quaternion(Euler const& euler);

            ~Quaternion();

            //------------------------------------------------------------
            
            /**
             * Converts this Quaternion representation of a rotation to  a 3x3 rotation matrix.
             * \return The converted matrix.
             */
            Matrix3x3<float> toRotationMatrix() const;

            /**
             * Converts this Quaternion representation of a rotation to a Euler angles.
             * \return The converted Euler angles.
             */
            Euler toEuler() const;


            //------------------------------------------------------------
            
            float w;             ///< W-component
            float x;             ///< W-component
            float y;             ///< W-component
            float z;             ///< W-component

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

//------------------------------------------------------------------------------------------

#endif