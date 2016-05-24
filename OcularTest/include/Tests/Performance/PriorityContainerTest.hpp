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
#ifndef __H__OCULAR_TEST_PRIORITY_CONTAINER_COMPARISON__H__
#define __H__OCULAR_TEST_PRIORITY_CONTAINER_COMPARISON__H__

#include "Tests/ATest.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Tests
     * @{
     */
    namespace Tests
    {
        /**
         * \class PriorityContainerComparisonTest
         *
         * This tests compares the runtime performance between 
         * the following priority containers:<br/><br/>
         *
         * <ul>
         *     <li>STL PriorityQueue</li>
         *     <li>Ocular PriorityMultiQueue</li>
         *     <li>Ocular PriorityList</li>
         * </ul><br/><br/>
         *
         * The test performs an X amount of random, but identical, 
         * actions. The actions tested are:<br/><br/>
         *
         * <ul>
         *     <li>Enqueue/Add</li>
         *     <li>Dequeue/Remove</li>
         *     <li>Remove All</li>
         * </ul><br/><br/>
         *
         * It tests these actions the following amount of times:<br/><br/>
         *
         * <ul>
         *     <li>10</li>
         *     <li>100</li>
         *     <li>1000</li>
         *     <li>10000</li>
         *     <li>100000</li>
         *     <li>1000000</li>
         *     <li>10000000</li>
         * </ul><br/><br/>
         *
         * Since this is a performance test, it may take a non-trivial amount
         * of time to complete, and thus should not be run as part of the 
         * normal testing package.
         *
         */
        class PriorityContainerComparisonTest : public ATest 
        {
        public:

            PriorityContainerComparisonTest();
            ~PriorityContainerComparisonTest();

            virtual void run() override;

        protected:

            void testSTLPriorityQueue();
            void testPriorityMultiQueue();
            void testPriorityList();

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