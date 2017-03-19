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
#include "Widgets/ContentFrame.hpp"
#include "Widgets/RenderFrame.hpp"
#include "Widgets/SceneFrame.hpp"
#include "Widgets/SceneTree.hpp"
#include "Widgets/DetailsFrame.hpp"
#include "Widgets/PropertiesPanel.hpp"

#include <QtWidgets/qboxlayout.h>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ContentFrame::ContentFrame(QWidget *parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
            setLineWidth(1);
            
            m_LayoutContent = new QHBoxLayout();

            m_SceneFrame = new SceneFrame();
            m_RenderFrame = new RenderFrame();
            m_DetailsFrame = new DetailsFrame();
            
            m_pSplitter = new QSplitter();
            m_pSplitter->addWidget(m_SceneFrame);
            m_pSplitter->addWidget(m_RenderFrame);
            m_pSplitter->addWidget(m_DetailsFrame);
            m_pSplitter->setStretchFactor(1, 1);     // When window is resized, the render frame will take the majority of the stretch difference
                                                     // leaving the other two frames relatively the same size
            m_LayoutContent->addWidget(m_pSplitter);

            setLayout(m_LayoutContent);
            setContentsMargins(0, 0, 0, 0);
        }

        ContentFrame::~ContentFrame()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ContentFrame::sizeHint() const
        {
            // Some arbitrarily large size so that the frame always exapnds to fill all available space
            return QSize(99999, 99999);
        }

        void ContentFrame::update()
        {
            m_DetailsFrame->getPropertiesPanel()->update();
            m_SceneFrame->getSceneTree()->update();
        }

        PropertiesPanel* ContentFrame::getPropertiesPanel() const
        {
            return m_DetailsFrame->getPropertiesPanel();
        }

        SceneFrame* ContentFrame::getSceneFrame() const
        {
            return m_SceneFrame;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}