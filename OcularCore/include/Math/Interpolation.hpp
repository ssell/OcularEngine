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
#ifndef __H__OCULAR_ENGINE_MATH_INTERPOLATION__H__
#define __H__OCULAR_ENGINE_MATH_INTERPOLATION__H__

#include "Definitions.hpp"
#include <cmath>

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
         * Linearly interpolates from one value to another.
         *
         * With linear interpolation, a straight line will result from the transition between values.
         * If used to interpolate over multiple points, for example a graph, there will be no 
         * continuity between the points.
         *
         * \param[in] from
         * \param[in] to
         * \param[in] frac Value on range [0.0, 1.0]
         *
         * \return Interpolated value. When frac == 0.0, returns from. When frac == 1.0, returns to.
         */
        static float InterpolateLinear(float const from, float const to, float const frac)
        {
            float boundFrac = (frac < 0.0f) ? 0.0f : (frac > 1.0f) ? 1.0f : frac;

            return (from * (1.0f - boundFrac)) + (to * boundFrac);
        }

        /**
         * Smoothly interpolates from one value to another.
         *
         * With cosine interpolation, a smooth curve will result from the transition between values.
         * If used to interpolate over multiple points, for example a graph, there will be no
         * continuity between the points.
         *
         * \param[in] from
         * \param[in] to
         * \param[in] frac Value on range [0.0, 1.0]
         *
         * \return Interpolated value. When frac == 0.0, returns from. When frac == 1.0, returns to.
         */
        static float InterpolateCosine(float const from, float const to, float const frac)
        {
            float boundFrac = (frac < 0.0f) ? 0.0f : (frac > 1.0f) ? 1.0f : frac;
            float x = (1.0f - cosf(boundFrac * static_cast<float>(PI))) * 0.5f;

            return (from * (1.0f - x)) + (to * x);
        }

        /**
         * Smoothly interpolates from one value to another.
         *
         * With cubic interpolation, a smooth curve will result from the transition between values.
         * If used to interpolate over multiple points, for example a graph, there will be
         * continuity between the points (unlike linear and cosine).
         *
         * \param[in] before Value prior to our starting point (used to influence the result and provide continuity)
         * \param[in] from   Starting point of the interpolation
         * \param[in] to     Ending point of the interpolation
         * \param[in] after  Value following our ending point (used to influence the result and provide continuity)
         *
         * \return Interpolated value. When frac == 0.0, returns from. When frac == 1.0f, returns to.
         */
        static float InterpolateCubic(float const before, float const from, float const to, float const after, float const frac)
        {
            float boundFrac = (frac < 0.0f) ? 0.0f : (frac > 1.0f) ? 1.0f : frac;
            float frac2 = boundFrac * boundFrac;
            float a0 = after - to - before + from;
            float a1 = before - from - a0;
            float a2 = to - before;
            float a3 = from;

            return (a0 * boundFrac * frac2) + (a2 * frac2) + (a2 * boundFrac) + a3;
        }

        /**
         * Variant of cubic interpolation which produces a very smooth curved result.
         *
         * \param[in] before Value prior to our starting point (used to influence the result and provide continuity)
         * \param[in] from   Starting point of the interpolation
         * \param[in] to     Ending point of the interpolation
         * \param[in] after  Value following our ending point (used to influence the result and provide continuity)
         *
         * \return Interpolated value. When frac == 0.0, returns from. When frac == 1.0f, returns to.
         */
        static float InterpolateCatmullRom(float const before, float const from, float const to, float const after, float const frac)
        {
            float boundFrac = (frac < 0.0f) ? 0.0f : (frac > 1.0f) ? 1.0f : frac;
            float frac2 = boundFrac * boundFrac;
            float a0 = (-0.5f * before) + (1.5f * from) - (1.5f * to) + (0.5f * after);
            float a1 = before - (2.5f * from) + (2.0f * to) - (0.5f * after);
            float a2 = (-0.5f * before) + (0.5f * to);
            float a3 = from;

            return (a0 * boundFrac * frac2) + (a2 * frac2) + (a2 * boundFrac) + a3;
        }

        /**
         * Smoothly interpolates from one value to another.
         *
         * With hermite interpolation, a smooth curve will result frm the transition between values.
         * If used to interpolate over multiple points, for example a graph, there will be
         * continuity between the points (unlike linear and cosine).
         *
         * There are additional controls available in hermite interpolation: tension and bias.
         *
         * Tension is used to tighten or loosen the curvature at the known points.
         *
         * Bias is used to twist the curve around the known points.
         *
         * \param[in] before  Value prior to our starting point (used to influence the result and provide continuity)
         * \param[in] from    Starting point of the interpolation
         * \param[in] to      Ending point of the interpolation
         * \param[in] after   Value following our ending point (used to influence the result and provide continuity)
         * \param[in] tension Curvature at known points. High == 1.0, Normal == 0.0, Low == -1.0.
         * \param[in] bias    Bias towards segments. No bias == 0.0, Bias towards first segment > 0.0, Bias towards second segment < 0.0
         *
         * \return Interpolated value. When frac == 0.0, returns from. When frac == 1.0f, returns to.
         */
        static float InterpolateHermite(float const before, float const from, float const to, float const after,
                                        float const frac, float const tension = 0.0f, float const bias = 0.0f)
        {
            float boundFrac = (frac < 0.0f) ? 0.0f : (frac > 1.0) ? 1.0f : frac;
            float frac2 = boundFrac * boundFrac;
            float frac3 = boundFrac * frac2;
            float m0 = ((from - before) * (1.0f + bias) * (1.0f - tension) * 0.5f)
                     + ((to - from)     * (1.0f - bias) * (1.0f - tension) * 0.5f);
            float m1 = ((to - from)     * (1.0f + bias) * (1.0f - tension) * 0.5f)
                     + ((after - to)    * (1.0f - bias) * (1.0f - tension) * 0.5f);
            float a0 = (2.0f * frac3) - (3.0f * frac2) + 1.0f;
            float a1 = frac3 - (2.0f * frac2) + boundFrac;
            float a2 = frac3 - frac2;
            float a3 = (-2.0f * frac3) + (3.0f * frac2);

            return (a0 * from) + (a1 * m0) + (a2 * m1) + (a3 * to);
        }
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