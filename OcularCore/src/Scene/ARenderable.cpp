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

#include "Scene/ARenderable.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ARenderable::ARenderable(std::string const& name, std::string const& type, SceneObject* parent)
            : Object(name, type),
              m_Parent(parent)
        {
            if(m_Parent)
            {
                m_Parent->setRenderable(this);
            }
        }

        ARenderable::~ARenderable()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // Getters and Setters
        //----------------------------------------------------------------

        bool ARenderable::initialize()
        {
            return true;
        }

        bool ARenderable::preRender()
        {
            return true;
        }

        void ARenderable::render()
        {

        }

        void ARenderable::postRender()
        {

        }

        void ARenderable::updateBounds()
        {

        }

        SceneObject* ARenderable::getParent() const
        {
            return m_Parent;
        }

        std::string const& ARenderable::getName() const
        {
            return m_Name;
        }

        uint32_t ARenderable::getRenderPriority() const
        {
            return static_cast<uint32_t>(RenderPriority::Opaque);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}