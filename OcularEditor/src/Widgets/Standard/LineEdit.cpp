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
#include "Widgets/Standard/LineEdit.hpp"
#include "Widgets/Properties/Types/Arithmetic/UInt32Validator.hpp"
#include "QtGui/qvalidator.h"

#include <limits>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        LineEdit::LineEdit(LineType type, QWidget* parent)
            : QLineEdit(parent),
              m_Type(type),
              m_WasEdited(false)
        {
            switch(m_Type)
            {
            case LineType::Int8:
                setValidator(new QIntValidator(static_cast<int32_t>(std::numeric_limits<int8_t>::min()), static_cast<int32_t>(std::numeric_limits<int8_t>::max()), this));
                break;

            case LineType::UInt8:
                setValidator(new QIntValidator(static_cast<int32_t>(std::numeric_limits<uint8_t>::min()), static_cast<int32_t>(std::numeric_limits<uint8_t>::max()), this));
                break;

            case LineType::Int16:
                setValidator(new QIntValidator(static_cast<int32_t>(std::numeric_limits<int16_t>::min()), static_cast<int32_t>(std::numeric_limits<int16_t>::max()), this));
                break;

            case LineType::UInt16:
                setValidator(new QIntValidator(static_cast<int32_t>(std::numeric_limits<uint16_t>::min()), static_cast<int32_t>(std::numeric_limits<uint16_t>::max()), this));
                break;

            case LineType::Int32:
                setValidator(new QIntValidator(std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max(), this));
                break;

            case LineType::UInt32:
                setValidator(new UInt32Validator(this));
                break;

            case LineType::Float:    // Explicit fall through
            case LineType::Double:
                setValidator(new QDoubleValidator(this));
                break;

            case LineType::String:
            default:
                break;
            }

            setAlignment(Qt::AlignVCenter);
            
            connect(this, SIGNAL(textChanged(QString const&)), this, SLOT(contentsChanged(QString const&)));
            connect(this, SIGNAL(textEdited(QString const&)), this, SLOT(userEdited(QString const&)));
        }

        LineEdit::~LineEdit()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool LineEdit::wasEdited(bool reset)
        {
            bool result = m_WasEdited;

            if(reset)
            {
                m_WasEdited = false;
            }

            return result;
        }

        void LineEdit::setInvalid(bool invalid)
        {
            if(invalid)
            {
                setStyleSheet(GeneralStyles::lineEditInvalidStyle);
            }
            else
            {
                setStyleSheet(GeneralStyles::lineEditValidStyle);
            }
        }

        int32_t LineEdit::asInt() const
        {
            return OcularString->fromString<int32_t>(text().toStdString());
        }

        uint32_t LineEdit::asUint() const
        {
            return OcularString->fromString<uint32_t>(text().toStdString());
        }

        float LineEdit::asFloat() const
        {
            return OcularString->fromString<float>(text().toStdString());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
        
        void LineEdit::contentsChanged(QString const& text)
        {
            if(!hasFocus())
            {
                if((m_Type == LineType::Float) ||
                    (m_Type == LineType::Double))
                {
                    const int index = text.lastIndexOf('.');

                    if(index > 0)
                    {
                        const int numDecimals = (text.size() - index);
                        const int numTrim = numDecimals - 5;

                        if(numTrim > 0)
                        {
                            std::string trimText = text.toStdString();
                            trimText = trimText.substr(0, (text.size() - numTrim));

                            setText(trimText.c_str());
                            setCursorPosition(0);
                        }
                    }
                }
            }
        }

        void LineEdit::userEdited(QString const& text)
        {
            m_WasEdited = true;
        }
    }
}