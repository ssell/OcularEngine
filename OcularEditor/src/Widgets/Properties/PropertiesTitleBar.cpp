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
#include "Widgets/Properties/PropertiesDisplayTitleBar.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PropertiesDisplayTitleBar::PropertiesDisplayTitleBar(std::string const& displayName, bool canMinimize, bool canClose, QWidget* parent)
            : QFrame(parent),
              m_CanMinimize(canMinimize),
              m_CanClose(canClose)
        {
            setStyleSheet("QFrame { background-color: rgb(27, 27, 28); color: rgb(255, 255, 255); border: 0px solid rgb(27, 27, 28); }");
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

            buildLayout();
            buildTitleBar();

            setTitle(displayName);
        }

        PropertiesDisplayTitleBar::~PropertiesDisplayTitleBar()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize PropertiesDisplayTitleBar::sizeHint() const
        {
            return QSize(275, 15);
        }

        void PropertiesDisplayTitleBar::setTitle(std::string const& title)
        {
            m_LabelTitle->setText(title.c_str());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void PropertiesDisplayTitleBar::buildLayout()
        {
            m_Layout = new QHBoxLayout();
            m_Layout->setAlignment(Qt::AlignTop);
            m_Layout->setContentsMargins(5, 2, 5, 2);

            setLayout(m_Layout);
        }

        void PropertiesDisplayTitleBar::buildTitleBar()
        {
            m_ButtonMinimize = new QPushButton("-");
            m_ButtonClose = new QPushButton("X");
            m_LabelTitle = new QLabel("...");

            m_ButtonMinimize->setFixedSize(20, 10);
            m_ButtonClose->setFixedSize(20, 10);
            
            std::string stylesheet = 
                "QPushButton { background-color: transparent; }"
                "QPushButton:hover { color: rgb(224, 62, 37); }"
                "QPushButton:pressed { color: rgb(224, 62, 37); }";

            m_ButtonMinimize->setStyleSheet(stylesheet.c_str());
            m_ButtonClose->setStyleSheet(stylesheet.c_str());

            m_Layout->addWidget(m_LabelTitle);
            m_Layout->addWidget(m_ButtonMinimize);
            m_Layout->addWidget(m_ButtonClose);

            if(!m_CanMinimize)
            {
                m_ButtonMinimize->hide();
            }

            if(!m_CanClose)
            {
                m_ButtonClose->hide();
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}