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
#ifndef __H__OCULAR_GRAPHICS_MATERIAL_RESOURCE_SAVER__H__
#define __H__OCULAR_GRAPHICS_MATERIAL_RESOURCE_SAVER__H__

#include "Resources/ResourceSaver.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        class ShaderProgram;

        /**
         * \class MaterialResourceSaver
         * \brief Saves a Material object to an Ocular Material file (.omat)
         */
        class MaterialResourceSaver : public Core::AResourceSaver
        {
        public:

            MaterialResourceSaver();
            virtual ~MaterialResourceSaver();

            virtual bool saveResource(Core::Resource* resource, Core::File const& file) override;

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