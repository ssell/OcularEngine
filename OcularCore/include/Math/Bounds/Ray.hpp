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
#ifndef __H__OCULAR_MATH_RAY__H__
#define __H__OCULAR_MATH_RAY__H__

#include "Math/Vector3.hpp"

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
         * \class Ray
         *
         * An infinite line that has an origin and direction.
         */
        class Ray
        {
        public:

            /**
             * Creates a ray with the specified origin and direction.
             *
             * \param[in] origin 
             * \param[in] direction Normalized vector direction.
             */
            Ray(Vector3f const& origin, Vector3f const& direction);
            
            Ray();
            ~Ray();

            /**
             * Sets the origin of the ray.
             */
            void setOrigin(Vector3f const& origin);

            /**
             * Sets the normalized direction of the ray.
             */
            void setDirection(Vector3f const& direction);

            /**
             * Returns the origin of the ray.
             */
            Vector3f const& getOrigin() const;

            /**
             * Returns the normalized direction of the ray.
             */
            Vector3f const& getDirection() const;

            /**
             * Returns the point that lies the given distance along the ray
             */
            Vector3f getPointAlong(float distance) const;

        protected:

        private:

            Vector3f m_Origin;
            Vector3f m_Direction;

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