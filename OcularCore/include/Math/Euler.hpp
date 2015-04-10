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

#ifndef __H__OCULAR_MATH_EULER_H__
#define __H__OCULAR_MATH_EULER_H__

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
        class Quaternion;

        //----------------------------------------------------------------

        /**
         * \class Euler
         * \brief Implementation of Euler (Tait-Bryan) angles - yaw, pitch, roll.
         */
        class Euler
        {
        public:

            /**
             *
             */
            Euler();

            /**
             * \param[in] pYaw
             * \param[in] pPitch
             * \param[in] pRoll
             */
            Euler(float const pYaw, float const pPitch, float const pRoll);

            /**
             * Initializes the Euler angles from a rotation matrix.
             *
             * \param[in] rotationMatrix
             */
            Euler(Matrix3x3<float> const& rotationMatrix);

            /**
             * Initializes the Euler angles from a quaternion.
             *
             * \param[in] quaternion
             */
            Euler(Quaternion const& quaternion);

            ~Euler();

            //------------------------------------------------------------
            
            /**
             * Converts this Euler angle representation of a rotation to
             * a 3x3 rotation matrix.
             *
             * \return The converted matrix.
             */
            Matrix3x3<float> toRotationMatrix() const;

            /**
             * Converts this Euler angle representation of a rotation to
             * a Quaternion.
             *
             * \return The converted quaternion.
             */
            Quaternion toQuaternion() const;


            //------------------------------------------------------------

            float yaw;             ///< Yaw in radians
            float pitch;           ///< Pitch in radians
            float roll;            ///< Roll in radians

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