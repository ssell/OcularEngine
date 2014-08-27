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

#pragma once
#ifndef __H__OCULAR_OBJECT__H__
#define __H__OCULAR_OBJECT__H__

#include <string>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \class Object
     * \brief Base class of all representable Ocular constructs.
     */
    class Object
    {
    public:
        
        /**
         * \brief Creates a new Object with the specified name.
         * \param name
         */
        Object(const std::string name);
        
        /**
         * \brief Creates a new Object with the default name ('Name').
         */
        Object();
        
        /**
         *
         */
        virtual ~Object();
        
        /**
         * \return The name of the Object
         */
        std::string getName();
        
        /**
         * \brief Sets the name of the Object
         * \param name 
         */
        void setName(const std::string name);
        
        /**
         * \return The UID of the Object
         */
        unsigned int getUID();
        
        /**
         * \return The string representation of the Object
         */
        virtual std::string toString();
        
    protected:
        
        std::string m_Name;          /**< Non-unique name of the Object */
        
        const std::string m_Class;   /**< Name of the class of which Object is an instance */
        const unsigned int m_UID;    /**< Unique integer identifier */
        
    private:
    };
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif