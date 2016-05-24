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
#include "Widgets/Properties/PropertyWidget.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        PropertyWidget::PropertyWidget(QWidget* parent)
            : QFrame(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setStyleSheet("QFrame { background-color: rgb(56, 56, 60); }");

            createLeftSide();
            createRightSide();
            createLayout();
        }

        PropertyWidget::~PropertyWidget()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize PropertyWidget::sizeHint() const
        {
            return QSize(275, 5);
        }

        bool PropertyWidget::updateProperties()
        {
            return false;
        }

        void PropertyWidget::setVariable(Core::ExposedVariable& variable)
        {
            m_Variable = variable;
        }
        
        void PropertyWidget::setDisplayName(std::string const& name)
        {
            m_DisplayName = name;
            m_LabelName->setText(name.c_str());
        }

        std::string const& PropertyWidget::getDisplayName() const
        {
            return m_DisplayName;
        }

        void PropertyWidget::addWidgetLeftSide(QWidget* widget)
        {
            m_LayoutLeft->addWidget(widget);
        }

        void PropertyWidget::addWidgetRightSide(QWidget* widget)
        {
            m_LayoutRight->addWidget(widget);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void PropertyWidget::createLeftSide()
        {
            m_LabelName = new QLabel(m_DisplayName.c_str());
            
            m_LayoutLeft = new QHBoxLayout();
            m_LayoutLeft->addWidget(m_LabelName);
            
            m_FrameLeftSide = new QFrame();
            m_FrameLeftSide->setLayout(m_LayoutLeft);
            m_FrameLeftSide->setFixedWidth(100);
        }

        void PropertyWidget::createRightSide()
        {
            m_LayoutRight = new QHBoxLayout();
            m_FrameRightSide = new QFrame();
            m_FrameRightSide->setLayout(m_LayoutRight);
        }

        void PropertyWidget::createLayout()
        {
            m_Layout = new QHBoxLayout();
            m_Layout->setContentsMargins(5, 0, 5, 0);
            m_Layout->addWidget(m_FrameLeftSide);
            m_Layout->addWidget(m_FrameRightSide);

            setLayout(m_Layout);
        }
    }
}