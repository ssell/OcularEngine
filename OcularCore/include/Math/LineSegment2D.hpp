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
#ifndef __H__OCULAR_MATH_LINE_SEGMENT_2D__H__
#define __H__OCULAR_MATH_LINE_SEGMENT_2D__H__

#include "MathCommon.hpp"
#include "Vector2.hpp"

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
         * \class LineSegment2D
         * 
         * A 2D line segment composed of two endpoints: A and B.
         */
        template<typename T>
        class LineSegment2D
        {
        public:

            /** 
             * Creates a new line segment with the given end points.
             *
             * \param[in] a
             * \param[in] b
             */
            LineSegment2D(Vector2<T> const& a, Vector2<T> const& b)
            {
                m_A = a;
                m_B = b;

                updateLength();
            }

            LineSegment2D()
            {
                m_Length = static_cast<T>(0);
                m_LengthSquared = static_cast<T>(0);
            }
            
            ~LineSegment2D()
            {
            
            }

            Vector2<T> const& getA() const
            {
                return m_A;
            }

            Vector2<T> const& getB() const
            {
                return m_B;
            }

            void setA(Vector2<T> const& a)
            {
                m_A = a;
                updateLength();
            }

            void setB(Vector2<T> const& b)
            {
                m_B = b;
                updateLength();
            }

            /**
             * Returns the length of the line segment.
             */
            T const& getLength() const
            {
                return m_Length;
            }

            /**
             * Returns the squared length of the line segment.
             */
            T const& getLengthSquared() const
            {
                return m_LengthSquared;
            }

            /**
             * Calculates which side of the line segment the point lies.
             *
             * This can be visualized as standing on A and looking torwards B.
             *
             * If the return value is -1, then the point is to the right of the line.
             * If the return value is +1, then the point is to the left of the line.
             * If the reutrn value is 0, then the point is on the line.
             *
             * \param[in] point 
             * \return Which side the point is on: left (+1), right (-1), on the line (0).
             */
            int32_t whichSide(Vector2<T> const& point) const
            {
                int32_t result;
                const T value = ((m_B.x - m_A.x) * (point.y - m_A.y)) - ((m_B.y - m_A.y) * (point.x - m_A.x));
                
                if(IsZero<T>(value))
                {
                    result = 0;
                }
                else
                {
                    result = (value < static_cast<T>(0)) ? -1 : 1;
                }

                return result;
            }

            /**
             * Calculates the minimum distance from the point to the line segment.
             * This distance is in relation whichever point on the segment is closest to the point.
             *
             * \param[in] point
             *
             * \return Minimum distance to the point from the line segment.
             */
            T distanceTo(Vector2<T> const& point) const
            {
                T result;

                if(IsZero<T>(m_LengthSquared))
                {
                    const Vector2<T> pointToA = point - m_A;
                    result = pointToA.getLength();    
                }
                else
                {
                    const Vector2<T> pointToA = point - m_A;
                    const Vector2<T> pointToB = point - m_B;
                    const Vector2<T> bToA = m_B - m_A;

                    const T t = pointToA.dot(bToA) / m_LengthSquared;

                    if(t < static_cast<T>(0))
                    {
                        result = pointToA.getLength();
                    }
                    else if(t > static_cast<T>(1))
                    {
                        result = pointToB.getLength();
                    }
                    else
                    {
                        const Vector2<T> projection = m_A + ((m_B - m_A) * t);
                        const Vector2<T> vector = point - projection;

                        result = vector.getLength();
                    }
                }

                return result;
            }

        protected:

            void updateLength() 
            {
                const Vector2<T> vector = m_B - m_A;

                m_Length = vector.getLength();
                m_LengthSquared = m_Length * m_Length;
            }

        private:

            Vector2<T> m_A;
            Vector2<T> m_B;

            T m_Length;
            T m_LengthSquared;
        };

        //--------------------------------------------
        // Common formats

        typedef LineSegment2D<float>  LineSegment2Df;
        typedef LineSegment2D<double> LineSegment2Dd;
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