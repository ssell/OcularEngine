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
#ifndef __H__OCULAR_EDITOR_QUAT_AS_EULER_PROPERTY__H__
#define __H__OCULAR_EDITOR_QUAT_AS_EULER_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/LineEdit.hpp"

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
         * \class QuatAsEulerProperty
         *
         * Pre-built property display for Quaternion variables.
         * Special version which displays the Quaternion in Euler form.
         *
         * To display a standard Quaternion, see the QuaternionProperty class.
         */
        class QuatAsEulerProperty : public PropertyWidget
        {
        public:

            QuatAsEulerProperty(QWidget* parent = nullptr);
            virtual ~QuatAsEulerProperty();

            virtual bool updateProperties() override;

        protected:

        private:

            QLabel* m_LabelX;
            QLabel* m_LabelY;
            QLabel* m_LabelZ;

            LineEdit* m_EditX;
            LineEdit* m_EditY;
            LineEdit* m_EditZ;
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