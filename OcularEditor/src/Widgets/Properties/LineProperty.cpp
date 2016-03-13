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
#include "Widgets/Properties/LineProperty.hpp"
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
        
        LineProperty::LineProperty(LineType type, QWidget* parent)
            : QLineEdit(parent),
              m_Type(type),
              m_WasEdited(false)
        {
            switch(m_Type)
            {
            case LineType::Integer:
                setValidator(new QIntValidator(this));
                break;

            case LineType::UnsignedInteger:
                setValidator(new QIntValidator(0, INT_MAX, this));
                break;

            case LineType::Float:
                setValidator(new QDoubleValidator(this));
                break;
                
            case LineType::String:
            default:
                break;
            }
            
            connect(this, SIGNAL(textChanged(QString const&)), this, SLOT(contentsChanged(QString const&)));
            connect(this, SIGNAL(textEdited(QString const&)), this, SLOT(userEdited(QString const&)));
        }

        LineProperty::~LineProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool LineProperty::wasEdited(bool reset)
        {
            bool result = m_WasEdited;

            if(reset)
            {
                m_WasEdited = false;
            }

            return result;
        }

        int32_t LineProperty::asInt() const
        {
            return OcularString->fromString<int32_t>(text().toStdString());
        }

        uint32_t LineProperty::asUint() const
        {
            return OcularString->fromString<uint32_t>(text().toStdString());
        }

        float LineProperty::asFloat() const
        {
            return OcularString->fromString<float>(text().toStdString());
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
        
        void LineProperty::contentsChanged(QString const& text)
        {
            //setCursorPosition(0);
        }

        void LineProperty::userEdited(QString const& text)
        {
            m_WasEdited = true;
        }
    }
}