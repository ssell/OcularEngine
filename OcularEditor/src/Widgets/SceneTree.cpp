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

#include "Widgets/SceneTree.hpp"
#include "Widgets/SceneTreeItem.hpp"

#include "Events/Events/SceneObjectAddedEvent.hpp"
#include "Events/Events/SceneObjectRemovedEvent.hpp"
#include "Events/SceneObjectSelectedEvent.hpp"
#include "Events/SceneObjectFocusedEvent.hpp"

#include "Scene/Renderables/MeshRenderable.hpp"

namespace
{
    const uint64_t RefreshRate = 200;       // Tree refresh rate in MS

    // The strings below will eventually be moved into config files

    const std::string PathCoreMaterials = "OcularCore/Materials/";
    const std::string PathCoreMeshes = "OcularCore/Meshes/";
}

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

            setDragEnabled(true);
            setDropIndicatorShown(true);
            setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);

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

        void SceneTree::update()
        {
            for(int32_t i = 0; i < topLevelItemCount(); i++)
            {
                SceneTreeItem* item = dynamic_cast<SceneTreeItem*>(topLevelItem(i));

                if(item)
                {
                    item->update();
                }
            }
        }

        SceneTreeItem* SceneTree::getItem(Core::SceneObject* object)
        {
            SceneTreeItem* result = nullptr;
            
            if(object)
            {
                // The second (hidden) column for our items is the UUID string, so search for items matching that data
                auto items = findItems(QString(object->getUUID().toString().c_str()), Qt::MatchFlag::MatchExactly | Qt::MatchFlag::MatchRecursive, 1);

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
            auto items = findItems(QString(uuid.toString().c_str()), Qt::MatchFlag::MatchExactly | Qt::MatchFlag::MatchRecursive, 1);

            if(items.size() > 0)
            {
                result = dynamic_cast<SceneTreeItem*>(items[0]);
            }

            return result;
        }

        void SceneTree::addObject(Core::SceneObject* object)
        {
            if(object)
            {
                if(!Utils::String::Contains(object->getName(), "OCULAR_INTERNAL_EDITOR", true))
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
                                parentItem->setExpanded(true);
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

        void SceneTree::selectObject(Core::SceneObject* object)
        {
            auto item = getItem(object);
            auto selectItems = selectedItems();

            for(auto selected : selectItems)
            {
                selected->setSelected(false);
            }

            if(item)
            {
                item->setSelected(true);
            }
        }

        void SceneTree::selectObject(Core::UUID const& uuid)
        {
            auto item = getItem(uuid);
            auto selectItems = selectedItems();

            for(auto selected : selectItems)
            {
                selected->setSelected(false);
            }

            if(item)
            {
                item->setSelected(true);
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
                        OcularEditor.setSelectedObject(focusObject); 
                    }
                }
                else
                {
                    clearSelection();

                    const QModelIndex index;
                    selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);

                    OcularEditor.setSelectedObject(nullptr); 
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
                        OcularEvents->queueEvent(std::make_shared<SceneObjectFocusedEvent>(focusObject));
                    }
                }
            }
        }

        void SceneTree::dropEvent(QDropEvent* event)
        {
            if(event)
            {
                //--------------------------------------------------------
                // Retrieve the SceneObject that was dropped on

                Core::SceneObject* newParent = nullptr;
                SceneTreeItem* parentItem = dynamic_cast<SceneTreeItem*>(itemAt(event->pos()));
                
                if(parentItem)
                {
                    newParent = parentItem->getObject();
                }

                //--------------------------------------------------------
                // Update the parent of the dragged SceneObjects

                auto draggedItems = selectedItems();

                for(auto draggedItem : draggedItems)
                {
                    SceneTreeItem* item = dynamic_cast<SceneTreeItem*>(draggedItem);

                    if(item)
                    {
                        item->getObject()->setParent(newParent);
                    }
                }
            }

            QTreeWidget::dropEvent(event); // Call super at end or else it will clear the selected items list before we can use it
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
                        if(OcularScene->findObject(object->getUUID()))
                        {
                            addObject(object);
                        }
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

        void SceneTree::createObject(std::string const& type, Core::SceneObject* parent)
        {
            Core::SceneObject* object = OcularScene->createObjectOfType(type, type, parent);

            if(object == nullptr)
            {
                // Failed to create a custom SceneObject of the type.
                // Check if we were requested to create a Mesh instead.

                Core::SceneObject* object = new Core::SceneObject(type, parent);
                object->setRenderable("MeshRenderable");

                Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(object->getRenderable());

                if(renderable)
                {
                    renderable->setMaterial(PathCoreMaterials + "Default");
                    renderable->setMesh(PathCoreMeshes + type + "/" + type);
                }
            }
        }

        uint32_t SceneTree::getItemDepth(QTreeWidgetItem* item) const
        {
            // Calculates the depth of a given tree item.
            // Depth of 0 indicates its a top-level item (no parent).

            uint32_t result = 0;
            QTreeWidgetItem* searchItem = item;

            while(searchItem)
            {
                searchItem = searchItem->parent();
                result++;
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
            auto selectedItems = this->selectedItems();
            const uint32_t numSelected = static_cast<uint32_t>(selectedItems.size());

            if(numSelected)
            {
                /*
                 * We duplicate in two passes: 
                 *
                 *     1. Determine the top-level selected items. We only want to duplicate those.
                 *     2. Duplicate the SceneObjects associated with the top-level items.
                 */

                //--------------------------------------------------------
                // Pass 1
                //--------------------------------------------------------
                
                // Create a helper container to make life easier
                std::vector<std::pair<SceneTreeItem*, uint32_t>> items;
                items.reserve(selectedItems.size());

                uint32_t lowestDepth = std::numeric_limits<uint32_t>::max();

                for(auto item : selectedItems)
                {
                    SceneTreeItem* itemCast = dynamic_cast<SceneTreeItem*>(item);

                    if(item)
                    {
                        const uint32_t depth = getItemDepth(item);
                        items.push_back(std::make_pair(itemCast, depth));

                        if(depth < lowestDepth)
                        {
                            lowestDepth = depth;           // Keep track of the lowest depth (top-level)
                        }
                    }
                }

                //--------------------------------------------------------
                // Pass 2
                //--------------------------------------------------------

                for(auto itemPair : items)
                {
                    if(itemPair.second == lowestDepth)     // If one of our top-level items, duplicate
                    {
                        OcularScene->duplicateObject(itemPair.first->getObject());
                    }
                }
            }
        }

        void SceneTree::handleContextMenuActionRename()
        {
        
        }

        void SceneTree::handleContextMenuActionDelete()
        {
            auto selectedItems = this->selectedItems();
            const uint32_t numSelected = static_cast<uint32_t>(selectedItems.size());
            
            OcularEditor.setSelectedObject(nullptr);

            for(auto item : selectedItems)
            {
                SceneTreeItem* sceneTreeItem = dynamic_cast<SceneTreeItem*>(item);

                if(sceneTreeItem)
                {
                    OcularScene->destroyObject(sceneTreeItem->getUUID());
                    OcularEvents->queueEvent(std::make_shared<SceneObjectSelectedEvent>(nullptr));
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
                createObject(type, nullptr);
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
                        createObject(type, object);

                        sceneTreeItem->setExpanded(true);  // Ensure the item is expanded so we can see the new object
                    }
                }
            }
        }

        void SceneTree::populateAddObjectSubmenu(QMenu* submenu)
        {
            std::vector<std::string> objectTypes = OcularScene->getSceneObjectFactory().getRegisteredKeys();
            const bool disable = !OcularScene->isSceneActive();

            QMenu* meshSubmenu = submenu->addMenu("Add Mesh");
            
            meshSubmenu->addAction("Cube")->setDisabled(disable);
            meshSubmenu->addAction("Sphere")->setDisabled(disable);
            meshSubmenu->addAction("Torus")->setDisabled(disable);
            meshSubmenu->addAction("Plane")->setDisabled(disable);

            QMenu* lightSubmenu = submenu->addMenu("Add Light");
            
            lightSubmenu->addAction("Point Light")->setDisabled(disable);
            lightSubmenu->addAction("Spot Light")->setDisabled(disable);
            lightSubmenu->addAction("Directional Light")->setDisabled(disable);

            for(auto objectType : objectTypes)
            {
                if(!Utils::String::Contains(objectType, " Light"))
                {
                    submenu->addAction(objectType.c_str())->setDisabled(disable);
                }
            }
        }
    }
}