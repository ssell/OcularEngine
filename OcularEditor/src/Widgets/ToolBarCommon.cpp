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
#include "Widgets/ToolbarCommon.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ToolbarCommon::ToolbarCommon(QWidget *parent)
            : QToolBar(parent)
        {
            setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
            setStyleSheet("QToolBar{ border: 1px solid rgb(27, 27, 28); background-color: rgb(56, 56, 60); } QToolButton { width: 50px; background-color: rgba(0, 0, 0, 0);}");

            addAction("Translate");
            addAction("Scale");
            addAction("Rotate");

            addSeparator();

            addAction("Wireframe");
            addAction("Normals");
            addAction("UVs");
        }

        ToolbarCommon::~ToolbarCommon()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ToolbarCommon::sizeHint() const
        {
            return QSize(50000, 30);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}