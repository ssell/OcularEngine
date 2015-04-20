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

#include "Vector3.hpp"

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

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            Quaternion operator=(Quaternion const& rhs);

            //------------------------------------------------------------------------------
            // CONVERSIONS
            //------------------------------------------------------------------------------

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

            //------------------------------------------------------------------------------
            // OPERATIONS
            //------------------------------------------------------------------------------
            
            /**
             * Rotates the provided Vector by this Quaternion.
             *
             * \param[in] vector The Vector to be rotated.
             * \return The rotated vector.
             */
            Vector3<float> rotate(Vector3<float> const& vector) const;

            /**
             * \return Returns TRUE if the Quaternion is normalized (w + x + y + z = 0)
             */
            bool isNormalized() const;
            /**
             * Normalizes the Quaternion.
             * \note This method modifies the internal data stored in the Quaternion. See getNormalized if this is not desired.
             */
            void normalize();

            /**
             * Returns the normalized form of this Quaternion.
             * \note This method does not modify the internal data. See normalize if this is not desired.
             */
            Quaternion getNormalized() const;

            /**
             * Calculates the length of this Quaternion.
             * \return The length of this Quaternion.
             */
            float getLength() const;

            /**
             * Calculates the squared length of this Quaternion.
             * \return The squared length of this Quaternion.
             */
            float getLengthSquared() const;

            /**
             * Calculates and returns the inverse of this Quaternion.
             * \return The inverse of this Quaternion.
             */
            Quaternion getInverse() const;

            /**
             * \return The conjugate of the quaternion.
             */
            Quaternion getConjugate() const;

            /**
             * \return The x-rotation axis.
             */
            Vector3<float> getXRotationAxis() const;

            /**
             * \return The y-rotation axis.
             */
            Vector3<float> getYRotationAxis() const;

            /**
             * \return The z-rotation axis.
             */
            Vector3<float> getZRotationAxis() const;

            /**
             * Calculates and returns the dot product of two quaternions.
             */
            float dot(Quaternion const& rhs) const;

            //------------------------------------------------------------------------------
            // Static Methods
            //------------------------------------------------------------------------------

            /**
             * ...
             *
             * \param[in] forward
             * \param[in] upward
             */
            static Quaternion createLookAtRotation(Vector3<float> const& forward = Vector3<float>::forward(), Vector3<float> const& upward = Vector3<float>::up());

            /**
             * Performs linear quaternion interpolation and returns the resulting quaternion.
             * 
             * \param[in] a The starting Quaternion (result == a when t == 0.0).
             * \param[in] b The ending Quaternion (result == b when t == 1.0).
             * \param[in] t Alpha value.
             *
             * \return The resulting Quaternion (not normalized).
             */
            static Quaternion lerp(Quaternion const& a, Quaternion const& b, float const& t);

            /**
             * Performs bilinear quaternion interpolation and returns the result quaternion.
             *
             * \param[in] q00 "Lower-left" starting point for interpolation (x == 0.0 && y == 0.0)
             * \param[in] q10 "Lower-right" ending point for interpolation (x == 1.0)
             * \param[in] q01 "Upper-left" ending point for interpolation (y == 1.0)
             * \param[in] q11 "Upper-right" ending point for interpolation (x == 1.0 && y == 1.0)
             *
             * \return The resulting Quaternion (not normalized).
             */
            static Quaternion bilerp(Quaternion const& q00, Quaternion const& q10, Quaternion const& q01, Quaternion const& q11, float const& x, float const& y);

            /**
             * Performs spherical interpolation and returns the resulting quaternion.
             *
             * \param[in] a The starting Quaternion (result == a when t == 0.0)
             * \param[in] b The ending Quaternion (result == b when t == 1.0)
             * \param[in] t 
             *
             * \return The resulting Quaternion (not normalized).
             */
            static Quaternion slerp(Quaternion const& a, Quaternion const& b, float const& t);

            //------------------------------------------------------------------------------
            // PUBLIC VARIABLES
            //------------------------------------------------------------------------------
            
            float w;             ///< W-component
            float x;             ///< W-component
            float y;             ///< W-component
            float z;             ///< W-component

        protected:


        private:
        };

        Quaternion     operator+(Quaternion const& lhs, Quaternion const& rhs);
        Quaternion     operator-(Quaternion const& lhs, Quaternion const& rhs);
        Quaternion     operator*(Quaternion const& lhs, Quaternion const& rhs);
        Vector3<float> operator*(Quaternion const& lhs, Vector3<float> const& rhs);
        Vector3<float> operator*(Vector3<float> const& lhs, Quaternion const& rhs);
        Quaternion     operator*(Quaternion const& lhs, float const& rhs);
        Quaternion     operator*(float const& lhs, Quaternion const& rhs);
        Quaternion     operator/(Quaternion const& lhs, float const& rhs);

        bool operator==(Quaternion const& lhs, Quaternion const& rhs);
        bool operator!=(Quaternion const& lhs, Quaternion const& rhs);

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