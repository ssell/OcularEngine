/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Object.hpp"
#include <sstream>

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
    
        Object::Object(std::string name, std::string className)
            : m_Name(name), m_Class(className), m_UID(0)
        {
    
        }

        Object::Object(std::string name)
            : m_Name(name), m_Class("Object"), m_UID(0)
        {
        
        }
    
        Object::Object()
            : m_Name("Name"), m_Class("Object"), m_UID(0)
        {
        
        }
    
        Object::~Object()
        {
        
        }
    
        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
    
        void Object::setName(std::string name)
        {
            m_Name = name;
        }
    
        std::string Object::getName()
        {
            return m_Name;
        }
    
        unsigned int Object::getUID()
        {
            return m_UID;
        }
    
        std::string Object::toString()
        {
            std::stringstream sstream;
            sstream << "Name['" << m_Name << "'] UID[" << m_UID << "] Class[" << m_Class << "]";
        
            return sstream.str();
        }
    
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
    
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}