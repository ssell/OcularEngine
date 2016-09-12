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
#include "Widgets/SceneTreeItem.hpp"
#include "Widgets/SceneTree.hpp"

//------------------------------------------------------------------------------------------

namespace
{
    const char* activeText = "color: rgb(255, 255, 255);";
    const char* inactiveText = "color: rgb(0, 0, 0);";
}

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        SceneTreeItem::SceneTreeItem(SceneTree* parent, Core::SceneObject* object)
            : QTreeWidgetItem(parent),
              m_Object(object)
        {
            buildItem();
        }

        SceneTreeItem::SceneTreeItem(SceneTreeItem* parent, Core::SceneObject* object)
            : QTreeWidgetItem(parent),
              m_Object(object)
        {
            buildItem();
        }

        SceneTreeItem::~SceneTreeItem()
        {
            m_Object = nullptr;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void SceneTreeItem::update(bool const recursive)
        {
            if(m_Object)
            {
                //--------------------------------------------------------
                // Update active indicator
                //--------------------------------------------------------

                // Inactive object is represented by italics text since I have not found a reliable way yet to change the color.
                // There is no setStyleSheet for an item and setForeground did not work...

                QFont font = this->font(0);
                font.setItalic(!m_Object->isActive());

                setFont(0, font);

                //--------------------------------------------------------
                // Update name
                //--------------------------------------------------------

                if(text(0).compare(m_Object->getName().c_str()) != 0)
                {
                    setText(0, QString(m_Object->getName().c_str()));
                }
            }

            if(recursive)
            {
                for(int32_t i = 0; i < childCount(); i++)
                {
                    SceneTreeItem* childItem = dynamic_cast<SceneTreeItem*>(child(i));

                    if(childItem)
                    {
                        childItem->update(true);
                    }
                }
            }
        }

        Core::SceneObject* SceneTreeItem::getObject() const
        {
            return m_Object;
        }

        Core::UUID const& SceneTreeItem::getUUID() const
        {
            return m_ObjectUUID;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void SceneTreeItem::buildItem()
        { 
            if(m_Object)
            {
                m_ObjectUUID = m_Object->getUUID();

                setText(0, QString(m_Object->getName().c_str()));
                setText(1, QString(m_ObjectUUID.toString().c_str()));
            }
            else
            {
                setText(0, QString("NULL"));
                setText(1, QString("0"));
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}