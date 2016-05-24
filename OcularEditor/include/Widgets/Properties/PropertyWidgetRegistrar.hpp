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
#ifndef __H__OCULAR_EDITOR_PROPERTY_WIDGET_REGISTRAR__H__
#define __H__OCULAR_EDITOR_PROPERTY_WIDGET_REGISTRAR__H__

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
        class PropertyWidgetRegistrar
        {
        public:

            PropertyWidgetRegistrar(std::string const& type)
            {
                if(!OcularEditor.getPropertyWidgetFactory().registerComponent<T>(type))
                {
                    OcularLogger->error("Failed to register PropertyWidget for type '", type, "' as the type is already in use",
                                         OCULAR_INTERNAL_LOG("PropertyWidgetRegistrar", "PropertyWidgetRegistrar"));
                }
            }

            ~PropertyWidgetRegistrar()
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

#define OCULAR_REGISTER_PROPERTY_WIDGET(X,Y) Ocular::Editor::PropertyWidgetRegistrar<X> OCULAR_INTERNAL_PropertyWidgetRegistrar(Y)

//------------------------------------------------------------------------------------------

#endif