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
#include "Widgets/Properties/CommonPropertiesDisplay.hpp"
#include "Utilities/VoidCast.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CommonPropertiesDisplay::CommonPropertiesDisplay(QWidget* parent)
            : QGroupBox("", parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            m_Layout = new QVBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->setContentsMargins(5, 5, 5, 5);

            m_LineName = new QLineEdit();
            m_LabelTransform = new QLabel("Transform");

            m_Layout->addWidget(m_LineName);
            m_Layout->addWidget(m_LabelTransform);

            setLayout(m_Layout);
        }

        CommonPropertiesDisplay::~CommonPropertiesDisplay()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize CommonPropertiesDisplay::sizeHint() const
        {
            return QSize(275, 150);
        }

        void CommonPropertiesDisplay::setObject(Core::SceneObject* object)
        {
            if(object)
            {
                Core::ExposedVariable variable;

                object->getVariable("m_Name", variable);
                m_LineName->setText(void_cast<std::string>(variable.data).c_str());
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}