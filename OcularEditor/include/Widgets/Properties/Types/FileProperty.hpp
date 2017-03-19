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
#ifndef __H__OCULAR_EDITOR_FILE_PROPERTY__H__
#define __H__OCULAR_EDITOR_FILE_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/LineEdit.hpp"
#include "Widgets/Standard/ButtonFileBrowse.hpp"

#include <string>

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
        /**
         * \class FileProperty
         *
         * Pre-built property display for Core::File variables.
         */
        class FileProperty : public PropertyWidget
        {
        public:

            FileProperty(QWidget* parent = nullptr);
            virtual ~FileProperty();

            virtual bool updateProperties() override;

            /**
             * \param[in] value Expects a std::string with the file path.
             * \param[in] size  Unused in this implementation
             */
            virtual void setValue(void* value, uint32_t size = 0) override;
            virtual std::string getValue() const override;

        protected:

        private:

            LineEdit* m_LineValue;
            ButtonFileBrowse* m_ButtonBrowse;
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