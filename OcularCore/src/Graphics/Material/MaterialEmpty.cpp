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

#include "Graphics/Material/MaterialEmpty.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MaterialEmpty::MaterialEmpty()
            : Material()
        {
            setName("None");
            setMappingName("None");
        }

        MaterialEmpty::~MaterialEmpty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void MaterialEmpty::bind()
        {

        }

        void MaterialEmpty::unbind()
        {

        }

        void MaterialEmpty::unload()
        {
            // Intentionally left empty
        }

        void MaterialEmpty::onLoad(Core::BuilderNode const* node)
        {
            ObjectIO::onLoad(node);
        }

        void MaterialEmpty::onSave(Core::BuilderNode* node)
        {
            ObjectIO::onSave(node);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}