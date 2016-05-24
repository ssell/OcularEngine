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
#ifndef __H__OCULAR_CORE_SCENE_COMPONENT_FACTORY__H__
#define __H__OCULAR_CORE_SCENE_COMPONENT_FACTORY__H__

#include <unordered_map>
#include <string>
#include <functional>

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
         * \class ComponentFactory
         */
        template<class T>
        class ComponentFactory
        {
        public:

            ComponentFactory() { }
            ~ComponentFactory() { }

            /**
             *
             */
            T* createComponent(std::string const& name)
            {
                T* result = nullptr;
                const auto find = m_ComponentMap.find(name);

                if(find != m_ComponentMap.end())
                {
                    result = find->second();
                }

                return result;
            }

            /**
             *
             */
            template<typename S>
            bool registerComponent(std::string name)
            {
                bool result = false;
                const auto find = m_ComponentMap.find(name);

                if(find == m_ComponentMap.end())
                {
                    m_ComponentMap.insert(std::make_pair(name, [](){ return new S; }));
                    result = true;
                }

                return result;
            }

            std::vector<std::string> getRegisteredKeys() const
            {
                std::vector<std::string> result;
                result.reserve(m_ComponentMap.size());

                for(auto keyvalue : m_ComponentMap)
                {
                    result.emplace_back(keyvalue.first);
                }

                return result;
            }

        protected:

        private:

            std::unordered_map<std::string, std::function<T*()>> m_ComponentMap;
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