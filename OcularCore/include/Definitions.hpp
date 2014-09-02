/**
 * Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

// Ocular Versions

#define OCULAR_V0_0_1 "Ocular Engine v0.0.1"
#define OCULAR_VERSION OCULAR_V0_0_1

// Operating Systems

#if defined(_WIN16) || defined (_WIN32) || defined(_WIN64) || defined(__WIN32__) ||  defined(__TOS_WIN__) || defined(__WINDOWS__)
#define OCULAR_WINDOWS 1
#elif defined(__APPLE__) || defined(__MACH__)
#define OCULAR_OSX 1
#elif defined(__linux__)
#define OCULAR_LINUX 1
#endif

//------------------------------------------------------------------------------------------

#endif