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
#ifndef __H__OCULAR_EDITOR_COLOR_PROPERTY__H__
#define __H__OCULAR_EDITOR_COLOR_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/ButtonColorPicker.hpp"
#include "Widgets/Standard/ColorPreview.hpp"
#include "Math/Color.hpp"

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
         * \class ColorProperty
         *
         * Pre-built property display for Core::Color variables.
         */
        class ColorProperty : public PropertyWidget
        {
            Q_OBJECT

        public:

            ColorProperty(QWidget* parent = nullptr);
            virtual ~ColorProperty();

            virtual bool updateProperties() override;
            virtual void setValue(void* value, uint32_t size) override;
            virtual std::string getValue() const override;

        protected:

        private slots:

            void onColorPicked();

        private:

            ColorPreview* m_ColorPreview;
            ButtonColorPicker* m_ButtonColor;
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