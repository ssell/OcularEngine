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
#ifndef __H__OCULAR_TESTS_ITEST__H__
#define __H__OCULAR_TESTS_ITEST__H__

// Includes that nearly every test uses
#include "OcularEngine.hpp"
#include "Foo.hpp"
#include <vector>

//------------------------------------------------------------------------------------------

#define OCULAR_RUN_TEST(funcName) m_CurrentTest = #funcName; m_NumTests++; funcName();
#define OCULAR_FAIL_TEST          fail(__LINE__); return;
#define OCULAR_EXPECT_TRUE(expr)  if(!expr){ OCULAR_FAIL_TEST }
#define OCULAR_EXPECT_FALSE(expr) if(expr){ OCULAR_FAIL_TEST }

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
         * \class ATest
         */
        class ATest
        {
        public:

            ATest(std::string name);
            virtual ~ATest();

            virtual void run();

        protected:

            void fail(unsigned line);

            std::string m_CurrentTest;
            std::string m_Name;

            unsigned m_NumTests;
            unsigned m_NumFailures;

            std::vector<std::pair<std::string, unsigned>> m_Failures;

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