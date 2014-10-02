/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_UTILS_PRIORITY_MULTI_QUEUE__H__
#define __H__OCULAR_UTILS_PRIORITY_MULTI_QUEUE__H__

#include "CircularQueue.hpp"
#include "Events\EventPriority.hpp"

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
         * \class PriorityMultiQueue
         */
        template<typename T, std::size_t MAX_ELEMENTS>
        class PriorityMultiQueue
        {
        public:

            PriorityMultiQueue();
            ~PriorityMultiQueue();

            bool enqueue(T element, Core::EVENT_PRIORITY priority);
            bool dequeue(Core::EVENT_PRIORITY priority, T& retElement);

        protected:

        private:

            CircularQueue<T, MAX_ELEMENTS> m_CriticalPriority;
            CircularQueue<T, MAX_ELEMENTS> m_HighPriority;
            CircularQueue<T, MAX_ELEMENTS> m_MediumPriority;
            CircularQueue<T, MAX_ELEMENTS> m_LowPriority;
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