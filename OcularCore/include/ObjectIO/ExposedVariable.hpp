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
#ifndef __H__OCULAR_CORE_EXPOSED_VARIABLE__H__
#define __H__OCULAR_CORE_EXPOSED_VARIABLE__H__

#include "Utilities/Types.hpp"
#include "Utilities/StringUtils.hpp"

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
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \struct ExposedVariable
         */
        struct ExposedVariable
        {
            ExposedVariable(std::string const& name, std::string const& type, void* data, bool pointer, bool trivial, bool exposed, uint32_t size)
                : name(name), type(type), data(data), isPointer(pointer), isTrivial(trivial), isExposed(exposed), size(size) { }

            ExposedVariable()
                : data(nullptr), isPointer(false), isTrivial(true), isExposed(false), size(0) { }

            //------------------------------------------------------------

            std::string name;     ///< Name of the member variable
            std::string type;     ///< String representation of the variable type 
            
            void* data;           ///< Raw data value of the variable

            bool isPointer;       ///< If true, the exposed variable is a pointer (and must be handled accordingly).
            bool isTrivial;       ///< If true, is a trivial data type
            bool isExposed;       ///< If true, the type inherits from Exposable

            uint32_t size;        ///< Size of the data type
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