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

            setHeaderHidden(true);
            setColumnCount(2);           // First column is object name; Second is object UUID
            setColumnHidden(1, true);
        }

        SceneTree::~SceneTree()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize SceneTree::sizeHint() const
        {
            return QSize(250, 500);
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

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool SceneTree::onEvent(std::shared_ptr<Core::AEvent> event)
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

            return true;    // Do not consume this event
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
    }
}