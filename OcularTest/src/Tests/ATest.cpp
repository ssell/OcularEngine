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

#include "Tests/ATest.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Tests
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ATest::ATest(std::string name)
            : m_Name(name)
        {
            m_NumTests = 0;
            m_NumFailures = 0;
            m_CurrentTest = "";
        }

        ATest::~ATest()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void ATest::run()
        {
            OcularEngine.Logger()->info(
                m_Name, " complete with ", m_NumFailures, 
                " tests failed (", m_NumTests, " total)");

            for (unsigned i = 0; i < m_NumFailures; i++)
            {
                OcularEngine.Logger()->info("\t- Failed: ", m_Failures[i].first, " @ line ", m_Failures[i].second);
            }
        }

        void ATest::fail(unsigned line)
        {
            m_NumFailures++;
            m_Failures.push_back(std::pair<std::string, unsigned>(m_CurrentTest, line));
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}