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
#ifndef __H__OCULAR_UTILS_CIRCULAR_QUEUE__H__
#define __H__OCULAR_UTILS_CIRCULAR_QUEUE__H__

#include <array>

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
         * \class CircularQueue
         *
         * Implementation of a circular queue with O(1) push and pop.
         */
        template<typename T, std::size_t MAX_ELEMENTS>
        class CircularQueue
        {
        public:

            /**
             * \param[in] size Starting size of the internal array.
             */
            CircularQueue()
                : m_Last(MAX_ELEMENTS - 1), m_Head(0), m_Tail(0), m_NumElements(0)
            {
            }

            /**
             *
             */
            ~CircularQueue()
            {
            }

            /**
            * Adds the element to the queue.
            *
            * \return TRUE if successfully enqueued.
            */
            bool enqueue(T const element)
            {
                bool retVal = false;

                if(m_NumElements < MAX_ELEMENTS)
                {
                    m_Array[m_Tail] = element;
                    incrementTail();
                    retVal = true;
                }

                return retVal;
            }

            /**
             * Dequeues an element from the queue if it is not empty.
             *
             * \param[out] retElement The element removed from the queue.
             * \return TRUE if an element was successfully dequeued.
             */
            bool dequeue(T& retElement)
            {
                bool retVal = false;

                if(m_NumElements > 0)
                {
                    retElement = m_Array[m_Head];
                    
                    incrementHead();
                    retVal = true;
                }

                return retVal;
            }

            bool dequeue()
            {
                bool retVal = false;

                if(m_NumElements > 0)
                {
                    incrementHead();
                    retVal = true;
                }

                return retVal;
            }

            /**
            * \param[out] retElement Element at the front of the queue.
            * \return TRUE if an element is available to view.
            */
            bool peek(T& retElement)
            {
                bool retVal = false;;

                if(m_NumElements > 0)
                {
                    retElement = m_Array[m_Head];
                    retVal = true;
                }
                
                return retVal;
            }

            /**
            * \return Current number of elements in the queue.
            */
            unsigned getNumElements() const
            {
                return m_NumElements;
            }

        protected:

        private:

            /**
            *
            */
            void incrementHead()
            {
                if (m_NumElements > 0)
                {
                    
                    if (m_Head != m_Last)
                    {
                        m_Head++;
                    }
                    else
                    {
                        m_Head = 0;
                    }

                    m_NumElements--;
                }
            }

            /**
            *
            */
            void incrementTail()
            {
                if (m_NumElements < MAX_ELEMENTS)
                {
                    if (m_Tail != m_Last)
                    {
                        m_Tail++;
                    }
                    else
                    {
                        m_Tail = 0;
                    }

                    m_NumElements++;
                }
            }

            //----------------------------------------

            unsigned m_NumElements;
            unsigned m_Head;
            unsigned m_Tail;
            unsigned m_Last;

            std::array<T, MAX_ELEMENTS> m_Array;
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