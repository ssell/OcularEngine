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
        /**
         * \class PropertiesDisplayBox
         */
        class PropertiesDisplayBox : public QGroupBox
        {
        public:

            PropertiesDisplayBox(QString const& displayName, QWidget* parent = nullptr);
            ~PropertiesDisplayBox();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            virtual void setObject(Core::SceneObject* object) = 0;
            virtual void updateProperties() = 0;

        protected:
            
            void buildLayout();
            void buildName();
            void buildTransform();

            //------------------------------------------------------------

            QVBoxLayout* m_Layout;
            Core::SceneObject* m_Object;

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