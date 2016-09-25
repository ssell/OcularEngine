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
        
        void MaterialTree::populateTree()
        {
            //------------------------------------------------------------
            // Get all Materials
            //------------------------------------------------------------

            std::vector<std::string> allMaterialMappings;
            OcularResources->getResourcesOfType(Core::ResourceType::Material, allMaterialMappings);

            if(allMaterialMappings.size())
            {

            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}