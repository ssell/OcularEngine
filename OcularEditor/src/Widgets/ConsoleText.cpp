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

#include "stdafx.h"
#include "Widgets/ConsoleText.hpp"
#include <sstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ConsoleText::ConsoleText(QWidget *parent)
            : QTextEdit(parent)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            setReadOnly(true);

            setStyleSheet(tr("font-family: \"Lucida Console\", Monaco, monospace; background-color: rgb(56, 56, 60);"));

            OcularLogger->registerListener(this);
        }

        ConsoleText::~ConsoleText()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize ConsoleText::sizeHint() const
        {
            return QSize(250, 175);
        }

        void ConsoleText::onLogMessage(Core::LoggerMessage const& message)
        {
            switch(message.channel)
            {
            case Core::LoggerChannels::Warning:
                writeWarning(message.message);
                break;

            case Core::LoggerChannels::Error:    // Intentional fall through
            case Core::LoggerChannels::Fatal:
                writeError(message.message);
                break;

            default:
                write(message.message);
                break;
            }
        }

        void ConsoleText::write(std::string const& message)
        {
            std::stringstream sstream;
            sstream << "<font color=\"#DDDDDD\"> " << message << "</font><br>";

            insertHtml(tr(sstream.str().c_str()));
        }

        void ConsoleText::writeWarning(std::string const& message)
        {
            std::stringstream sstream;
            sstream << "<font color=\"#DDDD00\"> " << message << "</font><br>";

            insertHtml(tr(sstream.str().c_str()));
        }

        void ConsoleText::writeError(std::string const& message)
        {
            std::stringstream sstream;
            sstream << "<font color=\"#DD0000\"> " << message << "</font><br>";

            insertHtml(tr(sstream.str().c_str()));
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}