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

#include "SystemInfo.hpp"
#include "OcularEngine.hpp"
#include "Common.hpp"
#include "Utilities/StringUtils.hpp"

#ifdef OCULAR_WINDOWS
#include <Windows.h>
#endif

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        OperatingSystems       SystemInfo::m_OperatingSystem       = OperatingSystems::Unknown;
        ProcessorArchitectures SystemInfo::m_ProcessorArchitecture = ProcessorArchitectures::Unknown;
        Endianness             SystemInfo::m_Endianness            = Endianness::Unknown;
        OpenGLLevels           SystemInfo::m_OpenGLLevel           = OpenGLLevels::Unknown;
        DirectXLevels          SystemInfo::m_DirectXLevel          = DirectXLevels::Unknown;
        unsigned long long     SystemInfo::m_TotalRAM              = 0;
        unsigned long long     SystemInfo::m_FreeRAM               = 0;
        unsigned long long     SystemInfo::m_TotalGPUMemory        = 0;
        unsigned long long     SystemInfo::m_FreeGPUMemory         = 0;
        unsigned int           SystemInfo::m_NumberOfChannels      = 0;
        Core::Directory        SystemInfo::m_WorkingDirectory      = Core::Directory();

        //------------------------------------------------------------------------------------------
        // CONSTRUCTORS
        //------------------------------------------------------------------------------------------

        SystemInfo::SystemInfo()
        {
            
        }

        SystemInfo::~SystemInfo()
        {
        
        }

        //------------------------------------------------------------------------------------------
        // PUBLIC METHODS
        //------------------------------------------------------------------------------------------

        void SystemInfo::initialize()
        {
            discoverOperatingSystem();
            discoverProcessorArchitecture();
            discoverEndianness();
            discoverOpenGLLevel();
            discoverDirectXLevel();
            discoverInstalledRAM();
            discoverInstalledGPUMemory();

            refresh();
        }

        void SystemInfo::refresh()
        {
            discoverAvailableRAM();
            discoverAvailableGPUMemory();
            discoverChannels();
        }

        void SystemInfo::logSystemInfo()
        {
           std::string osString      = "Unknown";
           std::string archString    = "Unknown";
           std::string endianString  = "Unknown";
           std::string openglString  = "Unknown";
           std::string directxString = "Unknown";

           //-----------------------------------------

           switch(m_OperatingSystem)
           {
           case OperatingSystems::Windows:
               osString = "Windows";
               break;
           case OperatingSystems::MacOS:
               osString = "Mac OS";
               break;
           case OperatingSystems::Linux:
               osString = "Linux";
               break;
           }

           switch(m_ProcessorArchitecture)
           {
           case ProcessorArchitectures::x86:
               archString = "x86";
               break;

           case ProcessorArchitectures::x64:
               archString = "x64";
               break;

           case ProcessorArchitectures::IA64:
               archString = "Intel Itanium 64";
               break;

           case ProcessorArchitectures::ARM:
               archString = "ARM";
               break;
           }

           switch(m_Endianness)
           {
           case Endianness::BigEndian:
               endianString = "Big Endian";
               break;

           case Endianness::LittleEndian:
               endianString = "Little Endian";
               break;
           }

           /*switch(m_OpenGLLevel)
           {

           }

           switch(m_DirectXLevel)
           {

           }*/

           //-----------------------------------------

           OcularLogger->info("System Information:", 
               "\n\t- Operating System: ", osString, 
               "\n\t- Architecture:     ", archString,
               "\n\t- Endianness:       ", endianString, 
               "\n\t- OpenGL Support:   ", openglString, 
               "\n\t- DirectX Support:  ", directxString, 
               "\n\t- Total RAM:        ", Utils::StringUtils::bytesToString(m_TotalRAM), 
               "\n\t- Free RAM:         ", Utils::StringUtils::bytesToString(m_FreeRAM), 
               "\n\t- Total GPU Memory: ", Utils::StringUtils::bytesToString(m_TotalGPUMemory), 
               "\n\t- Free GPU Memory:  ", Utils::StringUtils::bytesToString(m_FreeGPUMemory),
               "\n\t- Output Channels:  ", m_NumberOfChannels);
        }

        OperatingSystems SystemInfo::getOperatingSystem()
        {
            return m_OperatingSystem;
        }

        ProcessorArchitectures SystemInfo::getProcessorArchitecture()
        {
            return m_ProcessorArchitecture;
        }

        Endianness SystemInfo::getEndianness()
        {
            return m_Endianness;
        }

        OpenGLLevels SystemInfo::getOpenGLSupportLevel()
        {
            return m_OpenGLLevel;
        }

        DirectXLevels SystemInfo::getDirectXSupportLevel()
        {
            return m_DirectXLevel;
        }

        unsigned long long SystemInfo::getTotalRAM()
        {
            return m_TotalRAM;
        }

        unsigned long long SystemInfo::getFreeRAM()
        {
            return m_FreeRAM;
        }

        unsigned long long SystemInfo::getTotalGPUMemory()
        {
            return m_TotalGPUMemory;
        }

        unsigned long long SystemInfo::getFreeGPUMemory()
        {
            return m_FreeGPUMemory;
        }

        unsigned int SystemInfo::getNumberOfChannels()
        {
            return m_NumberOfChannels;
        }

        Core::Directory SystemInfo::getWorkingDirectory()
        {
            return m_WorkingDirectory;
        }

        //------------------------------------------------------------------------------------------
        // PROTECTED METHODS
        //------------------------------------------------------------------------------------------

        void SystemInfo::discoverOperatingSystem()
        {
            // http://sourceforge.net/p/predef/wiki/OperatingSystems/

            if(m_OperatingSystem == OperatingSystems::Unknown)
            {
#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
                m_OperatingSystem = OperatingSystems::Windows;
#elif defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)
                m_OperatingSystem = OperatingSystems::MacOS;
#elif defined(__linux__) || defined(linux) || defined(__linux)
                m_OperatingSystem = OperatingSystems::Linux;
#endif
            }
        }

        void SystemInfo::discoverProcessorArchitecture()
        {
            // http://sourceforge.net/p/predef/wiki/Architectures/

            if(m_ProcessorArchitecture == ProcessorArchitectures::Unknown)
            {
#if defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__I86__) || defined(__386)
                m_ProcessorArchitecture = ProcessorArchitectures::x86;
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
                m_ProcessorArchitecture = ProcessorArchitecture::x64;
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(_M_IA64) || defined(__itanium__)
                m_ProcessorArchitecture = ProcessorArchitecture::IA64;
#elif defined(__arm__) || defined(__thumb__) || defined(_ARM) || defined(_M_ARM) || defined(_M_ARMT) || defined(__arm)
                m_ProcessorArchitecture = ProcessorArchitecture::ARM;
#endif
            }
        }

        void SystemInfo::discoverEndianness()
        {
            if(m_Endianness == Endianness::Unknown)
            {
                union 
                {
                    int  i;
                    char c[4];
                } endianCheck = { 0x01020304 };

                if(endianCheck.c[0] == 1)
                {
                    m_Endianness = Endianness::BigEndian;
                }
                else
                {
                    m_Endianness = Endianness::LittleEndian;
                }
            }
        }

        void SystemInfo::discoverOpenGLLevel()
        {
            if(m_OpenGLLevel == OpenGLLevels::Unknown)
            {
            
            }
        }

        void SystemInfo::discoverDirectXLevel()
        {   
            if(m_DirectXLevel == DirectXLevels::Unknown)
            {
            
            }
        }

        void SystemInfo::discoverInstalledRAM()
        {
#ifdef OCULAR_WINDOWS
            MEMORYSTATUSEX memoryStatus = { sizeof MEMORYSTATUSEX };

            if(::GlobalMemoryStatusEx(&memoryStatus))
            {
                m_TotalRAM = memoryStatus.ullTotalPhys;
            }
            else
            {
                DWORD error = GetLastError();
                OcularLogger->error(
                    "Failed to retrieve available system RAM with error (", error, "): ",
                    Utils::StringUtils::windowsErrorToString(error),
                    OCULAR_INTERNAL_LOG("SystemInfo", "discoverAvailableRAM"));
            }
#endif
        }

        void SystemInfo::discoverAvailableRAM()
        {
#ifdef OCULAR_WINDOWS
            MEMORYSTATUSEX memoryStatus = { sizeof MEMORYSTATUSEX };

            if(::GlobalMemoryStatusEx(&memoryStatus))
            {
                m_FreeRAM = memoryStatus.ullAvailPhys;
            }
            else
            {
                DWORD error = GetLastError();
                OcularLogger->error(
                    "Failed to retrieve available system RAM with error (", error, "): ",
                    Utils::StringUtils::windowsErrorToString(error),
                    OCULAR_INTERNAL_LOG("SystemInfo", "discoverAvailableRAM"));
            }
#endif
        }

        void SystemInfo::discoverInstalledGPUMemory()
        {
            
        }

        void SystemInfo::discoverAvailableGPUMemory()
        {
        
        }

        void SystemInfo::discoverChannels()
        {
        
        }

        //------------------------------------------------------------------------------------------
        // PRIVATE METHODS
        //------------------------------------------------------------------------------------------
    }
}