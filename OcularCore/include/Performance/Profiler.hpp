/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
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

#include "ProfilerNode.hpp"
#include "ProfilerScope.hpp"

#include <sstream>

//------------------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------------------

//#define OCULAR_PERFORM_PROFILING

#ifdef OCULAR_PERFORM_PROFILING
#define OCULAR_PROFILE()         Ocular::Core::ProfilerScope OCULAR_INTERNAL_PROFILE_SCOPE(BOOST_CURRENT_FUNCTION);
#define OCULAR_PROFILE_START(x)  OcularEngine.Profiler()->beginBlock(BOOST_CURRENT_FUNCTION, x);
#define OCULAR_PROFILE_STOP()    OcularEngine.Profiler()->endBlock();
#else
#define OCULAR_PROFILE()
#define OCULAR_PROFILE_START(x) do { } while(false);
#define OCULAR_PROFILE_STOP() 
#endif


//------------------------------------------------------------------------------------------
// Classes
//------------------------------------------------------------------------------------------

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
         * Which results in the following output (when printed to console or as plain-text):
         *
         *     - ParentMethod [1] [100.0ms] [100.0ms]
         *       - ChildMethod [1] [100.0ms] [100.0ms]
         *         - SubchildMethod "Segment A" [1] [50.0ms] [50.0ms]
         *         - SubchildMethod "Segment B" [1] [50.0ms] [50.0ms]
         *
         * The output lines are formatted as follows:
         *
         *     Name Segment Calls Elapsed Average 
         *
         * Where,
         *
         *          Name: Name of the profiled function/method
         *       Segment: Name of the block segment (optional)
         *         Calls: Total amount of times this segment of code had been called
         *       Elapsed: Total amount of elapsed time spent in the code segment
         *       Average: Average amount of time spent executing the code segment
         */
        class Profiler
        {
        public:

            Profiler();
            ~Profiler();

            /**
             * Begins a new block of code to profile.
             *
             * \param[in] name    Name of the code block.
             * \param[in] segment Optional segment name if part of a larger block of profiled code.
             *                    Use this if, for example, you are profiling multiple individual
             *                    segments of a single function.
             */
            void beginBlock(std::string const& name, std::string const& segment);

            /**
             * Ends the current profile block.
             */
            void endBlock();

            /**
             * Prints the current profiler data to the console (standard out).
             *
             * \param[in] prettify If TRUE, function signatures are trimmed to just their names (namespace::class:method).
             */
            void printToConsole(bool prettify = true) const;

            /**
             * Prints the current profiler data to the specified .txt file. Output is formatted in the same
             * manner as the prettified console output.
             *
             * \param[in] path File path to output the data to (expects a .txt)
             */
            void printToTXT(std::string const& path) const;

            /**
             * Prints the current profiler data as a pre-formatted HTML/JS tree table to the specified location.
             *
             * \param[in] path File path to output the data to (expects a .html)
             */
            void printToHTML(std::string const& path) const;

        protected:

            void destroy();
            void destroyNode(ProfilerNode* node) const;

            void createLogBuffer(std::stringstream& stream, bool prettify) const;
            void createLogForNode(ProfilerNode* node, std::stringstream& stream, bool prettify) const;

            std::string prettifyName(std::string const& name) const;

        private:

            ProfilerNode* m_RootNode;
            ProfilerNode* m_CurrentNode;
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