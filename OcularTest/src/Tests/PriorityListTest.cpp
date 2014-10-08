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

#include "Tests/PriorityListTest.hpp"
#include "Utilities/Structures/PriorityList.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Tests
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PriorityListTest::PriorityListTest()
            : ATest("PriorityListTest")
        {
            m_FooA = std::make_shared<Foo>("FooA");
            m_FooB = std::make_shared<Foo>("FooB");
            m_FooC = std::make_shared<Foo>("FooC");
            m_FooD = std::make_shared<Foo>("FooD");
            m_FooE = std::make_shared<Foo>("FooE");
        }

        PriorityListTest::~PriorityListTest()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void PriorityListTest::run()
        {
            RUN_TEST(testAdd);
            RUN_TEST(testContains);
            RUN_TEST(testRemoveElement);
            RUN_TEST(testRemoveIndex);

            ATest::run();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    
        void PriorityListTest::testAdd()
        {
            m_List.add(m_FooA, 0);
            m_List.add(m_FooB, 1);
            m_List.add(m_FooC, 2);
            m_List.add(m_FooD, 3);

            EXPECT_TRUE((m_List.size() == 4));
        }

        void PriorityListTest::testContains()
        {
            EXPECT_TRUE(m_List.contains(m_FooC));
            EXPECT_FALSE(m_List.contains(m_FooE));
        }

        void PriorityListTest::testRemoveElement()
        {
            m_List.removeElement(m_FooC);

            EXPECT_FALSE(m_List.contains(m_FooC));
            EXPECT_TRUE((m_List.size() == 3));
        }

        void PriorityListTest::testRemoveIndex()
        {
            m_List.removeIndex(1);

            EXPECT_FALSE(m_List.contains(m_FooB));
            EXPECT_TRUE((m_List.size() == 2));
        }
    }
}