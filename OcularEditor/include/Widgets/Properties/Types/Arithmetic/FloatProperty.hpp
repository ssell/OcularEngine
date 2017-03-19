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
#ifndef __H__OCULAR_EDITOR_FLOAT_PROPERTY__H__
#define __H__OCULAR_EDITOR_FLOAT_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/LineEdit.hpp"

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
         * \class FloatProperty
         *
         * Pre-built property display for 32-bit floating point value.
         */
        class FloatProperty : public PropertyWidget
        {
        public:

            FloatProperty(QWidget* parent = nullptr);
            virtual ~FloatProperty();

            virtual bool updateProperties() override;
            virtual void setValue(void* value, uint32_t size) override;
            virtual std::string getValue() const override;

            LineEdit* getLineEdit();

        protected:

        private:

            LineEdit* m_EditValue;
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