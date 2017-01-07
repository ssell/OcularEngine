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
#include "Scene/Light/PointLightRenderable.hpp"
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
            
            setRenderable(new PointLightRenderable());
        }

        PointLight::PointLight()
            : LightSource("Point Light", nullptr, "Point Light")
        {
            m_LightType = 1.0f;
            exposeProperties();

            setRenderable(new PointLightRenderable());
        }

        PointLight::~PointLight()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void PointLight::onVariableModified(std::string const& varName)
        {
            LightSource::onVariableModified(varName);

            if(Utils::String::IsEqual(varName, "m_Range"))
            {
                updateBounds(1);
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void PointLight::exposeProperties()
        {
            OCULAR_EXPOSE(m_Color);
            OCULAR_EXPOSE(m_Intensity);
            OCULAR_EXPOSE(m_Range);
            OCULAR_EXPOSE(m_Attenuation);
        }

        void PointLight::updateBounds(uint32_t const dirtyFlags)
        {
            if(dirtyFlags)
            {
                const Math::Vector3f position = getPosition(false);

                // We use a minimal bounding volume.

                // The range is what is used to determine if the lighting affects
                // the scene in the LightMananger.

                m_BoundsSphereWorld.setCenter(position);
                m_BoundsSphereWorld.setRadius(0.5f);

                m_BoundsAABBWorld.setCenter(position);
                m_BoundsAABBWorld.setExtents(Math::Vector3f(0.5f, 0.5f, 0.5f));

                OcularScene->triggerObjectDirty(m_UUID, isStatic());

                for(auto child : m_Children)
                {
                    child->updateBounds(dirtyFlags);
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}