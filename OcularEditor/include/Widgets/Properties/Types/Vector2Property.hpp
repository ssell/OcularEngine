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
#ifndef __H__OCULAR_EDITOR_VECTOR2_PROPERTY__H__
#define __H__OCULAR_EDITOR_VECTOR2_PROPERTY__H__

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
         * \class Vector2Property
         *
         * Pre-built property display for Vector2f variables.
         */
        class Vector2Property : public PropertyWidget
        {
        public:

            Vector2Property(QWidget* parent = nullptr);
            virtual ~Vector2Property();

            virtual bool updateProperties() override;

            /**
             * \param[in] value Expected as a Math::Vector2f
             */
            virtual void setValue(void* value, uint32_t size) override;

            QLabel* m_LabelX;
            QLabel* m_LabelY;

            LineEdit* m_EditX;
            LineEdit* m_EditY;

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