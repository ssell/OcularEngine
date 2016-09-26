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

#include "Widgets/MaterialEditor/MaterialTree.hpp"
#include "Widgets/MaterialEditor/MaterialTreeItem.hpp"

#include "Events/MaterialSelectedEvent.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MaterialTree::MaterialTree(QWidget *parent)
            : QTreeWidget(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
            setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

            setDragEnabled(false);

            setHeaderHidden(true);
            setColumnCount(2);           // First column is 'local' name; Second is full material path
            setColumnHidden(1, true);
        }

        MaterialTree::~MaterialTree()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void MaterialTree::refresh()
        {
            populateTree();
        }
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MaterialTree::mousePressEvent(QMouseEvent* event)
        {
            QTreeWidget::mousePressEvent(event);

            if(event)
            {
                MaterialTreeItem* item = dynamic_cast<MaterialTreeItem*>(itemAt(event->pos()));

                if(item)
                {
                    MaterialTreeItemDescriptor descriptor = item->getDescriptor();

                    if(descriptor.isMaterial)
                    {
                        OcularEvents->queueEvent(std::make_shared<MaterialSelectedEvent>(descriptor.mapping));
                    }
                }
                else
                {
                    clearSelection();

                    const QModelIndex index;
                    selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
                }
            }
        }
        
        void MaterialTree::populateTree()
        {
            //------------------------------------------------------------
            // Get all Materials
            //------------------------------------------------------------

            std::vector<std::string> allMaterialMappings;
            OcularResources->getResourcesOfType(Core::ResourceType::Material, allMaterialMappings);

            for(auto map : allMaterialMappings)
            {
                auto find = m_ItemMap.find(map);

                if(find == m_ItemMap.end())
                {
                    // Material has not been added to the tree, so create a new item.

                    std::string path;
                    std::string name;

                    splitMapping(map, path, name);

                    //----------------------------------------------------
                    // Create item descriptor

                    MaterialTreeItemDescriptor itemDescr;

                    itemDescr.mapping    = map;
                    itemDescr.path       = path;
                    itemDescr.name       = name;
                    itemDescr.isMaterial = true;

                    //----------------------------------------------------
                    // Create any parent items if needed

                    MaterialTreeItem* item = nullptr;

                    if(!OcularString->IsEqual(path, name))
                    {
                        // Path and name do not match which means there is at least one item above this
                        // First check if an item already exists which can be the parent.

                        const auto findParent = m_ItemMap.find(path);

                        if(findParent != m_ItemMap.end())
                        {
                            // Parent item already exists
                            item = new MaterialTreeItem(findParent->second, itemDescr);
                        }
                        else
                        {
                            // At least one parent item needs to be created.
                            item = new MaterialTreeItem(createParent(path), itemDescr);
                        }
                    }
                    else
                    {
                        // Path and name match which means this is a top-level item (exists directly in Resources folder)
                        MaterialTreeItem* item = new MaterialTreeItem(this, itemDescr);
                    }
                    
                    m_ItemMap.insert(std::make_pair(map, item));
                }
            }
        }

        void MaterialTree::splitMapping(std::string const& mapping, std::string& path, std::string& name)
        {
            /**
             * Splits a material mapping into a path and name. Example:
             *
             *     OcularCore/Materials/Default
             *
             *     Path: OcularCore/Materials
             *     Name: Default
             */

            const auto find = mapping.find_last_of('/');

            if(find != std::string::npos)
            {
                path = mapping.substr(0, find);
                name = mapping.substr(find + 1);
            }
            else
            {
                // Material exists directly in the Resources folder
                path = mapping;
                name = mapping;
            }
        }

        MaterialTreeItem* MaterialTree::createParent(std::string const& parentPath)
        {
            MaterialTreeItem* result = nullptr;

            auto find = m_ItemMap.find(parentPath);

            if(find != m_ItemMap.end())
            {
                result = find->second;
            }
            else
            {
                std::string path;
                std::string name;

                splitMapping(parentPath, path, name);

                //----------------------------------------------------
                // Create item descriptor

                MaterialTreeItemDescriptor itemDescr;

                itemDescr.mapping    = parentPath;
                itemDescr.path       = path;
                itemDescr.name       = name;
                itemDescr.isMaterial = false;

                //----------------------------------------------------

                if(OcularString->IsEqual(path, name))
                {
                    // This parent is top-level and there are no more ancestors. 
                    result = new MaterialTreeItem(this, itemDescr);
                }
                else
                {
                    // There are additional ancestors that may or may not need to be created
                    result = new MaterialTreeItem(createParent(path), itemDescr);
                }

                m_ItemMap.insert(std::make_pair(parentPath, result));
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}