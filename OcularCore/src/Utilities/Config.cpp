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

#include "pugixml/pugixml.hpp"

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

        bool Config::read()
        {
            bool result = false;

            if(isValidReadFile(m_File))
            {
                m_ConfigOptions.clear();

                pugi::xml_document document;
                pugi::xml_parse_result parseResult = document.load_file(m_File.getFullPath().c_str());

                if(parseResult)
                {
                    pugi::xml_node rootNode = document.child("OcularConfig");

                    for(auto child : rootNode.children())
                    {
                        m_ConfigOptions[child.name()] = child.text().as_string();
                    }

                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to parse Config file at '", m_File.getFullPath(), "' with error: ", parseResult.description(), OCULAR_INTERNAL_LOG("Config", "read"));
                }
            }
            else
            {
                OcularLogger->error("Config file at '", m_File.getFullPath(), "' is invalid", OCULAR_INTERNAL_LOG("Config", "read"));
            }

            return result;
        }

        bool Config::write()
        {
            bool result = false;

            if(isValidWriteFile(m_File))
            {
                pugi::xml_document document;
                pugi::xml_node rootNode = document.append_child("OcularConfig");

                for(auto keyValue : m_ConfigOptions)
                {
                    pugi::xml_node child = rootNode.append_child(keyValue.first.c_str());

                    if(child)
                    {
                        child.append_child(pugi::xml_node_type::node_pcdata).set_value(keyValue.second.c_str());
                    }
                }

                if(document.save_file(m_File.getFullPath().c_str(), "    "))
                {
                    result = true;
                }
                else
                {
                    OcularLogger->error("Failed to write to config file at '", m_File.getFullPath(), "'", OCULAR_INTERNAL_LOG("Config", "write"));
                }
            }
            else
            {
                OcularLogger->error("Config file at '", m_File.getFullPath(), "' is invalid", OCULAR_INTERNAL_LOG("Config", "write"));
            }

            return result;
        }

        void Config::setFile(Core::File const& file)
        {
            m_File = file;
        }

        std::string Config::get(std::string const& option) const
        {
            std::string result;
            auto find = m_ConfigOptions.find(option);

            if(find != m_ConfigOptions.end())
            {
                result = (*find).second;
            }

            return result;
        }

        void Config::set(std::string const& option, std::string const& value)
        {
            m_ConfigOptions[option] = value;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool Config::isValidReadFile(Core::File const& file) const
        {
            bool result = true;

            if(!file.exists())
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': file does not exist", OCULAR_INTERNAL_LOG("Config", "isValidReadFile"));
                result = false;
            }

            if(!file.canRead())
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': improper read permissions", OCULAR_INTERNAL_LOG("Config", "isValidReadFile"));
                result = false;
            }

            if(!Utils::String::IsEqual(file.getExtension(), ".oconf"))
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': invalid file extension (expected '.oconf')", OCULAR_INTERNAL_LOG("Config", "isValidReadFile"));
                result = false;
            }

            return result;
        }

        bool Config::isValidWriteFile(Core::File const& file) const
        {
            bool result = true;

            if(!Utils::String::IsEqual(file.getExtension(), ".oconf"))
            {
                OcularLogger->error("Failed to validate config file '", file.getFullPath(), "': invalid file extension (expected '.oconf')", OCULAR_INTERNAL_LOG("Config", "isValidWriteFile"));
                result = false;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}