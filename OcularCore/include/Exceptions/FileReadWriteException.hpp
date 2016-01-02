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
#ifndef __H__OCULAR_EXCEPTION_FILE_READ_WRITE__H__
#define __H__OCULAR_EXCEPTION_FILE_READ_WRITE__H__

#include "Exception.hpp"
#include "Utilities/StringComposer.hpp"

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
        class FileReadWriteException : public Exception 
        {
        public:

            FileReadWriteException(std::string const& file, std::string const& srcFile, int const line)
                : Exception(OCULAR_STRING_COMPOSER("Access to file/directory '", file, "' denied."), srcFile, line)
            {
                
            }

        protected:

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