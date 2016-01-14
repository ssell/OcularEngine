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

#pragma once
#ifndef __H__OCULAR_DEFINITIONS__H__
#define __H__OCULAR_DEFINITIONS__H__

//------------------------------------------------------------------------------------------
// Macros

//----------------------------------------------------
// Ocular Versions

#define OCULAR_V0_1 "Ocular Engine v0.1"
#define OCULAR_V0_2 "Ocular Engine v0.2"
#define OCULAR_V0_3 "Ocular Engine v0.3"
#define OCULAR_V0_4 "Ocular Engine v0.4"
#define OCULAR_VERSION OCULAR_V0_4

//----------------------------------------------------
// Operating Systems

#if defined(_WIN16) || defined (_WIN32) || defined(_WIN64) || defined(__WIN32__) ||  defined(__TOS_WIN__) || defined(__WINDOWS__)
#define OCULAR_WINDOWS 1
#elif defined(__APPLE__) || defined(__MACH__)
#define OCULAR_OSX 1
#elif defined(__linux__)
#define OCULAR_LINUX 1
#endif

#ifdef OCULAR_WINDOWS
#define OCULAR_PATH_SEPARATOR '\\'
#else
#define OCULAR_PATH_SEPARATOR '/'
#endif

//------------------------------------------------------------------------------------------
// Other
//------------------------------------------------------------------------------------------

// Amount of time, in MS, to allow for system message digestion and dispatching
#define OCULAR_SYS_MESSAGE_PROCESS_TIMEOUT 2

// Memory display
#define BYTES_PER_TiB 1099511627776ull
#define BYTES_PER_GiB 1073741824ull
#define BYTES_PER_MiB 1048576ull
#define BYTES_PER_KiB 1024ull


//------------------------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------------------------

namespace Ocular
{
    enum class OperatingSystems : unsigned
    {
        Unknown = 0,
        Windows,
        MacOS,
        Linux
    };

    enum class ProcessorArchitectures : unsigned
    {
        Unknown = 0,
        x86,
        x64,
        IA64,
        ARM
    };

    enum class Endianness : unsigned
    {
        Unknown = 0,
        Big,
        Little,
        Native        ///< Native endianness of the system. See SystemInfo::getEndianness()
    };

    enum class OpenGLLevels : unsigned
    {
        Unknown = 0,
        None
    };

    enum class DirectXLevels : unsigned
    {
        Unknown = 0,
        None
    };
}

//------------------------------------------------------------------------------------------

#endif