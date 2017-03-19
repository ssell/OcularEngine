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
#ifndef __H__OCULAR_CORE_PERFORMANCE_PROFILER_NODE__H__
#define __H__OCULAR_CORE_PERFORMANCE_PROFILER_NODE__H__

#include <string>
#include <vector>
#include <stdint.h>

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
        class ProfilerNode
        {
        public:

            ProfilerNode(ProfilerNode* parent, std::string const& name, std::string const& segment);
            ~ProfilerNode();

            bool operator==(ProfilerNode const* rhs);

            //------------------------------------------------------------
            // Variables

            std::string name;                        ///< Name of this node (fully qualified method/function name)
            std::string segment;                     ///< Segment name of this node

            uint32_t totalCalls;                     ///< Total amount of times this node has been profiled
            uint32_t blockDepth;                     ///< Depth of the block (used for printing)
            uint32_t recursiveDepth;                 ///< If in a recursive function, the current depth

            uint64_t blockStart;                     ///< Start time (ns) of the latest block
            uint64_t localElapsed;                   ///< Amount of time elapsed in the local block
            uint64_t totalElapsed;                   ///< Total amount of time elapsed

            ProfilerNode* parent;                    ///< Parent node (null if root)
            std::vector<ProfilerNode*> children;     ///< Children nodes

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