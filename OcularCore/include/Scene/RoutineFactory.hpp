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
#ifndef __H__OCULAR_CORE_SCENE_ROUTINE_FACTORY__H__
#define __H__OCULAR_CORE_SCENE_ROUTINE_FACTORY__H__

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
        class ARoutine;

        /**
         * \class RoutineFactory
         */
        class RoutineFactory
        {
        public:

            RoutineFactory();
            ~RoutineFactory();

            ARoutine* createRoutine(std::string const& name);

            template<class T>
            bool registerRoutine(std::string name)
            {
                bool result = false;
                const auto find = m_RoutineMap.find(name);

                if(find == m_RoutineMap.end())
                {
                    m_RoutineMap.insert(std::make_pair(name, [](){ return new T; }));
                    result = true;
                }

                return result;
            }

        protected:

        private:

            std::unordered_map<std::string, std::function<ARoutine*()>> m_RoutineMap;
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