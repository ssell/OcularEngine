/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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
#ifndef __H__OCULAR_CORE_LIGHT_SOURCE__H__
#define __H__OCULAR_CORE_LIGHT_SOURCE__H__

#include "Scene/SceneObject.hpp"

#include "Math/Vector4.hpp"
#include "Math/Color.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class LightSource
         */
        class LightSource : public SceneObject
        {
        public:

            ~LightSource();

            /**
             * Sets the light source's color.
             * \param[in] color
             */
            void setColor(Core::Color const& color);

            /**
             * \return The color of the light source.
             */
            Color getColor() const;

            /**
             * Sets the light source's intensity. This is the amount of energy that it outputs in lumens.
             * \param[in] intensity
             */
            void setIntensity(float intensity);

            /**
             * \return The intensity of the light source. This is the amount of energy that it outputs in lumens.
             */
            float getIntensity() const;

            /**
             * Sets the light source's range. For point lights this is the radius. Not used by directional lights.
             * \param[in] range
             */
            void setRange(float range);

            /**
             * \return The range of the light source. For point lights this is the radius. Not used by directional lights.
             */
            float getRange() const;

            /**
             * Sets the angle at the source of the light. Used only by spot lights.
             * \param[in] angle Angle in degrees.
             */
            void setAngle(float angle);

            /**
             * \return The angle (degrees) at the source of the light. Used only by spot lights.
             */
            float getAngle() const;

            /**
             * \return 0 = none; 1 = point; 2 = spot; 3 = directional
             */
            float getLightType() const;

        protected:

            LightSource(std::string const& name, SceneObject* parent, std::string const& type);   // Protected as there should be no stand-alone light sources. Must be point, spot, etc.
            
            //------------------------------------------------------------

            Color m_Color;

            float m_Intensity;
            float m_Range;
            float m_Angle;             // Angle is stored internally as radians
            float m_LightType;

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
