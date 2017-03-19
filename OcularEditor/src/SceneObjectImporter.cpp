/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "stdafx.h"
#include "SceneObjectImporter.hpp"

#include "Graphics/Mesh/MeshLoaders/OBJ/OBJImporter.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool SceneObjectImporter::Import(std::string const& filePath)
        {
            bool result = false;
            const Core::File file = Core::File(filePath);

            if(Utils::String::IsEqual(file.getExtension(), ".opre", true))
            {
                result = ImportOPRE(file);
            }
            else if(Utils::String::IsEqual(file.getExtension(), ".obj", true))
            {
                result = ImportOBJ(file);
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        bool SceneObjectImporter::ImportOPRE(Core::File const& file)
        {
            bool result = false;

            return result;
        }

        bool SceneObjectImporter::ImportOBJ(Core::File const& file)
        {
            bool result = false;
            const std::string mappingName = OcularResources->getResourceMappingName(file);

            if(mappingName.size())
            {
                result = (Graphics::OBJImporter::Import(mappingName) != nullptr);
            }
            else
            {
                OcularLogger->error("Failed to find associated Resource mapping name for '", file.getFullPath(), "'", OCULAR_INTERNAL_LOG("SceneObjectImporter", "ImportOBJ"));
            }
            
            return result;
        }
    }
}