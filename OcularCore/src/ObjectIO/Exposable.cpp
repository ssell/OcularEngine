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

#include "ObjectIO/Exposable.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Exposable::getAllExposedNames(std::vector<std::string>& names) const
        {
            names.clear();
            names.reserve(m_ExposedVariables.size());

            for(auto iter : m_ExposedVariables)
            {
                names.emplace_back(iter.first);
            }
        }

        bool Exposable::getVariable(std::string const& name, ExposedVariable& var)
        {
            bool result = false;
            auto find = m_ExposedVariables.find(name);

            if(find != m_ExposedVariables.end())
            {
                var = find->second;
                result = true;
            }

            return result;
        }

        void Exposable::onVariableModified(std::string const& varName)
        {
            // Do nothing
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Exposable::exposeVariable(std::string const& name, std::string const& type, bool isPointer, bool isExposed, void* data)
        {
            auto find = m_ExposedVariables.find(name);
            
            if(find == m_ExposedVariables.end())
            {
                m_ExposedVariables.insert(std::make_pair(name, ExposedVariable(name, type, data, isPointer, isExposed)));
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}