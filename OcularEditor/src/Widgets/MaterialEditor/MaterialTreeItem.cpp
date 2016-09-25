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

#include "Widgets/MaterialEditor/MaterialTreeItem.hpp"
#include "Widgets/MaterialEditor/MaterialTree.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        MaterialTreeItem::MaterialTreeItem(MaterialTree* parent, MaterialTreeItemDescriptor const& descriptor)
            : QTreeWidgetItem(parent),
              m_Descriptor(descriptor)
        {
            buildItem();
        }

        MaterialTreeItem::MaterialTreeItem(MaterialTreeItem* parent, MaterialTreeItemDescriptor const& descriptor)
            : QTreeWidgetItem(parent),
            m_Descriptor(descriptor)
        {
            buildItem();
        }

        MaterialTreeItem::~MaterialTreeItem()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        MaterialTreeItemDescriptor const& MaterialTreeItem::getDescriptor() const
        {
            return m_Descriptor;
        }

        bool MaterialTreeItem::isMaterial() const
        {
            return m_Descriptor.isMaterial;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MaterialTreeItem::buildItem()
        {
            setText(0, QString(m_Descriptor.name.c_str()));

            if(m_Descriptor.isMaterial)
            {
                setText(1, QString(m_Descriptor.mapping.c_str()));
            }
            else
            {
                setText(1, QString(m_Descriptor.path.c_str()));
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}