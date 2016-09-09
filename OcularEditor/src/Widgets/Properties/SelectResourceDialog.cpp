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
#include "Widgets/Properties/SelectResourceDialog.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SelectResourceDialog::SelectResourceDialog(ResourceType const type, QWidget* parent)
            : QDialog(parent)
        {
            setStyleSheet(GeneralStyles::windowStyle);

            buildWidgets();
            populateTree(type);

            connect(m_ButtonSelect, SIGNAL(clicked()), this, SLOT(onFinished()));
        }

        SelectResourceDialog::SelectResourceDialog(Core::ResourceType const type, QWidget* parent)
            : QDialog(parent)
        {
            setStyleSheet(GeneralStyles::windowStyle);

            buildWidgets();
            populateTree(type);

            connect(m_ButtonSelect, SIGNAL(clicked()), this, SLOT(onFinished()));
        }

        SelectResourceDialog::~SelectResourceDialog()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        std::string const& SelectResourceDialog::getSelectedName() const
        {
            return m_ResourceName;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void SelectResourceDialog::buildWidgets()
        {
            m_LabelTitle = new QLabel();
            m_LabelTitle->setStyleSheet("QLabel { background-color: transparent; }");
            
            m_TreeResource = new QTreeWidget();
            m_TreeResource->setHeaderHidden(true);

            m_ButtonSelect = new QPushButton("Select");

            m_Layout = new QVBoxLayout();
            m_Layout->addWidget(m_LabelTitle);
            m_Layout->addWidget(m_TreeResource);
            m_Layout->addWidget(m_ButtonSelect);

            setLayout(m_Layout);
        }

        void SelectResourceDialog::populateTree(ResourceType const type)
        {
            std::vector<std::string> availableNames;

            switch(type)
            {
            case ResourceType::Renderable:
                m_LabelTitle->setText("Renderables");
                availableNames = OcularScene->getRenderableFactory().getRegisteredKeys();
                break;

            case ResourceType::Routine:
                m_LabelTitle->setText("Routines");
                availableNames = OcularScene->getRoutineFactory().getRegisteredKeys();
                break;

            default:
                break;
            }

            for(auto name : availableNames)
            {
                QTreeWidgetItem* item = new QTreeWidgetItem(m_TreeResource);
                item->setText(0, name.c_str());

                m_TreeResource->addTopLevelItem(item);
            }

            m_TreeResource->clearSelection();
            m_TreeResource->selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
        }

        void SelectResourceDialog::populateTree(Core::ResourceType const type)
        {
            std::vector<std::string> availableNames;
            OcularResources->getResourcesOfType(type, availableNames);

            for(auto name : availableNames)
            {
                QTreeWidgetItem* item = new QTreeWidgetItem(m_TreeResource);
                item->setText(0, name.c_str());

                m_TreeResource->addTopLevelItem(item);
                m_TreeResource->sortByColumn(0, Qt::SortOrder::AscendingOrder);
            }

            m_TreeResource->clearSelection();
            m_TreeResource->selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void SelectResourceDialog::onFinished()
        {
            auto items = m_TreeResource->selectedItems();

            if(items.size())
            {
                auto item = items[0];

                if(item)
                {
                    m_ResourceName = item->text(0).toStdString();
                }
            }

            accept();
        }
    }
}