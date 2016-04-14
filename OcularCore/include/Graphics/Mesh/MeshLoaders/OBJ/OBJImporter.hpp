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
#ifndef __H__OCULAR_GRAPHICS_MESH_OBJ_IMPORTER__H__
#define __H__OCULAR_GRAPHICS_MESH_OBJ_IMPORTER__H__

#include <string>
#include <vector>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class SceneObject;
    }

    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class OBJImporter
         *
         * \note !!! Need to rewrite this as it just repeats itself
         *
         * OBJ files are handled differently from other mesh files such as PLY. 
         * This is because a single OBJ file may define multiple individual meshes within
         * it, as well as specifying the materials (found in an accompanying .mat) that it uses.
         *
         * Because of this, loading in an entire OBJ file does not create a single resource.
         * Instead, it creates multiple SceneObjects which then contain the renderables for
         * the described meshes and materials.
         *
         * In addition to loading in an entire OBJ to a group of SceneObjects, one may query
         * for the individual meshes defined within the file and use those separately.
         *
         * For example, if we have an OBJ at
         *
         *    Resources/
         *        Meshes/
         *            SomeModel.obj
         *
         * Which contains the following two meshes: pCube1 and pSphere1; we can retrieve the
         * individual meshes using:
         *
         *    OcularResources->getResource("Meshes/SomeModel/pCube1");
         *    OcularResources->getResource("Meshes/SomeModel/pSphere1");
         *
         * The actual OBJ file can be used in two different ways. If requested by the Resources
         * system, it will return a MultiResource which describes the contained meshes.
         *
         *    OcularResources->getResource<MultiResource>("Meshes/SomeModel");
         *
         * Alternatively, this OBJImporter class can be used to import the OBJ in SceneObjects.
         *
         *    SceneObject* parent = OBJImporter::Import("Meshes/SomeModel");
         *
         * Which would create the following SceneObject hierarchy:
         *
         *    SceneObject: SomeModel
         *       Child SceneObject: pCube1
         *           MeshRenderable
         *       Child SceneObject: pSphere1
         *           MeshRenderable
         */
        class OBJImporter
        {
        public:

            /**
             * Creates a new SceneObject hierarchy from the specified OBJ file. 
             *
             * The SceneObject will be added to the active scene as a top-level object (no parent).
             *
             * The returned object's name will match that of the filename and will have a child
             * object for each mesh found within the OBJ.
             *
             * \param[in] path The resource mapping path of the file (path relative to Resource folder, sans extension)
             *
             * \return May return NULL if unable to parse the OBJ file.
             */
            static Core::SceneObject* Import(std::string const& path);

            /**
             * Discovers all of the names of the meshes described within the specified OBJ file.
             *
             * \param[in] path  The resource mapping path of the file (path relative to Resource folder, sans extension)
             * \param[in] names Container of all mesh names found within the OBJ file
             *
             * \return May return FALSE if unable to parse the OBJ file.
             */
            static bool FindMeshes(std::string const& path, std::vector<std::string>& names);

        protected:

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif