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
#ifndef __H__OCULAR_MATH_QUATERNION__H__
#define __H__OCULAR_MATH_QUATERNION__H__

#include "MathCommon.hpp"

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
        template<typename T> class Vector4;
        class Matrix3x3;
        class Matrix4x4;

        struct Quaternion_Internal;

        /**
         * \class Quaternion
         */
        class Quaternion
        {
        public:

            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            /**
             *
             */
            Quaternion(float w, float x, float y, float z);
            
            /**
             * \param[in] angle Angle to rotate in degrees
             * \param[in] axis  Axis to rotate around
             */
            Quaternion(float angle, Vector3<float> const& axis);
            
            /**
             *
             */
            Quaternion(Vector3<float> const& euler);

            /**
             *
             */
            Quaternion(Matrix3x3 const& matrix);

            /**
             *
             */
            Quaternion(Matrix4x4 const& matrix);


            /**
             *
             */
            Quaternion(Quaternion_Internal const& data);

            /**
             *
             */
            Quaternion(Quaternion const& other);

            /**
             *
             */
            Quaternion();

            /**
             *
             */
            ~Quaternion();

            //------------------------------------------------------------------------------
            // OPERATORS
            //------------------------------------------------------------------------------

            Quaternion& operator=(Quaternion const& rhs);
            Quaternion& operator+=(Quaternion const& rhs);
            Quaternion& operator*=(Quaternion const& rhs);
            Quaternion& operator*=(float rhs);
            Quaternion& operator/=(float rhs);

            //------------------------------------------------------------------------------
            // GETTERS / SETTERS
            //------------------------------------------------------------------------------

            /**
             *
             */
            float& w();

            /**
             *
             */
            float& x();

            /**
             *
             */
            float& y();

            /**
             *
             */
            float& z();


            //------------------------------------------------------------------------------
            // GENERAL OPERATIONS
            //------------------------------------------------------------------------------

            /**
             *
             */
            float dot(Quaternion const& rhs);

            /**
             *
             */
            void inverse();

            /**
             *
             */
            Quaternion getInverse() const;

            /**
             *
             */
            Quaternion getConjugate() const;

            /**
             * 
             */
            void normalize();

            /**
             *
             */
            Quaternion getNormalized() const;

            /**
             *
             */
            float getLength() const;
            
            /**
             *
             */
            float getYaw() const;
            
            /**
             *
             */
            float getPitch() const;
            
            /**
             *
             */
            float getRoll() const;

            /**
             *
             */
            float getAngle() const;
            
            /**
             *
             */
            Vector3<float> getAxis() const;
            
            /**
             *
             */
            Quaternion cross(Quaternion const& rhs) const;

            //------------------------------------------------------------------------------
            // STATIC OPERATIONS
            //------------------------------------------------------------------------------

            /**
             *
             */
            static Quaternion CreateLookAtRotation(Vector3<float> const& from, Vector3<float> const& to, Vector3<float> const& up);

            /**
             *
             */
            static Quaternion Rotate(Quaternion const& source, float angle, Vector3<float> const& axis);

            /**
             *
             */
            static Quaternion Mix(Quaternion const& a, Quaternion const& b, float f);

            /**
             * Performs linear quaternion interpolation and returns the resulting quaternion.
             * 
             * \param[in] a The starting Quaternion (result == a when t == 0.0).
             * \param[in] b The ending Quaternion (result == b when t == 1.0).
             * \param[in] f Fractional value [0.0, 1.0]
             *
             * \return The resulting Quaternion (not normalized).
             */
            static Quaternion Lerp(Quaternion const& a, Quaternion const& b, float f);
            
            /**
             * Performs spherical interpolation and returns the resulting quaternion.
             *
             * \param[in] a The starting Quaternion (result == a when t == 0.0)
             * \param[in] b The ending Quaternion (result == b when t == 1.0)
             * \param[in] f Fractional value [0.0, 1.0]
             *
             * \return The resulting Quaternion (not normalized).
             */
            static Quaternion Slerp(Quaternion const& a, Quaternion const& b, float f);
            
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
            static Quaternion Bilerp(Quaternion const& q00, Quaternion const& q10, Quaternion const& q01, Quaternion const& q11, float x, float y);

            //------------------------------------------------------------------------------
            // MISC
            //------------------------------------------------------------------------------

            /**
             * For internal use only.
             * Only modify this pointer if you want your application to crash.
             */
            Quaternion_Internal* getInternal() const;

        protected:

            Quaternion_Internal* m_Internal;

        private:

        };

        bool operator==(Quaternion const& lhs, Quaternion const& rhs);
        bool operator!=(Quaternion const& lhs, Quaternion const& rhs);

        Quaternion operator+(Quaternion const& lhs, Quaternion const& rhs);
        Quaternion operator*(Quaternion const& lhs, Quaternion const& rhs);
        Quaternion operator*(Quaternion const& lhs, float rhs);
        Quaternion operator/(Quaternion const& lhs, float rhs);

        Vector3<float> operator*(Quaternion const& lhs, Vector3<float> const& rhs);
        Vector4<float> operator*(Quaternion const& lhs, Vector4<float> const& rhs);
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