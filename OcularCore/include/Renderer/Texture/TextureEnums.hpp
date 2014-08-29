/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_RENDERER_TEXTURE_ENUMS__H__
#define __H__OCULAR_RENDERER_TEXTURE_ENUMS__H__

//------------------------------------------------------------------------------------------

/*!
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /*! Sample filtering modes */
    enum TEXTURE_FILTER_MODE 
    {
        POINT = 0x0,     ///< Use Point filtering
        BILINEAR,        ///< Use Bilinear filtering
        TRILINEAR,       ///< Use Trilinear filtering
        ANISOTROPIC      ///< Use Anisotropic filtering
    };

    enum TEXTURE_USAGE_MODE
    {
        STATIC = 0x0,    ///< Texture will not be updated at runtime
        DYNAMIC          ///< Texture may be updated at runtime
    };
}

//------------------------------------------------------------------------------------------

#endif