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
#ifndef __H__OCULAR_EDITOR_CONTENT_TAB__H__
#define __H__OCULAR_EDITOR_CONTENT_TAB__H__

#include <QtWidgets/qtabwidget.h>

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
        /**
         * \class ContentTab
         * \brief Custom tab widget for content modification
         */
        class ContentTab : public QTabWidget
        {
        public:

            ContentTab(QWidget* parent = nullptr);
            ~ContentTab();

            virtual QSize sizeHint() const override;

        protected:

        private:

            void createTabs();

            //------------------------------------------------------------

            QWidget* m_ObjectTab;
            QWidget* m_SceneTreeTab;

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
