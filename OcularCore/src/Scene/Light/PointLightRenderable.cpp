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

#include "Scene/Light/PointLightRenderable.hpp"
#include "OcularEngine.hpp"

// We do not register this renderable as it is not a 'public'
// renderable and is used only by the PointLight class.

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PointLightRenderable::PointLightRenderable(std::string const& name, SceneObject* parent)
            : ARenderable(name, "PointLightRenderable", parent),
              m_ExtentsMaterial(nullptr),
              m_ExtentsMesh(nullptr)
        {

        }

        PointLightRenderable::~PointLightRenderable()
        {
            if(m_ExtentsMaterial)
            {
                delete m_ExtentsMaterial;
                m_ExtentsMaterial = nullptr;
            }

            if(m_ExtentsMesh)
            {
                delete m_ExtentsMesh;
                m_ExtentsMesh = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool PointLightRenderable::initialize()
        {
            bool result = true;

            return result;
        }

        bool PointLightRenderable::preRenderDebug()
        {
            bool result = true;

            return result;
        }

        void PointLightRenderable::renderDebug()
        {

        }

        void PointLightRenderable::postRenderDebug()
        {

        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool PointLightRenderable::buildExtentsMaterial()
        {
            bool result = false;

            return result;
        }

        bool PointLightRenderable::buildExtentsMesh()
        {
            bool result = false;

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}