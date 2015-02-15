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

#pragma once
#ifndef __H__OCULAR_RESOURCES_RESOURCE_LOADER_REGISTRAR__H__
#define __H__OCULAR_RESOURCES_RESOURCE_LOADER_REGISTRAR__H__

#include "Resource.hpp"
#include "OcularEngine.hpp"

#include <memory>

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
         * \class ResourceLoaderRegistrar
         */
        template<class T>
        class ResourceLoaderRegistrar
        {
        public:

            ResourceLoaderRegistrar()
            {
                T t = new T();
                AResourceLoader* loader = dynamic_cast<AResourceLoader*>(t);

                if(loader != nullptr)
                {
                    OcularEngine.ResourceManager()->registerResourceLoader(std::make_shared<AResourceLoader>(loader));
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

/// Used to automatically register AResourceLoader classes. Should be used once in the implementation source file of a Resource Loader.
#define OCULAR_REGISTER_RESOURCE_LOADER(T) Ocular::Core::ResourceLoaderRegistrar<T> OCULAR_INTERNAL_RegisterResourceLoader();

//------------------------------------------------------------------------------------------

#endif