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
#ifndef __H__OCULAR_RESOURCES_RESOURCE_SAVER_REGISTRAR__H__
#define __H__OCULAR_RESOURCES_RESOURCE_SAVER_REGISTRAR__H__

#include "Resource.hpp"
#include "OcularEngine.hpp"

#include <memory>
#include <iostream>

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
         * \class ResourceSaverRegistrar
         */
        template<class T>
        class ResourceSaverRegistrar
        {
        public:

            ResourceSaverRegistrar()
            {
                T* t = new T();
                AResourceSaver* saver = dynamic_cast<AResourceSaver*>(t);

                if(saver != nullptr)
                {
                    std::shared_ptr<AResourceSaver> shared(saver);
                    OcularEngine.ResourceManager()->registerResourceSaver(shared);
                }
                else 
                {
                    delete t;
                    t = nullptr;
                }
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

/// Used to automatically register AResourceSaver classes. Should be used once in the implementation source file of a Resource Saver.
#define OCULAR_REGISTER_RESOURCE_SAVER(T) Ocular::Core::ResourceSaverRegistrar<T> OCULAR_INTERNAL_RegisterResourceSaver;

//------------------------------------------------------------------------------------------

#endif