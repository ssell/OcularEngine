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
            : m_Name(name), 
              m_Class(className), 
              m_UUID(), 
              m_CreationTime(OcularEngine.Clock()->getElapsedMS())
        {
            OCULAR_EXPOSE(m_Name);
            OCULAR_EXPOSE(m_Class);
            OCULAR_EXPOSE(m_UUID);
        }

        Object::Object(std::string name)
            : m_Name(name), 
              m_Class("Object"), 
              m_UUID(), 
              m_CreationTime(OcularEngine.Clock()->getElapsedMS())
        {
            OCULAR_EXPOSE(m_Name);
            OCULAR_EXPOSE(m_Class);
            OCULAR_EXPOSE(m_UUID);
        }
    
        Object::Object()
            : m_Name("Name"), 
              m_Class("Object"), 
              m_UUID(), 
              m_CreationTime(OcularEngine.Clock()->getElapsedMS())
        {
            OCULAR_EXPOSE(m_Name);
            OCULAR_EXPOSE(m_Class);
            OCULAR_EXPOSE(m_UUID);
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
    
        std::string const& Object::getName() const
        {
            return m_Name;
        }

        std::string const& Object::getClass() const
        {
            return m_Class;
        }

        void Object::setUUID(std::string const& uuid)
        {
            const UUID oldUUID = m_UUID;

            m_UUID.set(uuid);

            OcularScene->updateUUID(oldUUID);
        }
    
        UUID const& Object::getUUID() const
        {
            return m_UUID;
        }

        int64_t Object::getCreationTime() const
        {
            return m_CreationTime;
        }
    
        std::string Object::toString() const
        {
            std::stringstream sstream;
            sstream << "Class[" << m_Class << "] Name['" << m_Name << "'] UID[" << m_UUID.toString() << "]";
        
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