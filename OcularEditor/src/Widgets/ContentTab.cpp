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
#include "Widgets/ContentTab.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ContentTab::ContentTab(QWidget *parent)
            : QTabWidget(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setMinimumSize(QSize(250, 700));

            createTabs();
        }

        ContentTab::~ContentTab()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ContentTab::sizeHint() const
        {
            return QSize(250, 700);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void ContentTab::createTabs()
        {
            m_ObjectTab = new QFrame();
            m_SceneTreeTab = new QFrame();

            addTab(m_ObjectTab, "Object Properties");
            addTab(m_SceneTreeTab, "Scene Tree");
        }
    }
}