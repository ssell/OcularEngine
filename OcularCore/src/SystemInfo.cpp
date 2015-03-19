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

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        OperatingSystems       SystemInfo::m_OperatingSystem       = OperatingSystems::UNKNOWN;
        ProcessorArchitectures SystemInfo::m_ProcessorArchitecture = ProcessorArchitectures::UNKNOWN;
        Endianness             SystemInfo::m_Endianness            = Endianness::UNKNOWN;
        OpenGLLevels           SystemInfo::m_OpenGLLevel           = OpenGLLevels::UNKNOWN;
        DirectXLevels          SystemInfo::m_DirectXLevel          = DirectXLevels::UNKNOWN;
        long long              SystemInfo::m_TotalRAM              = -1;
        long long              SystemInfo::m_FreeRAM               = -1;
        long long              SystemInfo::m_TotalGPUMemory        = -1;
        long long              SystemInfo::m_FreeGPUMemory         = -1;
        int                    SystemInfo::m_NumberOfChannels      = -1;
        Core::Directory        SystemInfo::m_WorkingDirectory      = Core::Directory();

        //------------------------------------------------------------------------------------------
        // CONSTRUCTORS
        //------------------------------------------------------------------------------------------

        SystemInfo::SystemInfo()
        {
            discoverOperatingSystem();
            discoverProcessorArchitecture();
            discoverEndianness();
            discoverOpenGLLevel();
            discoverDirectXLevel();
        }

        SystemInfo::~SystemInfo()
        {
        
        }

        //------------------------------------------------------------------------------------------
        // PUBLIC METHODS
        //------------------------------------------------------------------------------------------

        void SystemInfo::refresh()
        {
            discoverRAM();
            discoverGPUMemory();
            discoverChannels();
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

        long long SystemInfo::getTotalRAM()
        {
            return m_TotalRAM;
        }

        long long SystemInfo::getFreeRAM()
        {
            return m_FreeRAM;
        }

        long long SystemInfo::getTotalGPUMemory()
        {
            return m_TotalGPUMemory;
        }

        long long SystemInfo::getFreeGPUMemory()
        {
            return m_FreeGPUMemory;
        }

        int SystemInfo::getNumberOfChannels()
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
#elif defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(_M_IA64) || defined(__itanium__)
                m_ProcessorArchitecture = ProcessorArchitecture::IA64;
#
#endif
            }
        }

        void SystemInfo::discoverEndianness()
        {
            if(m_Endianness == Endianness::Unknown)
            {
            
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

        void SystemInfo::discoverRAM()
        {
            
        }

        void SystemInfo::discoverGPUMemory()
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