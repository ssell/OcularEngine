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
#ifndef __H__OCULAR_EDITOR_LINE_EDIT__H__
#define __H__OCULAR_EDITOR_LINE_EDIT__H__

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
        enum class LineType
        {
            String = 0,
            Integer,
            UnsignedInteger,
            Float
        };

        /**
         * \class LineEdit
         *
         * Helper class that automatically handles input mask, etc. setup based
         * on the specified LineType.
         */
        class LineEdit : public QLineEdit
        {
            Q_OBJECT

        public:

            LineEdit(LineType type, QWidget* parent = nullptr);
            ~LineEdit();

            /**
             * \param[in] reset If TRUE, then the edited flag is reset back to FALSE.
             * \return TRUE if the user has modifed this edit (return key was pressed). 
             */
            bool wasEdited(bool reset = true);

            /**
             *
             */
            int32_t asInt() const;

            /**
             *
             */
            uint32_t asUint() const;

            /**
             *
             */
            float asFloat() const;

        protected:
            
        private slots:

            void contentsChanged(QString const& text);
            void userEdited(QString const& text);

        private:

            LineType m_Type;
            bool m_WasEdited;
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