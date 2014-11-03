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

#include "Utilities/Structures/PriorityList.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

TEST(PriorityList, Add)
{
    Ocular::Utils::PriorityList<int, 16> list;
    list.add(5, 0);

    EXPECT_EQ(1, list.size());
}

TEST(PriorityList, Contains)
{
    Ocular::Utils::PriorityList<int, 16> list;
    list.add(5, 0);

    EXPECT_FALSE(list.contains(4));
    EXPECT_TRUE(list.contains(5));
}

TEST(PriorityList, RemoveElement)
{
    Ocular::Utils::PriorityList<int, 16> list;
    list.add(5, 0);

    list.removeElement(4);

    EXPECT_EQ(1, list.size());
    
    list.removeElement(5);

    EXPECT_EQ(0, list.size());
}

TEST(PriorityList, RemoveIndex)
{
    Ocular::Utils::PriorityList<int, 16> list;
    list.add(5, 0);

    EXPECT_EQ(1, list.size());

    list.removeIndex(0);

    EXPECT_EQ(0, list.size());
}