/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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
#include "OcularEngine.hpp"

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
            : m_Name(name), m_Class(className), m_UID(OcularEngine.UIDGenerator()->next()), m_CreationTime(OcularEngine.Clock()->getElapsedMS())
        {

        }

        Object::Object(std::string name)
            : m_Name(name), m_Class("Object"), m_UID(OcularEngine.UIDGenerator()->next()), m_CreationTime(OcularEngine.Clock()->getElapsedMS())
        {
        
        }
    
        Object::Object()
            : m_Name("Name"), m_Class("Object"), m_UID(OcularEngine.UIDGenerator()->next()), m_CreationTime(OcularEngine.Clock()->getElapsedMS())
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
    
        std::string Object::getName() const
        {
            return m_Name;
        }

        std::string Object::getClass() const
        {
            return m_Class;
        }
    
        unsigned long long Object::getUID() const
        {
            return m_UID;
        }

        long long Object::getCreationTime() const
        {
            return m_CreationTime;
        }
    
        std::string Object::toString() const
        {
            std::stringstream sstream;
            sstream << "Class[" << m_Class << "] Name['" << m_Name << "'] UID[" << m_UID << "]";
        
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