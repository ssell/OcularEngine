/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "Scene/Light/LightSource.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        LightSource::LightSource(std::string const& name, SceneObject* parent, std::string const& type)
            : SceneObject(name, parent, type),
              m_Intensity(1.0f),
              m_Range(10.0f),
              m_Attenuation(Math::Vector3f(1.0f, 0.0f, 0.01f)),
              m_Angle(0.0f),
              m_Color(Color::White()),
              m_LightType(0.0f)
        {
            OcularLights->registerLightSource(this);
        }

        LightSource::~LightSource()
        {
            OcularLights->unregisterLightSource(this);
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void LightSource::onLoad(BuilderNode const* node)
        {
            const UUID old = m_UUID;

            SceneObject::onLoad(node);

            if(old != m_UUID)
            {
                OcularLights->updateUUID(old);
            }
        }

        void LightSource::setColor(Core::Color const& color)
        {
            m_Color = color;
        }

        Color LightSource::getColor() const
        {
            return m_Color;
        }

        void LightSource::setIntensity(float const intensity)
        {
            m_Intensity = intensity;
        }

        float LightSource::getIntensity() const
        {
            return m_Intensity;
        }

        void LightSource::setRange(float const range)
        {
            m_Range = range;
        }

        float LightSource::getRange() const
        {
            return m_Range;
        }

        void LightSource::setAngle(float const angle)
        {
            m_Angle = Math::DegreesToRadians(angle);
        }

        float LightSource::getAngle() const
        {
            return Math::RadiansToDegrees(m_Angle);
        }

        void LightSource::setAttenuation(Math::Vector3f const& attenuation)
        {
            m_Attenuation = attenuation;
        }

        Math::Vector3f LightSource::getAttenuation() const
        {
            return m_Attenuation;
        }

        float LightSource::getLightType() const
        {
            return m_LightType;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}