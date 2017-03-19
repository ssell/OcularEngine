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
#ifndef __H__OCULAR_EDITOR_MATERIAL_TREE_ITEM__H__
#define __H__OCULAR_EDITOR_MATERIAL_TREE_ITEM__H__

#include <QtWidgets/qtreewidget.h>
#include "Graphics/Material/Material.hpp"

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
        class MaterialTree;

        struct MaterialTreeItemDescriptor
        {
            std::string name;
            std::string path;
            std::string mapping;

            bool isMaterial;
        };

        /**
         * \class MaterialTreeItem
         * \brief 
         */
        class MaterialTreeItem : public QTreeWidgetItem
        {
        public:

            MaterialTreeItem(MaterialTree* parent, MaterialTreeItemDescriptor const& descriptor);
            MaterialTreeItem(MaterialTreeItem* parent, MaterialTreeItemDescriptor const& descriptor);

            virtual ~MaterialTreeItem();

            //------------------------------------------------------------

            MaterialTreeItemDescriptor const& getDescriptor() const;
            
            bool isMaterial() const;

        protected:

            void buildItem();

            //------------------------------------------------------------

            MaterialTreeItemDescriptor m_Descriptor;

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
