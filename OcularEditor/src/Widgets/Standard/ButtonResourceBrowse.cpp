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

#include "stdafx.h"
#include "Widgets/Standard/ButtonResourceBrowse.hpp"
#include "Widgets/Properties/SelectResourceDialog.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        ButtonResourceBrowse::ButtonResourceBrowse(QWidget* parent)
            : QPushButton(parent),
              m_WasEdited(false),
              m_Type(Core::ResourceType::Undefined)
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

            setText("...");
            connect(this, SIGNAL(clicked()), this, SLOT(onButtonClick()));
        }

        ButtonResourceBrowse::~ButtonResourceBrowse()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ButtonResourceBrowse::sizeHint() const
        {
            return QSize(50, 0);
        }

        bool ButtonResourceBrowse::wasEdited(bool reset)
        {
            bool result = m_WasEdited;

            if(reset)
            {
                m_WasEdited = false;
            }

            return result;
        }

        void ButtonResourceBrowse::setResourceType(Core::ResourceType const type)
        {
            m_Type = type;
        }

        std::string const& ButtonResourceBrowse::getSelectedResource() const
        {
            return m_SelectedResource;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ButtonResourceBrowse::onButtonClick()
        {
            SelectResourceDialog dialog(m_Type);

            if(dialog.exec())
            {
                m_SelectedResource = dialog.getSelectedName();
                m_WasEdited = true;
            }
        }
    }
}