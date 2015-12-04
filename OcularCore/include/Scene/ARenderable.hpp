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

#pragma once
#ifndef __H__OCULAR_CORE_SCENE_ARENDERABLE__H__
#define __H__OCULAR_CORE_SCENE_ARENDERABLE__H__

#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Material/Material.hpp"

#include <string>

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
        class SceneObject;

        /**
         * \class ARenderable
         */
        class ARenderable
        {
        public:

            ARenderable(std::string const& name, SceneObject* parent);
            virtual ~ARenderable();

            virtual bool initialize();

            virtual bool preRender();     ///< If returns FALSE, will cancel mesh rendering
            virtual void postRender();

            //------------------------------------------------------------
            // Getters and Setters

            SceneObject* getParent();
            void setParent(SceneObject* parent);

            Graphics::Mesh* getMesh();
            void setMesh(Graphics::Mesh* mesh);

            Graphics::Material* getMaterial();
            void setMaterial(Graphics::Material* material);

            std::string getName() const;
            void setName(std::string const& name);

        protected:

            std::string m_Name;

            SceneObject* m_Parent;

            Graphics::Mesh* m_Mesh;
            Graphics::Material* m_Material;

        private:
        };
    }
}

//------------------------------------------------------------------------------------------

#endif