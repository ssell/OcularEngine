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

#include "Scene/Light/PointLight.hpp"
#include "Scene/SceneObjectRegistrar.hpp"

#include "OcularEngine.hpp"

OCULAR_REGISTER_SCENEOBJECT(Ocular::Core::PointLight, "Point Light");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        PointLight::PointLight(std::string const& name, SceneObject* parent)
            : LightSource(name, parent, "Point Light")
        {
            m_LightType = 1.0f;
            exposeProperties();
        }

        PointLight::PointLight()
            : LightSource("Point Light", nullptr, "Point Light")
        {
            m_LightType = 1.0f;
            exposeProperties();
        }

        PointLight::~PointLight()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void PointLight::exposeProperties()
        {
            exposeVariable("Color", Utils::TypeName<Core::Color>::name, false, true, &m_Color);
            exposeVariable("Intensity", Utils::TypeName<float>::name, false, true, &m_Intensity);
            exposeVariable("Range", Utils::TypeName<float>::name, false, true, &m_Range);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}