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
#ifndef __H__OCULAR_EDITOR_VECTOR4_PROPERTY__H__
#define __H__OCULAR_EDITOR_VECTOR4_PROPERTY__H__

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
         * \class Vector4Property
         *
         * Pre-built property display for Vector4f variables.
         */
        class Vector4Property : public PropertyWidget
        {
        public:

            Vector4Property(QString const& displayName, QWidget* parent = nullptr);
            ~Vector4Property();

            virtual bool updateProperties() override;

        protected:

        private:

            QLabel* m_LabelX;
            QLabel* m_LabelY;
            QLabel* m_LabelZ;
            QLabel* m_LabelW;

            LineProperty* m_EditX;
            LineProperty* m_EditY;
            LineProperty* m_EditZ;
            LineProperty* m_EditW;
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