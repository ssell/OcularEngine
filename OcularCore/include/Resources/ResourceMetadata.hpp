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

#pragma once
#ifndef __H__OCULAR_CORE_RESOURCE_METADATA__H__
#define __H__OCULAR_CORE_RESOURCE_METADATA__H__

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
         * \class ResourceMetadata
         *
         * ResourceMetadata represents optional data/information regarding a specific Resource.
         * The data stored in an instance of ResourceMetadata is completely dependent on the 
         * Resource type, source file type, and the specific implementation of ResourceMetadata used.
         */
        class ResourceMetadata
        {
        public:

            ResourceMetadata(std::string const& type);
            ~ResourceMetadata();

            virtual void ointernal();

            std::string const& getType() const;

        protected:

        private:

            std::string m_Type;
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

