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
#ifndef __H__OCULAR_EDITOR_MULTI_PROPERTY__H__
#define __H__OCULAR_EDITOR_MULTI_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/LineEdit.hpp"

#include <vector>

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
         * \class MultiProperty
         *
         * Customizable property that displays a variable number of line edits.
         */
        class MultiProperty : public PropertyWidget
        {
        public:

            MultiProperty(QWidget* parent = nullptr);
            virtual ~MultiProperty();

            virtual bool updateProperties() override;

            /**
             * Adds a new property to be displayed on the right-side of the widget.
             * 
             * \param[in] name Text of the name label that is displayed to the left of the edit.
             * \param[in] type The type of line edit to create.
             *
             * \return The index of the new property. Used to later retrieve the label and/or the edit.
             */
            uint32_t addProperty(std::string const& name, LineType type);

            /**
             * Returns the label displayed to the left of the edit with the specified index.
             * \param[in] index Valid property index. Returns NULL if index is invalid.
             */
            QLabel* getLabel(uint32_t index);

            /**
             * Returns the edit with the specified index.
             * \param[in] index Valid property index. Returns NULL if index is invalid.
             */
            LineEdit* getLineEdit(uint32_t index);

            /** 
             * Returns the number of properties displayed
             */
            uint32_t getNumProperties() const;

        protected:

        private:

            std::vector<std::pair<QLabel*, LineEdit*>> m_Properties;
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