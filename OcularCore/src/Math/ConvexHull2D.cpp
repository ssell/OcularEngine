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

#include "Math/ConvexHull2D.hpp"
#include <algorithm>

//------------------------------------------------------------------------------------------

/// Removes all instances of the specified value from the provided vector.
void RemoveAll(std::vector<Ocular::Math::Point2f>& vector, Ocular::Math::Point2f const& value)
{
    vector.erase(std::remove(vector.begin(), vector.end(), value), vector.end());
}

namespace Ocular
{
    namespace Math
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ConvexHull2D::ConvexHull2D(std::vector<Point2f> const& points)
        {
            m_Points.assign(points.begin(), points.end());
            m_Hull.reserve(m_Points.size());

            createHull();
        }

        ConvexHull2D::ConvexHull2D(Point2f const* points, uint32_t numPoints)
        {
            m_Points.reserve(numPoints);
            m_Hull.reserve(numPoints);

            if(points)
            {
                for(uint32_t i = 0; i < numPoints; i++)
                {
                    m_Points[i] = points[i];
                }
            }

            createHull();
        }

        ConvexHull2D::~ConvexHull2D()
        {
            m_Points.clear();
            m_Hull.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ConvexHull2D::sort()
        {
        
        }

        uint32_t ConvexHull2D::getNumPoints() const
        {
            return m_Hull.size();
        }

        std::vector<Point2f> const& ConvexHull2D::getHull() const
        {
            return m_Hull;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void ConvexHull2D::createHull()
        {
            // Implementation of the QuickHull algorithm as described at:
            // http://www.cse.yorku.ca/~aaw/Hang/quick_hull/Algorithm.html

            // Note: All 'left' and 'right' comparisons are done based on treating
            // the line segment as originating at A and ending at B.

            // Also Note: The QuickHull algorithm typically deals with right sides.
            // But left sides are more intuitive in my head and thus those are used in
            // my implementation. Switching to right-side checking requires reversing
            // the order of line segments and of course checking for whichSide to
            // return Right instead of Left.

            //------------------------------------------------------------
            // Find the two end points (x-axis extremes)

            Vector2f minEndpoint(FLT_MAX, 0.0f);
            Vector2f maxEndpoint(FLT_MIN, 0.0f);

            for(auto point : m_Points)
            {
                if(point.x < minEndpoint.x)
                {
                    minEndpoint = point;
                }

                if(point.x > maxEndpoint.x)
                {
                    maxEndpoint = point;
                }
            }

            //------------------------------------------------------------
            // Remove the extremes from the point collection and them to our convex hull list

            m_Hull.push_back(minEndpoint);
            m_Hull.push_back(maxEndpoint);

            RemoveAll(m_Points, minEndpoint);
            RemoveAll(m_Points, maxEndpoint);

            const LineSegment2Df segmentAB(minEndpoint, maxEndpoint);
            const LineSegment2Df segmentBA(maxEndpoint, minEndpoint);

            //--------------------------------------------------------------------
            // Split the remaining points into a 'left' and 'right' group

            std::vector<Point2f> leftGroup;
            std::vector<Point2f> rightGroup;

            leftGroup.reserve(m_Points.size());
            rightGroup.reserve(m_Points.size());

            splitCollection(segmentAB, leftGroup, rightGroup);

            //--------------------------------------------------------------------
            // Recursively find all hull points

            findHull(segmentAB, leftGroup);
            findHull(segmentBA, rightGroup);
        }

        void ConvexHull2D::splitCollection(LineSegment2Df const& segment, std::vector<Point2f>& leftGroup, std::vector<Point2f>& rightGroup)
        {
            // Since the initial split is always somewhat horizontal we can do a
            // quick heigh comparison. Any points that can not be grouped based
            // solely on their y components will need additional calculations.

            Vector2f highPoint = segment.getA();
            Vector2f lowPoint  = segment.getB();

            if(highPoint.y < lowPoint.y)
            {
                highPoint = segment.getB();
                lowPoint  = segment.getA();
            }

            for(auto point : m_Points)
            {
                if(point.y > highPoint.y)
                {
                    // If a point is higher than our highest endpoint, then it is clearly on the left side
                    leftGroup.push_back(point);
                }
                else if(point.y < lowPoint.y)
                {
                    // If a point is lower than our lowest endpoint, then it is clearly on the right side
                    rightGroup.push_back(point);
                }
                else
                {
                    LineSegmentSide side = segment.whichSide(point);

                    if(side == RightOfSegment)
                    {
                        rightGroup.push_back(point);
                    }
                    else
                    {
                        leftGroup.push_back(point);
                    }
                }
            }
        }

        void ConvexHull2D::findHull(LineSegment2Df const& segment, std::vector<Point2f>& points)
        {
            /**
             * Find the most distant point from the segment.
             *
             * This point (C) creates a triangle ACB with the two endpoints (AB) and is part of the hull.
             * Any points inside ACB are not part of the hull, while any points outside of it
             * may be part of the hull.
             *
             * Check the points to the left of the segment AC. The most distant one (D) will create a
             * a triangle ADC. Any inside this triangle are not part of the hull, and so on and so forth.
             *
             * Once all points left of AC have been accounted for, then do the same for all points
             * to the left of the line segment CB.
             */

            if(points.size() == 0)
            {
                return;
            }

            //------------------------------------------------------------
            // 1. Find most distant point

            Vector2f maxPoint;
            
            float maxDistance = FLT_MIN;
            float distance = 0.0f;

            for(auto point : points)
            {
                distance = segment.distanceTo(point);

                if(distance > maxDistance)
                {
                    maxDistance = distance;
                    maxPoint = point;
                }
            }

            m_Hull.push_back(maxPoint);
            RemoveAll(points, maxPoint);

            //------------------------------------------------------------
            // 2. Get all points left of line segment AC
            // 3. Get all points left of line segment CB
            // 4. Any remaining points are inside the triangle and not potentially part of the hull.

            const LineSegment2Df segmentAC(segment.getA(), maxPoint);
            const LineSegment2Df segmentCB(maxPoint, segment.getB());

            std::vector<Point2f> leftOfAC;
            std::vector<Point2f> leftOfCB;

            leftOfAC.reserve(points.size());
            leftOfCB.reserve(points.size());

            for(auto point : points)
            {
                if(segmentAC.whichSide(point) == LeftOfSegment)
                {
                    leftOfAC.push_back(point);
                }
                else if(segmentCB.whichSide(point) == LeftOfSegment)
                {
                    leftOfCB.push_back(point);
                }
            }

            //------------------------------------------------------------

            findHull(segmentAC, leftOfAC);
            findHull(segmentCB, leftOfCB);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}

