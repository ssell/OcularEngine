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
#include "Widgets/SceneBox.hpp"
#include "Widgets/SceneTree.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneBox::SceneBox(QWidget *parent)
            : QGroupBox("Scene", parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            m_SceneTree = new SceneTree();

            m_Layout = new QVBoxLayout();
            m_Layout->addWidget(m_SceneTree);
            m_Layout->setContentsMargins(1, 25, 1, 5);

            setLayout(m_Layout);
        }

        SceneBox::~SceneBox()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize SceneBox::sizeHint() const
        {
            return QSize(275, 500);
        }

        SceneTree* SceneBox::getSceneTree() const
        {
            return m_SceneTree;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}