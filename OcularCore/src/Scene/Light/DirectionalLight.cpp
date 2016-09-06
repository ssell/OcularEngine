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

#include "Scene/Light/DirectionalLight.hpp"
#include "Scene/SceneObjectRegistrar.hpp"

#include "OcularEngine.hpp"


OCULAR_REGISTER_SCENEOBJECT(Ocular::Core::DirectionalLight, "Directional Light");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        DirectionalLight::DirectionalLight(std::string const& name, SceneObject* parent)
            : LightSource(name, parent, "Directional Light")
        {
            m_LightType = 3.0f;
            exposeProperties();
        }

        DirectionalLight::DirectionalLight()
            : LightSource("Directional Light", nullptr, "Directional Light")
        {
            m_LightType = 3.0f;
            exposeProperties();
        }

        DirectionalLight::~DirectionalLight()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void DirectionalLight::exposeProperties()
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}