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
#ifndef __H__OCULAR_EDITOR_COMMON_PROPERTIES_DISPLAY__H__
#define __H__OCULAR_EDITOR_COMMON_PROPERTIES_DISPLAY__H__

#include <QtWidgets/qframe.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>

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
        class Vector3Property;
        class QuatAsEulerProperty;

        /**
         * \class CommonPropertiesDisplay
         */
        class CommonPropertiesDisplay : public QGroupBox
        {
        public:

            CommonPropertiesDisplay(QWidget* parent = nullptr);
            ~CommonPropertiesDisplay();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            void setObject(Core::SceneObject* object);
            void updateProperties();

        protected:
            
            void buildLayout();
            void buildName();
            void buildTransform();

            //------------------------------------------------------------

            QVBoxLayout* m_Layout;
            QLabel*      m_LabelTransform;
            QLineEdit*   m_LineName;

            Vector3Property*     m_PropertyPosition;
            QuatAsEulerProperty* m_PropertyRotation;
            Vector3Property*     m_PropertyScale;

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