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

#include "stdafx.h"
#include "Widgets/Properties/PropertiesDisplayBox.hpp"
#include "Widgets/Properties/PropertiesDisplayTitleBar.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PropertiesDisplayBox::PropertiesDisplayBox(std::string const& displayName, bool canMinimize, bool canClose, QWidget* parent)
            : QFrame(parent),
              m_Object(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            setStyleSheet("QGroupBox{ border: 0px solid black; }");

            buildLayout();
            buildTitleBar(displayName, canMinimize, canClose);

            setTitle(displayName);
        }

        PropertiesDisplayBox::~PropertiesDisplayBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize PropertiesDisplayBox::sizeHint() const
        {
            return QSize(275, 50);
        }

        void PropertiesDisplayBox::setTitle(std::string const& title)
        {
            m_TitleBar->setTitle(title);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void PropertiesDisplayBox::buildLayout()
        {
            m_Layout = new QVBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->setContentsMargins(0, 5, 0, 5);

            setLayout(m_Layout);
        }

        void PropertiesDisplayBox::buildTitleBar(std::string const& displayName, bool canMinimize, bool canClose)
        {
            m_TitleBar = new PropertiesDisplayTitleBar(displayName, canMinimize, canClose);
            m_Layout->addWidget(m_TitleBar);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}