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

        ARenderable::ARenderable(std::string const& name, SceneObject* parent)
            : m_Name(name),
              m_Parent(parent),
              m_Mesh(nullptr),
              m_Material(nullptr)
        {

        }

        ARenderable::~ARenderable()
        {
            m_Mesh = nullptr;        // Do not delete as meshes are shared
            m_Material = nullptr;    // Do not delete as materials are shared
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------
        // Getters and Setters
        //----------------------------------------------------------------

        SceneObject* ARenderable::getParent()
        {
            return m_Parent;
        }

        void ARenderable::setParent(SceneObject* parent)
        {
            if(parent && (parent != m_Parent))
            {
                if(m_Parent)
                {
                    m_Parent->removeRenderable(this, true);
                }

                m_Parent->addRenderable(this);
            }
        }

        Graphics::Mesh* ARenderable::getMesh() 
        {
            return m_Mesh;
        }

        void ARenderable::setMesh(Graphics::Mesh* mesh)
        {
            m_Mesh = mesh;
        }

        Graphics::Material* ARenderable::getMaterial()
        {
            return m_Material;
        }

        void ARenderable::setMaterial(Graphics::Material* material)
        {
            m_Material = material;
        }

        std::string ARenderable::getName() const
        {
            return m_Name;
        }

        void ARenderable::setName(std::string const& name)
        {
            m_Name = name;
        }

        bool ARenderable::preRender()
        {
            return true;
        }

        bool ARenderable::postRender()
        {
            return true;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}