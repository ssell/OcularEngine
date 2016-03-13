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
#ifndef __H__OCULAR_EDITOR_VECTOR2_PROPERTY__H__
#define __H__OCULAR_EDITOR_VECTOR2_PROPERTY__H__

#include "PropertyWidget.hpp"
#include <QtWidgets/qlineedit.h>

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
         * \class Vector2Property
         *
         * Pre-built property display for Vector2f variables.
         */
        class Vector2Property : public PropertyWidget
        {
        public:

            Vector2Property(QString const& displayName, QWidget* parent = nullptr);
            ~Vector2Property();

            virtual void updateProperties() override;

        protected:

        private:

            QLabel* m_LabelX;
            QLabel* m_LabelY;

            QLineEdit* m_EditX;
            QLineEdit* m_EditY;
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