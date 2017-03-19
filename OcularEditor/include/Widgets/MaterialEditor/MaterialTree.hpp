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
#ifndef __H__OCULAR_EDITOR_MATERIAL_TREE__H__
#define __H__OCULAR_EDITOR_MATERIAL_TREE__H__

#include <QtWidgets/qtreewidget.h>
#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        class MaterialTreeItem;

        /**
         * \class MaterialTree
         * \brief 
         */
        class MaterialTree : public QTreeWidget
        {
            Q_OBJECT

        public:

            MaterialTree(QWidget* parent = nullptr);
            ~MaterialTree();

            /**
             * Refreshes the list of materials.
             */
            void refresh();

        protected:

            virtual void mousePressEvent(QMouseEvent* event) override;

            void populateTree();
            void splitMapping(std::string const& mapping, std::string& path, std::string& name);
            MaterialTreeItem* createParent(std::string const& parentPath);

        private slots:

        private:

            std::unordered_map<std::string, MaterialTreeItem*> m_ItemMap;    ///< Convenience mapping of paths and items. Key is the full path of the item.

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
