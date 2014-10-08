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
#ifndef __H__OCULAR_TESTS_PRIORITY_LIST__H__
#define __H__OCULAR_TESTS_PRIORITY_LIST__H__

#include "Tests/ATest.hpp"
#include "Utilities/Structures/PriorityList.hpp"

#include <memory>

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
        * \class PriorityListTest
        */
        class PriorityListTest : public ATest
        {
        public:

            PriorityListTest();
            ~PriorityListTest();

            virtual void run();

        protected:

            void testAdd();
            void testContains();
            void testRemoveElement();
            void testRemoveIndex();

        private:

            Utils::PriorityList<std::shared_ptr<Foo>, 8> m_List;

            std::shared_ptr<Foo> m_FooA;
            std::shared_ptr<Foo> m_FooB;
            std::shared_ptr<Foo> m_FooC;
            std::shared_ptr<Foo> m_FooD;
            std::shared_ptr<Foo> m_FooE;
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