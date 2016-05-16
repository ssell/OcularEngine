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
#ifndef __H__OCULAR_RESOURCES_MULTI_RESOURCE__H__
#define __H__OCULAR_RESOURCES_MULTI_RESOURCE__H__

#include "Resource.hpp"
#include <vector>

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
         * \class MultiResource
         * 
         * Certain Resource files (such as OBJ) may define multiple individual resources.
         * To handle this, we have a MultiResource. 
         *
         * The MultiResource describes the individual Resources found within, which can then
         * be retrieved either directly from the MultiResources or via the Resources system.
         *
         * If retrieving from the Resources system, then the MultiResource can be treated 
         * as a folder, with the individual Resources stored inside. For example, if we
         * have an OBJ file named "SomeOBJ" with two meshes stored inside ("pCube1" and
         * "pSphere1"), we can retrieve the individual meshes as follows:
         *
         *     OcularResources->getResource("Meshes/SomeOBJ/pCube1");
         *     OcularResources->getResource("Meshes/SomeOBJ/pSphere1");
         */
        class MultiResource : public Resource
        {
        public:

            MultiResource();
            virtual ~MultiResource();
            
            //------------------------------------------------------------

            /**
             *
             */
            void addSubResource(Resource* resource, std::string const& name);

            /**
             *
             */
            Resource* getSubResource(std::string const& name);
            
            /**
             *
             */
            void getSubResourceNames(std::vector<std::string>& names);
            
            /**
             *
             */
            void getSubResources(std::vector<Resource*>& resources);
            
            /**
             *
             */
            uint32_t getNumSubResources() const;

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