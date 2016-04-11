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

#include "CoreDynamicRegistration.hpp"

#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_BMP.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_PNG.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_TGA.hpp"
#include "Graphics/Texture/TextureSavers/TextureResourceSaver_BMP.hpp"
#include "Graphics/Texture/TextureSavers/TextureResourceSaver_PNG.hpp"

#include "Graphics/Mesh/MeshLoaders/PLY/MeshResourceLoader_PLY.hpp"
#include "Graphics/Mesh/MeshLoaders/OBJ/ResourceLoader_OBJ.hpp"
#include "Graphics/Mesh/MeshSavers/PLY/MeshResourceSaver_PLY.hpp"

#include "Graphics/Material/MaterialResourceLoader.hpp"
#include "Graphics/Material/MaterialResourceSaver.hpp"

#include "Scene/Routines/FreeFlyController.hpp"
#include "Scene/Renderables/MeshRenderable.hpp"

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    //--------------------------------------------------------------------------------------
    // CONSTRUCTORS
    //--------------------------------------------------------------------------------------

    CoreDynamicRegistration::CoreDynamicRegistration()
    {
        Graphics::TextureResourceLoader_BMP TextureResourceLoader_BMP;
        Graphics::TextureResourceLoader_PNG TextureResourceLoader_PNG;
        Graphics::TextureResourceLoader_TGA TextureResourceLoader_TGA;
        Graphics::MeshResourceLoader_PLY MeshResourceLoader_PLY;
        Graphics::ResourceLoader_OBJ ResourceLoader_OBJ;

        Graphics::TextureResourceSaver_BMP TextureResourceSaver_BMP;
        Graphics::TextureResourceSaver_PNG TextureResourceSaver_PNG;
        Graphics::MeshResourceSaver_PLY MeshResourceSaver_PLY;

        Graphics::MaterialResourceLoader MaterialResourceLoader;
        Graphics::MaterialResourceSaver MaterialResourceSaver;

        Core::FreeFlyController FreeFlyController;
        Core::MeshRenderable MeshRenderable;
        
        Math::Vector2f::OCULAR_INTERNAL_Force = true;
        Math::Vector3f::OCULAR_INTERNAL_Force = true;
        Math::Vector4f::OCULAR_INTERNAL_Force = true;
    }

    CoreDynamicRegistration::~CoreDynamicRegistration()
    {
    
    }

    //--------------------------------------------------------------------------------------
    // PUBLIC METHODS
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // PROTECTED METHODS
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // PRIVATE METHODS
    //--------------------------------------------------------------------------------------
}