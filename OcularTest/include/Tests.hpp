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
#ifndef __H__OCULAR_TESTS_TESTS__H__
#define __H__OCULAR_TESTS_TESTS__H__

#include "Tests/PriorityListTest.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Tests
    {
        static const std::vector<std::shared_ptr<ATest>> Tests =
        {
            std::make_shared<PriorityListTest>()
        };

        static void RunTests()
        {
            for(unsigned i = 0; i < Tests.size(); i++)
            {
                Tests[i]->run();
            }
        }
    }
}

//------------------------------------------------------------------------------------------

#endif