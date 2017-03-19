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

#include "Scene/Light/GPULight.hpp"
#include "Scene/Light/LightSource.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        GPULight::GPULight()
            : parameters(Math::Vector4f(0.0f, 0.0f, 0.0f, 0.0f))
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void GPULight::operator()(LightSource const* light)
        {
            if(light)
            {
                position      = light->getPosition(false);
                direction     = -light->getTransform().getForwards().getNormalized();   // We want the direction to the light source
                color         = light->getColor();
                attenuation   = light->getAttenuation();
                attenuation.w = light->getRange();
                parameters.x  = light->getIntensity();
                parameters.y  = light->getAngle();
                parameters.z  = light->getLightType();
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}