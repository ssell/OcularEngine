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
#ifndef __H__OCULAR_SYSTEM_INFO__
#define __H__OCULAR_SYSTEM_INFO__

#include "FileIO/Directory.hpp"
#include "Common.hpp"

#include <cstdint>

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

            /**
             * Populates with all available system info.
             */
            static void initialize();

            /**
             * Forces a refresh of variables that can change during program lifetime. These include:
             *
             *     - Available RAM
             *     - Available GPU Memory
             *     - Available Channels
             *
             * This method is called automatically at the start of each frame.
             */
            static void refresh();

            /**
             * Helper method that logs all current system information.
             */
            static void logSystemInfo();

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
             * Returns the total amount of physical RAM on this system (in bytes).
             * \note A return value of 0 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static uint64_t getTotalRAM();

            /**
             * Returns the total amount of physical RAM that is available on the system (in bytes).
             * \note A return value of 0 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static uint64_t getFreeRAM();

            /**
             * Returns the total amount of memory on the GPUs (both used and unused) (in bytes).
             * \note A return value of 0 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static uint64_t getTotalGPUMemory();

            /**
             * Returns the total amount of memory that is free and not in use on the GPUs (in bytes).
             * \note A return value of 0 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static uint64_t getFreeGPUMemory();

            /**
             * Returns number of output channels (monitors, etc.) on the system.
             * \note A return value of 0 indicates unknown. Either Ocular failed to retrieve the data, or refresh needs to be called.
             */
            static uint32_t getNumberOfChannels();

            /**
             * Returns the number of supported concurrent threads.
             */
            static uint32_t getNumberOfThreads();

            /**
             * Returns the directory that the executable is running from.
             */
            static Core::Directory getWorkingDirectory();

        protected:

            //----------------------------------------
            // System specifics that should not change during program runtime.
            // These are called in initialize

            static void discoverOperatingSystem();
            static void discoverProcessorArchitecture();
            static void discoverEndianness();
            static void discoverOpenGLLevel();
            static void discoverDirectXLevel();
            static void discoverInstalledRAM();
            static void discoverInstalledGPUMemory();
            static void discoverNumberOfThreads();

            //----------------------------------------
            // System specific that can change during program runtime
            // These are called in refresh

            static void discoverAvailableGPUMemory();
            static void discoverAvailableRAM();
            static void discoverChannels();

        private:

            static OperatingSystems m_OperatingSystem;
            static ProcessorArchitectures m_ProcessorArchitecture;
            static Endianness m_Endianness;
            static OpenGLLevels m_OpenGLLevel;
            static DirectXLevels m_DirectXLevel;

            static uint64_t m_TotalRAM;
            static uint64_t m_FreeRAM;
            static uint64_t m_TotalGPUMemory;
            static uint64_t m_FreeGPUMemory;

            static uint32_t m_NumberOfChannels;
            static uint32_t m_NumberOfThreads;

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
