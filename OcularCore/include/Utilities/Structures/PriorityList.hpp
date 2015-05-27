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
#ifndef __H__OCULAR_UTILS_PRIORITY_LIST__H__
#define __H__OCULAR_UTILS_PRIORITY_LIST__H__

#include "Exceptions/Exception.hpp"
#include "Priority.hpp"

#include <utility>

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
         * \class PriorityList
         */
        template<typename T, std::size_t MAX_ELEMENTS>
        class PriorityList
        {
        public:

            /**
             *
             */
            PriorityList()
            {
                m_TrueSize = 0;
            }

            /**
             *
             */
            ~PriorityList()
            {

            }

            /**
             * Pushes the element onto the list.
             *
             * \param[in] element 
             * \param[in] priority Priority level of the element. Lower is higher priority.
             *
             * \return TRUE if push was successful.
             */
            bool push(T const element, uint32_t priority)
            {
                bool retVal = false;

                if(m_TrueSize < MAX_ELEMENTS)
                {
                    retVal = add(element, priority);
                }

                return retVal;
            }

            /**
             * Removes the element with highest priority.
             *
             * \return TRUE if pop was successful.
             */
            bool pop()
            {
                bool retVal = false;

                if(m_TrueSize > 0)
                {
                    removeIndex(0);
                    retVal = true;
                }

                return retVal;
            }

            /**
             * Attempts to add the provided element into the priority list.
             *
             * \param[in] element 
             * \param[in] priority Priority level of the element. Lower is higher priority.
             *
             * \return TRUE if successfully inserted, else FALSE. 
             *         May only fail if list if full.
             */
            bool add(T const element, uint32_t priority)
            {
                bool result = false;

                if(m_TrueSize < MAX_ELEMENTS)
                {
                    insertElement(element, static_cast<uint32_t>(priority));
                    m_TrueSize++;
                    result = true;
                }

                return result;
            }

            /**
            * Removes the specified element if it exists.
            */
            void removeElement(T const element)
            {
                if(m_TrueSize > 0)
                {
                    std::size_t index = locateIndex(element);

                    if(index != MAX_ELEMENTS)
                    {
                        deleteElement(index);
                        m_TrueSize--;
                    }
                }
            }

            /**
             * Removes the element at the specified index.<br/>
             * Throws an exception if index is out of bounds.
             */
            void removeIndex(unsigned index)
            {
                if(index >= m_TrueSize)
                {
                    THROW_EXCEPTION("Index Out of Bounds");
                }

                deleteElement(index);
                m_TrueSize--;
            }

            /**
             * \return The element at the specified index. If the element
             * (or the index) does not exist, then null is returned.
             */
            T const get(std::size_t index) const
            {
                if(index >= m_TrueSize)
                {
                    THROW_EXCEPTION("Index Out of Bounds");
                }

                return m_Array[index].first;
            }

            /**
             * \return Number of elements currently tracked.
             */
            std::size_t size() const
            {
                return m_TrueSize;
            }

            /**
             * \return Maximum number of elements possible to track.
             */
            std::size_t maxSize() const
            {
                return MAX_ELEMENTS;
            }

            /**
             * \return TRUE if list is empty
             */
            bool empty() const 
            {
                return (m_TrueSize == 0);
            }

            /**
             * \return TRUE if the list contains an element that
             * matches the one specified.
             */
            bool contains(T const element) const
            {
                std::size_t index = locateIndex(element);
                return (index != MAX_ELEMENTS);
            }

            /**
             * Removes all elements from the list.
             */
            void clear() 
            {
                while(size() > 0)
                {
                    removeIndex(0);
                }
            }

        protected:

            /**
             * Inserts the element into the specified index into the internal array.
             */
            void insertElement(T const element, unsigned const priority)
            {
                std::size_t index = findIndex(priority);

                shiftRight(index);
                m_Array[index] = std::pair<T, unsigned>(element, priority);
            }

            /**
             * Removes the element at the specified index from the internal array.
             */
            void deleteElement(std::size_t const index)
            {
                //m_Array[index].first = 0;
                shiftLeft(index);
            }

            /**
             * Shifts all elements from the provided index and onwards to the left.<br/>
             * Used in element removal.
             */
            void shiftLeft(std::size_t const index)
            {
                // Effectively does the following (shiftLeft(3)):
                //
                //          [0][1][2][3][4][5][6][7][8][9]
                // Before:  [*][*][*][ ][*][*][*][*][ ][ ]
                //  After:  [*][*][*][*][*][*][*][ ][ ][ ]

                for(std::size_t i = index; i < m_TrueSize - 1; i++)
                {
                    m_Array[i] = m_Array[i + 1];
                }

                //m_Array[m_TrueSize - 1].first = 0;
            }

            /**
             * Shifts all elements from the provided index and onwards to the right.<br/>
             * Used in element insertion.
             */
            void shiftRight(std::size_t const index)
            {
                // Effectively does the following (shiftRight(3)):
                //
                // Before:  [0][1][2][3][4][5][6][ ][ ][ ]
                //  After:  [0][1][2][ ][3][4][5][6][ ][ ]
                
                if(m_TrueSize != MAX_ELEMENTS)
                {
                    for(std::size_t i = m_TrueSize; i > index; i--)
                    {
                        m_Array[i] = m_Array[i - 1];
                    }

                    //m_Array[index].first = 0;
                }
            }

            /**
             * Finds and returns the index that matches the provided element.<br/>
             * If the element is not found, return MAX_ELEMENTS.
             */
            std::size_t locateIndex(T const element) const
            {
                std::size_t index = MAX_ELEMENTS;

                for(std::size_t i = 0; i < m_TrueSize; i++)
                {
                    if(m_Array[i].first == element)
                    {
                        index = i;
                        break;
                    }
                }

                return index;
            }

            /**
             * Finds and returns the index that best fits the given priority level.
             */
            std::size_t findIndex(unsigned const priority) const
            {
                // If the array is empty, return index 0
                if(m_TrueSize == 0) 
                {
                    return 0;
                }

                // Quick check to see if we should insert at the front
                // or at the back of the list.
                if(priority < m_Array[0].second)
                {
                    return 0;
                }
                else if(priority > m_Array[m_TrueSize - 1].second)
                {
                    return m_TrueSize;
                }

                return binaryFind(priority);
            }

            /**
             * Performs a binary search on the internal priority list and returns
             * the best fit index for the given priority level.
             */
            std::size_t binaryFind(unsigned const priority) const
            {
                unsigned upper = m_TrueSize;
                unsigned index = m_TrueSize / 2;
                unsigned increment = index / 2;

                // While this could be done in a while(true){}, we
                // place an upper bound on the potential number of
                // iterations to avoid any (unlikely) infinite loops.

                for( ; upper > 0; upper--, increment /= 2)
                {
                    if (increment == 0)
                    {
                        increment = 1;
                    }

                    if(m_Array[index].second == priority)
                    {
                        break;
                    }
                    else if (m_Array[index].second > priority)
                    {
                        // If we are at the front of the list we can not go any further
                        if(index == 0)
                        {
                            break;
                        }

                        index -= increment;
                    }
                    else
                    {
                        // If we are at the end of the list we can not go any further
                        if((index == m_TrueSize) || (index == MAX_ELEMENTS - 1))
                        {
                            break;
                        }

                        index += increment;
                    }
                }

                return index;
            }

        private:

            std::size_t m_TrueSize;    ///< Actual number of elements in the storage array
            //std::array<std::pair<T, unsigned>, MAX_ELEMENTS> m_Array;
            std::pair<T, std::size_t> m_Array[MAX_ELEMENTS] = {};
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