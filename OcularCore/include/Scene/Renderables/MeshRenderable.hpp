/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_CORE_SCENE_RENDERABLE_MESH__H__
#define __H__OCULAR_CORE_SCENE_RENDERABLE_MESH__H__

#include "Scene/ARenderable.hpp"

#include "Graphics/Mesh/Mesh.hpp"
#include "Graphics/Material/Material.hpp"

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
         * \class MeshRenderable
         *
         * Default generic renderable for simple mesh rendering.
         */
        class MeshRenderable : public ARenderable
        {
        public:

            MeshRenderable(std::string const& name = "MeshRenderable", SceneObject* parent = nullptr);
            virtual ~MeshRenderable();

            //------------------------------------------------------------
            // Inherited Methods

            virtual bool initialize() override;

            virtual bool preRender() override;
            virtual void render() override;

            //------------------------------------------------------------
            // Getters / Setters

            /**
             *
             */
            bool setMesh(std::string const& name);
            
            /**
             *
             */
            void setMesh(Graphics::Mesh* mesh);
            
            /**
             *
             */
            Graphics::Mesh* getMesh() const;
            
            /**
             *
             */
            bool setMaterial(std::string const& name);
            
            /**
             *
             */
            void setMaterial(Graphics::Material* material);
            
            /**
             *
             */
            Graphics::Material* getMaterial() const;

        protected:

            Graphics::Mesh* m_Mesh;
            Graphics::Material* m_Material;

        private:
        };
    }
}

//------------------------------------------------------------------------------------------

#endif