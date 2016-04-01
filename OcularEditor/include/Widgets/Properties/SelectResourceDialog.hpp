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

#pragma once
#ifndef __H__OCULAR_EDITOR_SELECT_RESOURCE_DIALOG__H__
#define __H__OCULAR_EDITOR_SELECT_RESOURCE_DIALOG__H__

#include <QtWidgets/qdialog.h>
#include <QtWidgets/qtreewidget.h>

#include "Resources/Resource.hpp"

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
        enum class ResourceType
        {
            Undefined = 0,
            Renderable,
            Routine
        };

        /**
         * \class SelectResourceDialog
         */
        class SelectResourceDialog : public QDialog
        { 
            Q_OBJECT

        public:
            
            SelectResourceDialog(ResourceType const type, QWidget* parent = nullptr);
            SelectResourceDialog(Core::ResourceType const type, QWidget* parent = nullptr);

            virtual ~SelectResourceDialog();

            std::string const& getSelectedName() const;

        protected:

            void buildWidgets();
            
            void populateTree(ResourceType const type);
            void populateTree(Core::ResourceType const type);

        private slots:

            void onFinished();

        private:

            std::string m_ResourceName;
            
            QLabel* m_LabelTitle;

            QVBoxLayout* m_Layout;
            QTreeWidget* m_TreeResource;

            QPushButton* m_ButtonSelect;
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