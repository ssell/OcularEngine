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

#include "stdafx.h"
#include "Widgets/Properties/Types/Arithmetic/UInt32Validator.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        UInt32Validator::UInt32Validator(QObject* parent)
            : QValidator(parent)
        {

        }

        UInt32Validator::~UInt32Validator()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QValidator::State UInt32Validator::validate(QString& input, int& pos) const
        {
            QValidator::State result = QValidator::Acceptable;

            //------------------------------------------------------------
            // Ensure it is comprised of only numeric characters
            //------------------------------------------------------------

            QRegExp regex("\\d*");

            if(regex.exactMatch(input))
            {
                // Ensure it can be converted to an uint32_t

                try
                {
                    uint32_t value = std::stoul(input.toStdString());
                }
                catch(std::invalid_argument const& e)
                {
                    // Failed to convert
                    result = QValidator::Invalid;
                }
            }
            else
            {
                // As an unsigned integer, there is no room for non-numeric characters.
                // No `-`, `.`, ` `, etc.
                result = QValidator::Invalid;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}