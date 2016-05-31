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

#pragma once
#ifndef __H__OCULAR_CORE_SCENE_RENDERABLE_MESH__H__
#define __H__OCULAR_CORE_SCENE_RENDERABLE_MESH__H__

#include "Scene/ARenderable.hpp"

#include <vector>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Graphics
    {
        class Mesh;
        class Material;
    }

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
         *
         * A combination of a single Mesh with one or more Materials. 
         *
         * If the Mesh has multiple SubMeshes, then each SubMesh will be rendered with the associated  
         * Material (the first SubMesh will be rendered with material at index 0, second SubMesh with 
         * material at index 1, etc.).
         *
         * If there are more SubMeshes than Materials, then the last bound Material will be used for 
         * any additional SubMeshes. If there are more Materials than SubMeshes, then the extra Materials 
         * will never be used.
         * 
         * Specifying NULL as a Material is valid for this renderable and it disables rendering of 
         * any associated SubMeshes. 
         */
        class MeshRenderable : public ARenderable
        {
        public:

            MeshRenderable(std::string const& name = "MeshRenderable", SceneObject* parent = nullptr);
            virtual ~MeshRenderable();

            //------------------------------------------------------------
            // Inherited Methods
            //------------------------------------------------------------

            virtual bool initialize() override;

            virtual bool preRender() override;
            virtual void render() override;

            virtual void onLoad(BuilderNode const* node) override;
            virtual void onSave(BuilderNode* node) override;

            virtual void updateBounds() override;

            //------------------------------------------------------------
            // Mesh Methods
            //------------------------------------------------------------

            /**
             * Sets the Mesh to be rendered.
             * \param[in] name The mapping-name of the Mesh resource to render.
             */
            bool setMesh(std::string const& name);
            
            /**
             * Sets the Mesh to be rendered.
             * \param[in] mesh Pointer to the Mesh resource to render. May be NULL.
             */
            void setMesh(Graphics::Mesh* mesh);
            
            /**
             * Returns the Mesh currently being rendered.
             * \return Pointer to the rendered Mesh. May be NULL.
             */
            Graphics::Mesh* getMesh() const;
            
            //------------------------------------------------------------
            // Material Methods
            //------------------------------------------------------------

            /**
             * Adds a new Material.
             *
             * \param[in] name The mapping-name of the Material resource.
             * \return Index assigned to the new Material
             */
            uint32_t addMaterial(std::string const& name);

            /**
             * Adds a new Material.
             *
             * \param[in] material Pointer to the Material resource. May be NULL.
             * \return Index assigned to the new Material
             */
            uint32_t addMaterial(Graphics::Material* material);
            
            /**
             * Sets the Material at the specified index.
             *
             * If an invalid name is specified, then any associated SubMeshes will not be rendered.
             * 
             * \param[in] name  The mapping-name of the Material resource.
             * \param[in] index The index to place the Material at. 
             * \param[in] resize If true, will add NULL Materials to the Material container until the specified index is valid.
             */
            bool setMaterial(std::string const& name, uint32_t index = 0, bool resize = false);
            
            /**
             * Sets the Material at the specified index.
             *
             * If NULL is passed, then any associated SubMeshes will not be rendered.
             * 
             * \param[in] material Pointer to the Material resource. May be NULL.
             * \param[in] index    The index to place the Material at. 
             * \param[in] resize If true, will add NULL Materials to the Material container until the specified index is valid.
             */
            void setMaterial(Graphics::Material* material, uint32_t index = 0, bool resize = false);

            /**
             * Removes the Material at the specified index.
             *
             * This completely deletes the Material from the Renderable.
             * You may use setMaterial to set it NULL instead if that is more desireable.
             *
             * \param[in] index
             */
            void removeMaterial(uint32_t index);
            
            /**
             * Retrieves the material assigned to the specific index.
             *
             * \param[in] index
             * \return Pointer to specified Material. May be NULL.
             */
            Graphics::Material* getMaterial(uint32_t index = 0) const;

            /**
             * \return The number of stored Materials. This includes any Materials set to NULL.
             */
            uint32_t getNumMaterials() const;

        protected:

            //------------------------------------------------------------

            Graphics::Mesh* m_Mesh;
            std::vector<Graphics::Material*> m_Materials;

        private:
        };
    }
}

//------------------------------------------------------------------------------------------

#endif