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
#ifndef __H__OCULAR_MATH_TRANSFORM__H__
#define __H__OCULAR_MATH_TRANSFORM__H__

#include "Vector3.hpp"
#include "Quaternion.hpp"
#include "Matrix4x4.hpp"

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
         * \class Transform
         */
        class Transform
        {
        public:

            Transform();
            Transform(Vector3f const& position, Quaternion const& rotation, Vector3f const& scale);

            ~Transform();

            //------------------------------------------------------------
            // Getters and Setters

            void setPosition(Vector3f const& position);
            void setPosition(float const x, float const y, float const z);
            Vector3f getPosition() const;

            void setRotation(Quaternion const& rotation);
            Quaternion getRotation() const;

            void setScale(Vector3f const& scale);
            Vector3f getScale() const;
            
            /**
             * Retrieves the forwards (negative z-axis) vector of this transform.
             */
            Vector3f getForwards() const;
            
            /**
             * Retrieves the upwards (positive y-axis) vector of this transform.
             */
            Vector3f getUp() const;
            
            /**
             * Retrieves the right (positive x-axis) vector of this transform.
             */
            Vector3f getRight() const;

            //------------------------------------------------------------
            // Movement

            /**
             * Translates the transform in the specified direction and distance.
             * \param[in] translation
             */
            void translate(Vector3f const& translation);
            
            /**
             * Moves the transform along the forward vector for the given delta.
             * Moving backwards can be achieved by specifying a negative delta.
             *
             * \param[in] delta
             */
            void moveForward(float const delta);
            
            /**
             * Moves the transform along the up vector for the given delta.
             * Moving downwards can be achieved by specifying a negative delta.
             *
             * \param[in] delta
             */
            void moveUp(float const delta);
            
            /**
             * Moves the transform along the right vector for the given delta.
             * Moving left can be achieved by specifying a negative delta.
             *
             * \param[in] delta
             */
            void moveRight(float const delta);
            
            //------------------------------------------------------------
            // Rotation

            /**
             * Rotates the transform on the specified axis by the given angle.
             *
             * \param[in] axis  Normalized vector axis to rotate on.
             * \param[in] angle Angles to rotate in degrees.
             */
            void rotate(Vector3f const& axis, float const angle);

            /**
             * Rotates the transform so that the forward vector points at the specified point.
             *
             * \param[in] point    Point position in space to look at.
             * \param[in] upVector Vector that specifies the new up vector.
             */
            void lookAt(Vector3f const& point, Vector3f const& upVector = Vector3f::Up());

            //------------------------------------------------------------
            
            void getModelMatrix(Math::Matrix4x4f& matrix) const;

        protected:

        private:

            Vector3f   m_Position;
            Quaternion m_Rotation;
            Vector3f   m_Scale;
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