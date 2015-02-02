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
         *
         * The PriorityMultiQueue is a priority system based off of the priority levels defined in Core::EVENT_PRIORITY<br/><br/>
         *
         * This structure is best suited for situations where high volumes of enqueue and dequeue actions are expected,
         * and can perform up to 250 times faster than the STL std::priority_queue in this regard. Conversely, random-access
         * is not supported and (currently) neither is set iteration.<br/><br/>
         *
         * If random-access and/or element iteration is required, please see PriorityList.
         */
        template<typename T, std::size_t MAX_ELEMENTS>
        class PriorityMultiQueue
        {
        public:
            
            /**
             *
             */
            PriorityMultiQueue()
            {
            
            }
            
            /**
             *
             */
            ~PriorityMultiQueue()
            {
            
            }

            /**
             * Enqueues the element inside of the specified priority queue.
             *
             * \return TRUE if successfully enqueued.
             */
            bool enqueue(T const element, Core::EVENT_PRIORITY priority)
            {
                bool result = false;

                switch(priority)
                {
                case Core::EVENT_PRIORITY::CRITICAL:
                    result = m_CriticalPriority.enqueue(element);
                    break;

                case Core::EVENT_PRIORITY::HIGH:
                    result = m_HighPriority.enqueue(element);
                    break;

                case Core::EVENT_PRIORITY::MEDIUM:
                    result = m_MediumPriority.enqueue(element);
                    break;

                case Core::EVENT_PRIORITY::LOW:
                    result = m_LowPriority.enqueue(element);
                    break;
                    
                default:
                    break;
                }

                return result;
            }

            /**
             * Dequeues the first available element from the priority queues.<br/>
             * The queues are attempted to be dequeued in this order:<br/><br/>
             *
             * <ul>
             *     <li>Critical</li>
             *     <li>High</li>
             *     <li>Medium</li>
             *     <li>Low</li>
             * </ul>
             *
             * \param[out] retElement The element removed from the queue.
             * \return TRUE if an element was successfully dequeued.
             */
            bool dequeue()
            {
                // Short-circuit evaluation ensures that we will 
                // return once a successful dequeue has occurred.

                return m_CriticalPriority.dequeue() ||
                       m_HighPriority.dequeue()     ||
                       m_MediumPriority.dequeue()   ||
                       m_LowPriority.dequeue();
            }
            
            /**
             * Dequeues the first available element from the priority queues.<br/>
             * The queues are attempted to be dequeued in this order:<br/><br/>
             *
             * <ul>
             *     <li>Critical</li>
             *     <li>High</li>
             *     <li>Medium</li>
             *     <li>Low</li>
             * </ul>
             *
             * \param[out] retElement The element removed from the queue.
             * \return TRUE if an element was successfully dequeued.
             */
            bool dequeue(T& retElement)
            {
                // Short-circuit evaluation ensures that we will 
                // return once a successful dequeue has occurred.

                return m_CriticalPriority.dequeue(retElement) ||
                       m_HighPriority.dequeue(retElement)     ||
                       m_MediumPriority.dequeue(retElement)   ||
                       m_LowPriority.dequeue(retElement);
            }
            
            /**
             * Dequeues the element at the front of the specified queue.
             *
             * \param[out] retElement The element removed from the queue.
             * \return TRUE if an element was successfully dequeued.
             */
            bool dequeue(Core::EVENT_PRIORITY priority, T& retElement)
            {
                bool result = false;

                switch(priority)
                {
                case Core::EVENT_PRIORITY::CRITICAL:
                    result = m_CriticalPriority.dequeue(element);
                    break;

                case Core::EVENT_PRIORITY::HIGH:
                    result = m_HighPriority.dequeue(element);
                    break;

                case Core::EVENT_PRIORITY::MEDIUM:
                    result = m_MediumPriority.dequeue(element);
                    break;

                case Core::EVENT_PRIORITY::LOW:
                    result = m_LowPriority.dequeue(element);
                    break;
                    
                default:
                    break;
                }

                return result;
            }

            /**
             * \return Total number of elements across all priority levels.
             */
            unsigned getNumElements() const 
            {
                return getNumElementsCritical() +
                       getNumElementsHigh() +
                       getNumElementsMedium() +
                       getNumElementsLow();
            }

            /**
             * \return Number of elements in the Critical priority queue.
             */
            unsigned getNumElementsCritical() const
            {
                return m_CriticalPriority.getNumElements();
            }
            
            /**
             * \return Number of elements in the High priority queue.
             */
            unsigned getNumElementsHigh() const
            {
                return m_HighPriority.getNumElements();
            }
            
            /**
             * \return Number of elements in the Medium priority queue.
             */
            unsigned getNumElementsMedium() const
            {
                return m_MediumPriority.getNumElements();
            }
            
            /**
             * \return Number of elements in the Low priority queue.
             */
            unsigned getNumElementsLow() const
            {
                return m_LowPriority.getNumElements();
            }

            /**
             * \return TRUE if container is empty.
             */
            bool empty()
            {
                return (getNumElements() == 0);
            }

            void clear()
            {
                while(dequeue());
            }

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