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

#pragma once
#ifndef __H__OCULAR_EDITOR_SCENE_TREE_ITEM__H__
#define __H__OCULAR_EDITOR_SCENE_TREE_ITEM__H__

#include <QtWidgets/qtreewidget.h>
#include <UUID.hpp>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    namespace Core
    {
        class SceneObject;
    }

    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        class SceneTree;

        /**
         * \class SceneTreeItem
         * \brief 
         */
        class SceneTreeItem : public QTreeWidgetItem
        {
        public:

            /**
             * Constructor for a top-level tree item.
             *
             * \param[in] parent Parent tree to add this item to
             * \param[in] object SceneObject that this item represents
             */
            SceneTreeItem(SceneTree* parent, Core::SceneObject* object);
            
            /**
             * Constructor for a child tree item.
             *
             * \param[in] parent Parent item to add this item to
             * \param[in] object SceneObject that this item represents
             */
            SceneTreeItem(SceneTreeItem* parent, Core::SceneObject* object);

            /**
             * Destructor
             */
            virtual ~SceneTreeItem();

            //------------------------------------------------------------

            void update(bool recursive = true);

            /**
             * \return The object that is represented by this item.
             */
            Core::SceneObject* getObject() const;

            /**
             * \return The UUID of the object that is represented by this item.
             */
            Core::UUID const& getUUID() const;

        protected:

            /**
             * Builds the item based off of the SceneObject
             */
            void buildItem();

            //------------------------------------------------------------

            Core::SceneObject* m_Object;
            Core::UUID m_ObjectUUID;

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif
