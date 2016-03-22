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

#include "stdafx.h"
#include "Widgets/Standard/ButtonColorPicker.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        ButtonColorPicker::ButtonColorPicker(QWidget* parent)
            : QPushButton(parent),
              m_WasEdited(false)
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

            setText("...");
            connect(this, SIGNAL(clicked()), this, SLOT(onButtonClick()));
        }

        ButtonColorPicker::~ButtonColorPicker()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ButtonColorPicker::sizeHint() const
        {
            return QSize(50, 0);
        }

        bool ButtonColorPicker::wasEdited(bool reset)
        {
            bool result = m_WasEdited;

            if(reset)
            {
                m_WasEdited = false;
            }

            return result;
        }

        Core::Color const& ButtonColorPicker::getSelectedColor() const
        {
            return m_SelectedColor;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ButtonColorPicker::onButtonClick()
        {
            m_QColor = QColorDialog::getColor(m_QColor, this, "Select Color", QColorDialog::ShowAlphaChannel);

            if(m_QColor.isValid())    // Returns false if the user canceled the action
            {
                //--------------------------------------------------------
                // Convert QColor to Ocular Color
                //--------------------------------------------------------

                qreal r = 0.0;
                qreal g = 0.0;
                qreal b = 0.0;
                qreal a = 0.0;

                m_QColor.getRgbF(&r, &g, &b, &a);

                m_SelectedColor = Core::Color(static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a));
                m_WasEdited = true;
            }
        }
    }
}