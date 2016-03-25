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
#ifndef __H__OCULAR_EDITOR_COMBO_BOX__H__
#define __H__OCULAR_EDITOR_COMBO_BOX__H__

#include <QtWidgets/qcombobox.h>

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
         * \class ComboBox
         *
         * Helper class implementation of QComboBox
         */
        class ComboBox : public QComboBox
        {
            Q_OBJECT

        public:

            ComboBox(QWidget* parent = nullptr);
            ~ComboBox();

            /**
             * \param[in] reset If TRUE, then the edited flag is reset back to FALSE.
             * \return TRUE if the user has modifed this edit. 
             */
            bool wasEdited(bool reset = true);

        protected:
            
        private slots:

            void onIndexChanged(int index);

        private:

            bool m_WasEdited;
            int  m_ValidationIndex;
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