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
#include "Widgets/SceneTree.hpp"
#include "Widgets/SceneTreeItem.hpp"
#include "Events/Events/SceneObjectAddedEvent.hpp"
#include "Events/Events/SceneObjectRemovedEvent.hpp"
#include "Events/SceneObjectSelectedEvent.hpp"
#include "Routines/EditorCameraController.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneTree::SceneTree(QWidget *parent)
            : QTreeWidget(parent)
        {
            OcularEvents->registerListener(this, Core::Priority::Medium);

            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setSelectionMode(QAbstractItemView::SelectionMode::ContiguousSelection);
            setContextMenuPolicy(Qt::CustomContextMenu);

            setHeaderHidden(true);
            setColumnCount(2);           // First column is object name; Second is object UUID
            setColumnHidden(1, true);

            connect(this, SIGNAL(customContextMenuRequested(QPoint const&)), this, SLOT(onShowContextMenu(QPoint const&)));
        }

        SceneTree::~SceneTree()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize SceneTree::sizeHint() const
        {
            return QSize(275, 500);
        }

        SceneTreeItem* SceneTree::getItem(Core::SceneObject* object)
        {
            SceneTreeItem* result = nullptr;
            
            if(object)
            {
                // The second (hidden) column for our items is the UUID string, so search for items matching that data
                auto items = findItems(QString(object->getUUID().toString().c_str()), Qt::MatchFlag::MatchExactly, 1);

                if(items.size() > 0)
                {
                    result = dynamic_cast<SceneTreeItem*>(items[0]);
                }
            }

            return result;
        }

        SceneTreeItem* SceneTree::getItem(Core::UUID const& uuid)
        {
            SceneTreeItem* result = nullptr;

            // The second (hidden) column for our items is the UUID string, so search for items matching that data
            auto items = findItems(QString(uuid.toString().c_str()), Qt::MatchFlag::MatchExactly, 1);

            if(items.size() > 0)
            {
                result = dynamic_cast<SceneTreeItem*>(items[0]);
            }

            return result;
        }

        void SceneTree::addObject(Core::SceneObject* object)
        {
            if(!isObjectTracked(object))
            {
                Core::SceneObject* parent = object->getParent();

                if(parent)
                {
                    SceneTreeItem* parentItem = getItem(parent);

                    if(parentItem)
                    {
                        SceneTreeItem* item = new SceneTreeItem(parentItem, object);
                    }
                    else
                    {
                        SceneTreeItem* item = new SceneTreeItem(this, object);
                        OcularLogger->warning("Unexpected SceneTreeItem ancestry", OCULAR_INTERNAL_LOG("Editor::SceneTree", "addObject"));
                    }
                }
                else
                {
                    SceneTreeItem* item = new SceneTreeItem(this, object);
                }
            }
        }

        void SceneTree::removeObject(Core::UUID const& uuid)
        {
            auto item = getItem(uuid);

            if(item)
            {
                delete item;
            }
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void SceneTree::mousePressEvent(QMouseEvent* event)
        {
            QTreeWidget::mousePressEvent(event);

            if(event)
            {
                SceneTreeItem* item = dynamic_cast<SceneTreeItem*>(itemAt(event->pos()));

                if(item)
                {
                    Core::SceneObject* focusObject = item->getObject();

                    if(focusObject == nullptr)
                    {
                        focusObject = OcularScene->findObject(item->getUUID());
                    }

                    if(focusObject)
                    {
                        OcularEvents->queueEvent(std::make_shared<SceneObjectSelectedEvent>(focusObject));
                    }
                }
                else
                {
                    clearSelection();

                    const QModelIndex index;
                    selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);

                    OcularEvents->queueEvent(std::make_shared<SceneObjectSelectedEvent>(nullptr));
                }
            }
        }

        void SceneTree::mouseDoubleClickEvent(QMouseEvent* event)
        {
            QTreeWidget::mouseDoubleClickEvent(event);

            if(event)
            {
                SceneTreeItem* item = dynamic_cast<SceneTreeItem*>(itemAt(event->pos()));

                if(item)
                {
                    Core::SceneObject* focusObject = item->getObject();

                    if(focusObject == nullptr)
                    {
                        focusObject = OcularScene->findObject(item->getUUID());
                    }

                    if(focusObject)
                    {
                        Core::Camera* editorCamera = OcularEditor.getEditorCamera();

                        if(editorCamera)
                        {
                            EditorCameraController* controller = dynamic_cast<EditorCameraController*>(editorCamera->getRoutine("EditorCameraController"));

                            if(controller)
                            {
                                controller->focus(focusObject);
                            }
                        }
                    }
                }
            }
        }

        bool SceneTree::onEvent(std::shared_ptr<Core::AEvent> event)
        {
            if(event->isType<Core::SceneObjectAddedEvent>())
            {
                Core::SceneObjectAddedEvent* objectEvent = dynamic_cast<Core::SceneObjectAddedEvent*>(event.get());

                if(objectEvent)
                {
                    Core::SceneObject* object = objectEvent->object;

                    if(object)
                    {
                        addObject(object);
                    }
                }
            }
            else if(event->isType<Core::SceneObjectRemovedEvent>())
            {
                Core::SceneObjectRemovedEvent* objectEvent = dynamic_cast<Core::SceneObjectRemovedEvent*>(event.get());

                if(objectEvent)
                {
                    removeObject(objectEvent->uuid);
                }
            }

            return true;    // Do not consume this event
        }

        bool SceneTree::isObjectTracked(Core::SceneObject* object)
        {
            bool result = false;

            if(getItem(object))
            {
                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void SceneTree::onShowContextMenu(QPoint const& pos)
        {
            const QPoint globalPos = mapToGlobal(pos);

            //------------------------------------------------------------
            // Build Context Menu
            //------------------------------------------------------------

            QMenu contextMenu;

            auto selectedItems = this->selectedItems();
            const uint32_t numSelected = static_cast<uint32_t>(selectedItems.size());

            switch(numSelected)
            {
            case 0:
                handleContextMenuNoSelection(&contextMenu, globalPos);
                break;

            case 1:
                handleContextMenuSingleSelection(&contextMenu, globalPos);
                break;

            case 2:
            default:         // Explicit fall through
                handleContextMenuMultiSelection(&contextMenu, globalPos, numSelected);
                break;
            }
        }

        void SceneTree::handleContextMenuNoSelection(QMenu* menu, QPoint const& globalPos)
        {
            QMenu* submenu = menu->addMenu("Add SceneObject");
            populateAddObjectSubmenu(submenu);

            menu->addSeparator();
            menu->addAction("Duplicate")->setDisabled(true);
            menu->addAction("Rename")->setDisabled(true);
            menu->addAction("Delete")->setDisabled(true);
            
            handleContextMenuAction(menu->exec(globalPos));
        }

        void SceneTree::handleContextMenuSingleSelection(QMenu* menu, QPoint const& globalPos)
        {
            QMenu* submenu = menu->addMenu("AddChild");
            populateAddObjectSubmenu(submenu);

            menu->addSeparator();
            menu->addAction("Duplicate");
            menu->addAction("Rename");
            menu->addAction("Delete");

            handleContextMenuAction(menu->exec(globalPos));
        }

        void SceneTree::handleContextMenuMultiSelection(QMenu* menu, QPoint const& globalPos, uint32_t numSelected)
        {
            QMenu* submenu = menu->addMenu("Add Children");
            populateAddObjectSubmenu(submenu);

            menu->addSeparator();
            menu->addAction("Duplicate");
            menu->addAction("Rename")->setDisabled(true);
            menu->addAction("Delete");
            
            handleContextMenuAction(menu->exec(globalPos));
        }

        void SceneTree::handleContextMenuAction(QAction* action)
        {
            if(action)
            {
                const QString text = action->text();

                if(text.compare("Duplicate") == 0)
                {
                    handleContextMenuActionDuplicate();
                }
                else if(text.compare("Rename") == 0)
                {
                    handleContextMenuActionRename();
                }
                else if(text.compare("Delete") == 0)
                {
                    handleContextMenuActionDelete();
                }
                else
                {
                    handleContextMenuActionCreateObject(text.toStdString());                    
                }
            }
        }

        void SceneTree::handleContextMenuActionDuplicate()
        {
        
        }

        void SceneTree::handleContextMenuActionRename()
        {
        
        }

        void SceneTree::handleContextMenuActionDelete()
        {
            auto selectedItems = this->selectedItems();
            const uint32_t numSelected = static_cast<uint32_t>(selectedItems.size());

            for(auto item : selectedItems)
            {
                SceneTreeItem* sceneTreeItem = dynamic_cast<SceneTreeItem*>(item);

                if(sceneTreeItem)
                {
                    OcularScene->destroyObject(sceneTreeItem->getUUID());
                }
            }
        }

        void SceneTree::handleContextMenuActionCreateObject(std::string const& type)
        {
            auto selectedItems = this->selectedItems();
            const uint32_t numSelected = static_cast<uint32_t>(selectedItems.size());

            if(numSelected == 0)
            {
                // We are creating a new, top-level object 
                OcularScene->createObjectOfType(type, type);
            }
            else if(numSelected)
            {
                // We are creating one or more child objects
                for(auto item : selectedItems)
                {
                    SceneTreeItem* sceneTreeItem = dynamic_cast<SceneTreeItem*>(item);

                    if(sceneTreeItem)
                    {
                        Core::SceneObject* object = sceneTreeItem->getObject();

                        if(object)
                        {
                            OcularScene->createObjectOfType(type, type, object);
                        }
                    }
                }
            }
        }

        void SceneTree::populateAddObjectSubmenu(QMenu* submenu)
        {
            std::vector<std::string> objectTypes = OcularScene->getSceneObjectFactory().getRegisteredKeys();
            const bool disable = !OcularScene->isSceneActive();

            for(auto objectType : objectTypes)
            {
                submenu->addAction(objectType.c_str())->setDisabled(disable);
            }
        }

    }
}