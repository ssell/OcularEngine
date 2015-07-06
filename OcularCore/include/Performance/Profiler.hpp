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
#ifndef __H__OCULAR_CORE_PERFORMANCE_PROFILER__H__
#define __H__OCULAR_CORE_PERFORMANCE_PROFILER__H__

#include <string>

//------------------------------------------------------------------------------------------

#define PROFILE(x)
#define PROFILE_START(x)
#define PROFILE_END(x)

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class Profiler
         * 
         * A simple CPU performance profiler. Records the amount of time it takes to
         * execute a given segment of code. The profiler may be invoked directly, or 
         * the PROFILE family of macros can be used instead.
         *
         * Performance readings are done in a series of nested blocks, and the results
         * can either be queried at runtime or saved to an external log.
         *
         * In order for profiling to occur, the OCULAR_PROFILE flag must be enabled.
         * By default, all debug builds of the Ocular Engine have this flag enabled.
         *
         * It should be noted that while the act of profiling may cause a slowdown in
         * program performance, the recording results of the profiling are of the true
         * execution time of the code segment. So, deeply nested instances of profiling
         * will not affect the performance readings.
         *
         * There are two different types of profiling: per scope or per designated block.
         * These can be seen in the following example:
         *
         *     void ParentMethod()
         *     {
         *         PROFILE()
         *         ChildMethod();
         *     }
         *
         *     void ChildMethod()
         *     {
         *         PROFILE()
         *
         *         // ...
         *
         *         SubchildMethod();
         *     }
         *
         *     void SubchildMethod()
         *     {
         *         PROFILE_START("Segment A")
         *       
         *         // ...
         *
         *         PROFILE_END()
         *         PROFILE_START("Segment B")
         *
         *         // ...
         *
         *         PROFILE_END()
         *     }
         *
         * Which results in the following log output:
         *
         *     - ParentMethod [100.0ms] [100.0ms] [1]
         *       - ChildMethod [100.0ms] [100.0ms] [1]
         *         - SubchildMethod "Segment A" [50.0ms] [50.0ms] [1]
         *         - SubchildMethod "Segment B" [50.0ms] [50.0ms] [1]
         *
         * The output lines are formatted as follows:
         *
         *     Name Specifier Elapsed Average Calls
         *
         * Where,
         *
         *          Name: Name of the profiled function/method
         *     Specifier: Segment specifier 
         *       Elapsed: Total amount of elapsed time spent in the code segment
         *       Average: Average amount of time spent executing the code segment
         *         Calls: Total amount of times this segment of code had been called
         */
        class Profiler
        {
        public:

            Profiler();
            ~Profiler();

            void beginBlock(std::string name);
            void endBlock();

        protected:

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