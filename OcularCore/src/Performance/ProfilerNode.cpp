/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Performance/ProfilerNode.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        ProfilerNode::ProfilerNode(ProfilerNode* parent, std::string const& name, std::string const& segment)
            : parent(parent), name(name), segment(segment)
        {
            totalCalls     = 0;
            totalElapsed   = 0;
            localElapsed   = 0;
            blockStart     = 0;
            blockDepth     = 0;
            recursiveDepth = 0;
        }

        ProfilerNode::~ProfilerNode()
        {
            parent = nullptr;
            children.clear();
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool ProfilerNode::operator==(ProfilerNode const* rhs)
        {
            bool result = false;

            if(rhs)
            {
                result = (name.compare(rhs->name) == 0);

                if(result)
                {
                    result = (name.compare(rhs->segment) == 0);
                }
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}