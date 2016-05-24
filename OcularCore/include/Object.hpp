/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "ObjectIO/ObjectIO.hpp"
#include "UUID.hpp"

#include <string>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class Object
         * \brief Base class of all representable Ocular constructs.
         */
        class Object : public ObjectIO
        {
        public:
        
            /**
             * \brief Creates a new Object with the specified name and class.
             * \param name
             * \param className
             */
            Object(std::string name, std::string className);

            /**
             * \brief Creates a new Object with the specified name.
             * \param name
             */
            Object(std::string name);
        
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
            std::string const& getName() const;
        
            /**
             * \brief Sets the name of the Object
             * \param name 
             */
            void setName(std::string name);

            /**
             * \return String representation of the object's Class
             */
            std::string const& getClass() const;

            /**
             * Sets the UUID based off of the properly formatted UUID string.
             * \param[in] uuid
             */
            void setUUID(std::string const& uuid);

            /**
             * \return The UID of the Object
             */
            UUID const& getUUID() const;

            /**
             * \return The time this object was created in MS since engine initialization
             */
            int64_t getCreationTime() const;
        
            /**
             * \return The string representation of the Object
             */
            virtual std::string toString() const;

            /**
             * 
             */
            template<class T> bool isType() 
            { 
                /* Unfortunately, this dynamic_cast seems to be the best solution.
                 * Using std::is_base_of, std::is_convertible, typeid() ==, etc. just aren't sufficient.
                 *
                 * The issue is that a common use-case for this method is checking if an event is a
                 * certain type. For example, we get an Ocular::Core::AEvent* and we want to see if it
                 * is an instance of Ocular::Core::MouseScrollInputEvent.
                 *
                 * The other approaches such as:
                 *
                 *      std::is_base_of<T, std::remove_pointer<decltype(this)>::type>::value
                 *      typeid(T*) == typeid(*this)
                 *
                 * Work fine if checking making this comparison in a vaccuum. Ie:
                 *
                 *     std::is_convertible<AEvent*, MouseScrollInputEvent*>  -> true
                 *     std::is_convertible<MouseScrollInputEvent*, AEvent*>  -> true
                 *
                 * But since this a method of Object, when we call `this`, all of the types return
                 * the type of `Object` and not whatever the actual derived caller may be (in this
                 * example MouseScrollInputEvent).
                 */

                return (dynamic_cast<T*>(this) ? true : false); 
            }
        
        protected:
        
            std::string m_Name;   /**< Non-unique name of the Object */
            std::string m_Class;  /**< Name of the class of which Object is an instance */

            UUID m_UUID;
            const int64_t m_CreationTime;
        
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