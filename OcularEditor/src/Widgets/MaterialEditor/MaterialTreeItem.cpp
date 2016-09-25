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
        
        MaterialTreeItem::MaterialTreeItem(MaterialTree* parent, std::string const& materialPath)
            : QTreeWidgetItem(parent),
              m_MaterialPath(materialPath)
        {
            buildItem();
        }

        MaterialTreeItem::~MaterialTreeItem()
        {
            m_Material = nullptr;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        Graphics::Material const* MaterialTreeItem::getMaterial() const
        {
            return m_Material;
        }

        std::string const& MaterialTreeItem::getMaterialPath() const
        {
            return m_MaterialPath;
        }
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MaterialTreeItem::buildItem()
        {
            setText(0, QString(getLocalName().c_str()));
            setText(0, QString(m_MaterialPath.c_str()));
        }
        
        std::string MaterialTreeItem::getLocalName()
        {
            // Resource path names are separated by '/'
            // The local name is simply the text following the last '/'

            std::string result = m_MaterialPath;
            const size_t pos = result.find_last_of('/');

            if(pos != std::string::npos)
            {
                result = m_MaterialPath.substr(pos + 1);
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}