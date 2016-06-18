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

#pragma once
#ifndef __H__OCULAR_UTILITIES_CONFIG__H__
#define __H__OCULAR_UTILITIES_CONFIG__H__

#include "FileIO/File.hpp"

#include <string>
#include <unordered_map>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Utils
     * @{
     */
    namespace Utils
    {
        /**
         * \class Config
         *
         * Simple configuration utility.
         *
         * Configuration options can be retrieved or set via the get and set methods:
         *
         *    std::string resolutionX = config->get("ResolutionX");
         *    config->set("ResolutionY", 600);
         *
         * All options are returned and set as strings. These strings can be converted
         * to other types via the Ocular::Utils::String helper class (see OcularString).
         *
         * There can be any number of configuration files in use, but the engine itself
         * uses only one. This file is expected to be at 'engine.oconf' in the same 
         * directory as the executable being run.
         *
         * If this configuration file is missing, it should generally be re-generated 
         * automatically by the engine during initialization. If it fails to be created,
         * then one can be downloaded from: ...
         */
        class Config
        {
        public:

            Config();
            ~Config();

            //------------------------------------------------------------

            /**
             * Reads the set configuration file and populates the options map with it's contents.
             */
            bool read();

            /**
             * Overwrites the set configuration file with the current contents of the options map.
             */
            bool write();

            /**
             * Sets the configuration (.oconf) file to read from/write to.
             *
             * \param[in] file
             */
            void setFile(Core::File const& file);

            /**
             * Retrieves the value of the specified option. If the option is not present, returns an empty string.
             *
             * The validity of an option may be checked via hasOption.
             *
             * The returned value may be converted to a non-string type via OcularString->fromString
             *
             * \param[in] option String option name
             * \return String option value
             */
            std::string get(std::string const& option) const; 

            /**
             * Sets the value of the specified option.
             *
             * \param[in] option
             * \param[in] value
             */
            void set(std::string const& option, std::string const& value);
                                            
        protected:
            
            bool isValidReadFile(Core::File const& file) const;
            bool isValidWriteFile(Core::File const& file) const;

        private:

            Core::File m_File;

            std::unordered_map<std::string, std::string> m_ConfigOptions;     ///< Key: option name; Value: option value
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