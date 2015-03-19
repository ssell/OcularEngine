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
#ifndef __H__OCULAR_SYSTEM_INFO__
#define __H__OCULAR_SYSTEM_INFO__

#include "FileIO/Directory.hpp"

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
        enum class OperatingSystems : unsigned
        {
            UNKNOWN = 0,
            WINDOWS
        };

        enum class ProcessorArchitectures : unsigned
        {
            UNKNOWN = 0,
            X86,
            X64,
            ARM,
            IA64
        };

        enum class Endianness : unsigned
        {
            UNKNOWN = 0,
            BIG_ENDIAN,
            LITTLE_ENDIAN
        };

        enum class OpenGLLevels : unsigned 
        {
            UNKNOWN = 0,
            NONE
        };

        enum class DirectXLevels : unsigned 
        {
            UNKNOWN = 0,
            NONE
        };

        //----------------------------------------------------------------------------------

        /**
         * \class SystemInfo
         *
         * Static class that collects many pieces of useful system information such as OS, 
         * architecture, supported graphics APIs, etc.
         */
        class SystemInfo
        {
        public:

            SystemInfo();
            ~SystemInfo();

            static bool refresh();

            /**
             * Returns the current running Operating System.
             */
            static OperatingSystems getOperatingSystem();

            /**
             * Returns the processor architecture for the system.
             */
            static ProcessorArchitectures getProcessorArchitecture();

            /**
             * Returns the endianness of the system.
             */
            static Endianness getEndianness();

            /**
             * Returns the level of OpenGL support on this system.
             */
            static OpenGLLevels getOpenGLSupportLevel();

            /**
             * Returns the level of DirectX support on this system.
             */
            static DirectXLevels getDirectXSupportLevel();

            /**
             * Returns the total amount of RAM on this system (both used and unused) (in bytes).
             * \note A return value of -1 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static long long getTotalRAM();

            /**
             * Returns the total amount of RAM that is free and not in use on the system (in bytes).
             * \note A return value of -1 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static long long getFreeRAM();

            /**
             * Returns the total amount of memory on the GPUs (both used and unused) (in bytes).
             * \note A return value of -1 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static long long getTotalGPUMemory();

            /**
             * Returns the total amount of memory that is free and not in use on the GPUs (in bytes).
             * \note A return value of -1 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static long long getFreeGPUMemory();

            /**
             * Returns number of output channels (monitors, etc.) on the system.
             * \note A return value of -1 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static int getNumberOfChannels();

            /**
             * Returns the directory that the executable is running from.
             */
            static Core::Directory getWorkingDirectory();

        protected:

        private:

            static OperatingSystems m_OperatingSystem;
            static ProcessorArchitectures m_ProcessorArchitecture;
            static Endianness m_Endianness;
            static OpenGLLevels m_OpenGLLevel;
            static DirectXLevels m_DirectXLevel;

            static long long m_TotalRAM;
            static long long m_FreeRAM;
            static long long m_TotalGPUMemory;
            static long long m_FreeGPUMemory;

            static int m_NumberOfChannels;

            static Core::Directory m_WorkingDirectory;
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
