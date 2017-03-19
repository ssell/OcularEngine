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
#ifndef __H__OCULAR_EDITOR_COMMON_DISPLAY__H__
#define __H__OCULAR_EDITOR_COMMON_DISPLAY__H__

#include "PropertiesDisplayBox.hpp"
#include "Widgets/Standard/CheckBox.hpp"

#include <QtWidgets/qframe.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

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
        class LineEdit;

        /**
         * \class CommonDisplay
         */
        class CommonDisplay : public PropertiesDisplayBox
        {
        public:

            CommonDisplay(QWidget* parent = nullptr);
            ~CommonDisplay();

            //------------------------------------------------------------

            virtual void setObject(Core::SceneObject* object) override;
            virtual void updateProperties() override;

        protected:
            
            void buildName();
            void buildTransform();

            //------------------------------------------------------------

            // Name / IsActive

            QHBoxLayout* m_NameActiveLayout;

            QLabel* m_LabelTransform;
            LineEdit* m_LineName;

            CheckBox* m_ActiveCheckBox;

            // Trnasform

            PropertyWidget* m_PropertyPosition;
            PropertyWidget* m_PropertyRotation;
            PropertyWidget* m_PropertyScale;

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