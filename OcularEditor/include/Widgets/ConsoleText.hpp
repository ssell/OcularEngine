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
#ifndef __H__OCULAR_EDITOR_CONSOLE_TEXT__H__
#define __H__OCULAR_EDITOR_CONSOLE_TEXT__H__

#include <QtWidgets/qtextedit.h>
#include "Logger/ILoggerListener.hpp"

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
         * \class ConsoleText
         * \brief 
         */
        class ConsoleText : public QTextEdit, public Core::ILoggerListener
        {
        public:

            ConsoleText(QWidget* parent = nullptr);
            ~ConsoleText();

            virtual QSize sizeHint() const override;
            virtual void onLogMessage(Core::LoggerMessage const& message) override;

            void write(std::string const& message);
            void writeWarning(std::string const& message);
            void writeError(std::string const& message);

        protected:

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
