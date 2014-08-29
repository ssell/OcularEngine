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
#ifndef __H__OCULAR_RENDERER_TEXTURE__H__
#define __H__OCULAR_RENDERER_TEXTURE__H__

#include "Object.hpp"
#include "TextureEnums.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \class Texture
     * \brief Base class for all texture objects
     */
    class Texture : public Object
    {
    public:

        /**
         * \param filter
         * \param usage
         * \param name
         */
        Texture(TEXTURE_FILTER_MODE filter = BILINEAR, TEXTURE_USAGE_MODE usage = STATIC, std::string name = "Texture");

        virtual ~Texture();

        /**
         * Applies the changes made to the texture. This uploads the newly modified texture to the GPU.<br/><br/>
         * Textures will not be updated (i.e. changes rendered) until this method is called.
         *
         * \note Texture usage mode must be set to ::DYNAMIC in order to modify a texture at runtime.
         */
        virtual void apply() = 0;

        /**
         * Sets the filter mode of the texture.<br/>
         * The filter mode determines how pixels are sampled during rendering.<br/><br/>
         *
         * The default filter is ::BILINEAR.
         *
         * \param filter 
         */
        virtual void setFilterMode(TEXTURE_FILTER_MODE filter);

        /**
         * Sets the usage mode of the texture.<br/><br/>
         *
         * The usage mode determines if a copy of the texture is maintained on the CPU.
         * By setting usage to DYNAMIC, one may modify the texture at runtime. But this
         * also requires additional memory overhead which is unnecessary for most textures.<br/><br/>
         * 
         * The default usage is STATIC.
         */
        virtual void setUsageMode(TEXTURE_USAGE_MODE usage);

    protected:

        TEXTURE_FILTER_MODE m_Filter;
        TEXTURE_USAGE_MODE  m_Usage;

    private:
    };
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif