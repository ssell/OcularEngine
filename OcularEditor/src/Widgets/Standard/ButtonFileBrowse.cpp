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
#include "Widgets/Standard/ButtonFileBrowse.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        ButtonFileBrowse::ButtonFileBrowse(QWidget* parent)
            : QPushButton(parent),
              m_WasEdited(false),
              m_FilterString("Any File (*)")
        {
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

            setText("...");
            connect(this, SIGNAL(clicked()), this, SLOT(onButtonClick()));
        }

        ButtonFileBrowse::~ButtonFileBrowse()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ButtonFileBrowse::sizeHint() const
        {
            return QSize(50, 0);
        }

        bool ButtonFileBrowse::wasEdited(bool reset)
        {
            bool result = m_WasEdited;

            if(reset)
            {
                m_WasEdited = false;
            }

            return result;
        }

        void ButtonFileBrowse::setNameFilter(std::string const& filter)
        {
            m_FilterString = filter;
        }

        std::string const& ButtonFileBrowse::getSelectedFile() const
        {
            return m_SelectedFile;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ButtonFileBrowse::onButtonClick()
        {
            m_SelectedFile = QFileDialog::getOpenFileName(this, tr("Select File"), OcularResources->getSourceDirectory().c_str(), m_FilterString.c_str()).toStdString();
            m_WasEdited = true;
        }
    }
}