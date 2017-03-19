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

#pragma once
#ifndef __H__OCULAR_EDITOR_CUSTOM_DISPLAY_REGISTRAR__H__
#define __H__OCULAR_EDITOR_CUSTOM_DISPLAY_REGISTRAR__H__

#include "OcularEditor.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        template<class T>
        class CustomDisplayRegistrar
        {
        public:

            CustomDisplayRegistrar(std::string const& type)
            {
                if(!OcularEditor.getCustomDisplayFactory().registerComponent<T>(type))
                {
                    OcularLogger->error("Failed to register PropertiesDisplayBox for type '", type, "' as the type is already in use",
                                         OCULAR_INTERNAL_LOG("CustomDisplayRegistrar", "CustomDisplayRegistrar"));
                }
            }

            ~CustomDisplayRegistrar()
            {

            }

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

#define OCULAR_REGISTER_CUSTOM_DISPLAY(X,Y) Ocular::Editor::CustomDisplayRegistrar<X> OCULAR_INTERNAL_CustomDisplayRegistrar(Y)

//------------------------------------------------------------------------------------------

#endif