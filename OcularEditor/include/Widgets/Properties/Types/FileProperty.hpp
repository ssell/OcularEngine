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

#pragma once
#ifndef __H__OCULAR_EDITOR_FILE_PROPERTY__H__
#define __H__OCULAR_EDITOR_FILE_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/LineEdit.hpp"
#include "Widgets/Standard/ButtonFileBrowse.hpp"

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
         * Pre-built property display for file variables.
         */
        class FileProperty : public PropertyWidget
        {
        public:

            FileProperty(QWidget* parent = nullptr);
            virtual ~FileProperty();

            virtual bool updateProperties() override;

            /**
             * See QFileDialog::setNameFilter
             */
            void setNameFilter(std::string const& filter);

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