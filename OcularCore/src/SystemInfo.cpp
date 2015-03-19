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

        }

        SystemInfo::~SystemInfo()
        {
        
        }

        //------------------------------------------------------------------------------------------
        // PUBLIC METHODS
        //------------------------------------------------------------------------------------------

        bool SystemInfo::refresh()
        {
            bool result = false;


            return result;
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

        //------------------------------------------------------------------------------------------
        // PRIVATE METHODS
        //------------------------------------------------------------------------------------------
    }
}