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
#ifndef __H__OCULAR_UTILITIES_EXPOSABLE__H__
#define __H__OCULAR_UTILITIES_EXPOSABLE__H__

#include "Types.hpp"
#include "StringUtils.hpp"

#include <string>
#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Utils
     * @{
     */
    namespace Utils
    {
        /**
         * \struct ExposedVariable
         */
        struct ExposedVariable
        {
            std::string name;     ///< Name of the member variable
            std::string type;     ///< String representation of the variable type 
            void* ptr;            ///< Raw generic pointer to the variable
        };

        /**
         * \class Exposable
         */
        class Exposable
        {
        public:
           
            /**
             * Fills a vector with the names of all exposed variables. These names
             * can then be used with the various get/set variable methods.
             *
             * \note The provided vector is cleared prior to any names being added
             *
             * \param[out] names
             */
            void getAllExposedNames(std::vector<std::string>& names) const;

            /**
             * Attempts to retrieve the specified exposed variable.
             *
             * \param[in]  name
             * \param[out] var
             *
             * \return TRUE if a variable was exposed with the specified name
             */
            bool getVariable(std::string const& name, ExposedVariable& var);

            /**
             * Attempts to retrieve the value of the specified exposed variable.
             *
             * \param[in]  name
             * \param[out] var
             *
             * \return TRUE if a variable was exposed with the specified name and matching type
             */
            template<typename T>
            bool getVariableValue(std::string const& name, T& var)
            {
                bool result = false;
                auto find = m_ExposedVariables.find(name);

                if(find != m_ExposedVariables.end())
                {
                    if(StringUtils::isEqual(OCULAR_TYPE(T), find->second.type))
                    {
                        value = *(T*)(find->second.ptr);
                        result = true;
                    }
                }

                return result;
            }

            /**
             * Attempts to set the value of the specified exposed variable.
             *
             * \param[in] name
             * \param[in] value
             *
             * \return TRUE if successfully set the value of the specified variable.
             *         May fail if no variable with the given name was found and/or
             *         if variable type did not match.
             */
            template<typename T>
            bool setVariableValue(std::string const& name, T const& value)
            {
                bool result = false;
                auto find = m_ExposedVariables.find(name);

                if(find != m_ExposedVariables.end())
                {
                    if(StringUtils::isEqual(OCULAR_TYPE(T), find->second.type))
                    {
                        *(find->second.ptr) = value;
                        result = true;
                    }
                }

                return result;
            }

        protected:

            /**
             * Exposes the specified member variable so that it's value can be retrieved or 
             * modified by anyone. This includes protected and private variables.
             *
             * Internally (ie by the Ocular engine itself) this is typically only used
             * for saving/loading purposes (or by the editor application). But it's use
             * is in no way limited to just the engine.
             *
             * \note If a variable with the specified name was already exposed, then no
             * action will be taken.
             *
             * \param[in] name Full unique case-sensitive name of the member variable
             * \param[in] type String representation of the member variable type (see OCULAR_TYPE macro)
             * \param[in] ptr  Pointer to the member variable to expose
             */
            void exposeVariable(std::string const& name, std::string const& type, void* ptr);

        private:

            std::unordered_map<std::string, ExposedVariable> m_ExposedVariables;
        };

/**
 * Exposes the specified member variable. See Ocular::Utils::Exposable
 */
#define OCULAR_EXPOSE(X) exposeVariable(std::string(#X), OCULAR_TYPE(X), &X)

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