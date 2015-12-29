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

/**
 * Utility header that includes all core auto-register objects. This includes:
 *
 *     - Resource Loaders
 *     - Resource Savers
 *     - Routines
 *     - Renderables
 *
 * Under normal circumstances, these objects will correctly self-register with
 * their respective managers, factories, etc. This happens in parent executables
 * and in dynamic libraries.
 *
 * But, since Ocular Core is a static library, this does not happen. What happens
 * is that during compilation, the linker is throwing away our unreferenced static
 * objects, even if they have desireable behaviour. So, to keep them from being
 * tossed out, we have to create an explicit reference.
 *
 * For more information:
 *
 * https://social.msdn.microsoft.com/Forums/vstudio/en-US/2aa2e1b7-6677-4986-99cc-62f463c94ef3/linkexe-bug-optnoref-option-doesnt-work?forum=vclanguage
 * http://ofekshilon.com/2013/04/06/forcing-construction-of-global-objects-in-static-libraries/ (note: did not work)
 *
 * Hopefully a future C++ standard (C++17 reflection work?) will remove the need.
 * Until then, this header is required for the core library. 
 *
 * Note that this is not needed for any auto-register objects defined in 
 * dynamic libraries or the actual executable project/code.
 */

#pragma once
#ifndef __H__OCULAR_CORE_DYNAMIC_REGISTRATION__H__
#define __H__OCULAR_CORE_DYNAMIC_REGISTRATION__H__

#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_BMP.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_PNG.hpp"
#include "Graphics/Texture/TextureLoaders/TextureResourceLoader_TGA.hpp"
#include "Graphics/Texture/TextureSavers/TextureResourceSaver_BMP.hpp"
#include "Graphics/Texture/TextureSavers/TextureResourceSaver_PNG.hpp"

#include "Graphics/Material/MaterialResourceLoader.hpp"
#include "Graphics/Material/MaterialResourceSaver.hpp"

#include "Graphics/Mesh/MeshLoaders/PLY/MeshResourceLoader_PLY.hpp"
#include "Graphics/Mesh/MeshSavers/PLY/MeshResourceSaver_PLY.hpp"

namespace Ocular
{
    //--------------------------------------------------------------------------------------
    // Resource Loaders
    //--------------------------------------------------------------------------------------

    static const Graphics::TextureResourceLoader_BMP OCULAR_INTERNAL_RESOURCE_LOADER_TEXTURE_BMP;
    static const Graphics::TextureResourceLoader_PNG OCULAR_INTERNAL_RESOURCE_LOADER_TEXTURE_PNG;
    static const Graphics::TextureResourceLoader_TGA OCULAR_INTERNAL_RESOURCE_LOADER_TEXTURE_TGA;

    static const Graphics::MaterialResourceLoader OCULAR_INTERNAL_RESOURCE_LOADER_MATERIAL;

    static const Graphics::MeshResourceLoader_PLY OCULAR_INTERNAL_RESOURCE_LOADER_MESH_PLY;

    //--------------------------------------------------------------------------------------
    // Resource Savers
    //--------------------------------------------------------------------------------------

    static const Graphics::TextureResourceSaver_BMP OCULAR_INTERNAL_RESOURCE_SAVER_TEXTURE_BMP;
    static const Graphics::TextureResourceSaver_PNG OCULAR_INTERNAL_RESOURCE_SAVER_TEXTURE_PNG;

    //static const Graphics::MaterialResourceSaver OCULAR_INTERNAL_RESOURCE_SAVER_MATERIAL;

    static const Graphics::MeshResourceSaver_PLY OCULAR_INTERNAL_RESOURCE_SAVER_MESH_PLY;

    //--------------------------------------------------------------------------------------
    // Routines
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // Renderables
    //--------------------------------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    // Misc.
    //--------------------------------------------------------------------------------------
}

#endif