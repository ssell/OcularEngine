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
#ifndef __H__OCULAR_EDITOR_PROPERTIES_DISPLAY_BOX__H__
#define __H__OCULAR_EDITOR_PROPERTIES_DISPLAY_BOX__H__


#include <QtWidgets/qgroupbox.h>
#include <QtWidgets/qboxlayout.h>

#include "Scene/SceneObject.hpp"

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
        class PropertiesDisplayTitleBar;

        /**
         * \class PropertiesDisplayBox
         */
        class PropertiesDisplayBox : public QFrame
        {
        public:

            PropertiesDisplayBox(std::string const& displayName, bool canMinimize = true, bool canClose = false, QWidget* parent = nullptr);
            ~PropertiesDisplayBox();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            void setTitle(std::string const& title);

            virtual void setObject(Core::SceneObject* object) = 0;
            virtual void updateProperties() = 0;

        protected:
            
            void buildLayout();
            void buildTitleBar(std::string const& displayName, bool canMinimize, bool canClsoe);

            //------------------------------------------------------------

            QVBoxLayout* m_Layout;
            Core::SceneObject* m_Object;

            PropertiesDisplayTitleBar* m_TitleBar;

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