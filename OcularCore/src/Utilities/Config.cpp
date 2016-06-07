/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "Utilities/Config.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Utils
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Config::Config()
        {

        }

        Config::~Config()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool Config::read(Core::File const& file)
        {
            bool result = false;

            return result;
        }

        std::string Config::get(std::string const& option)
        {
            std::string result;
            auto find = m_ConfigOptions.find(option);

            if(find != m_ConfigOptions.end())
            {
                result = (*find).second;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool Config::isValidFile(Core::File const& file)
        {
            bool result = true;

            if(!file.exists())
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': file does not exist", OCULAR_INTERNAL_LOG("Config", "isValidFile"));
                result = false;
            }

            if(!file.canRead())
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': improper read permissions", OCULAR_INTERNAL_LOG("Config", "isValidFile"));
                result = false;
            }

            if(!Utils::String::IsEqual(file.getExtension(), ".oconf"))
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': invalid file extension (expected '.oconf')", OCULAR_INTERNAL_LOG("Config", "isValidFile"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}