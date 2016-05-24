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
#ifndef __H__OCULAR_UTILITIES_VOID_CAST__H__
#define __H__OCULAR_UTILITIES_VOID_CAST__H__

#include <type_traits>

//------------------------------------------------------------------------------------------

/**
 * No namespace as I like to live dangerously.
 *
 * Implementation of a simple `void_cast` set of functions. As the name suggests,
 * these allow for the casting back and forth between void*. Example of it's use:
 *
 * \code{.cpp}
 *     void* vp = nullptr;
 *
 *     uint32_t uiA = 5;
 *     uint32_t uiB = 0;
 *
 *     vp = void_cast<uint32_t>(uiA);
 *     uiB = void_cast<uint32_t>(vp);     // uiB now equals 5
 *
 *     //---------------------------------------------
 *
 *     float fA = 13.37;
 *     float fB = 0.0f;
 *
 *     vp = void_cast<float>(fA);
 *     fB = void_cast<float>(vp);         // fB now equals 13.37f
 *
 *     //---------------------------------------------
 *
 *     Foo* fooA = new Foo();
 *     Foo* fooB = nullptr;
 *
 *     fooA->value = 19;
 *
 *     vp = void_cast<Foo*>(fooA);
 *     fooB = void_cast<Foo*>(vp);        // fooB->value now equals 19
 *
 *     //---------------------------------------------
 *
 *     Foo fooC;
 *     Foo fooD;
 *
 *     fooC.value = 36;
 *
 *     vp = void_cast<Foo>(fooC);
 *     fooD = void_cast<Foo>(vp);        // fooD->value now equals 36
 * \endcode
 */

template<typename T>
union OCULAR_INTERNAL_VoidCast
{
    T var;
    void* ptr;
};

template<typename T>
static typename std::enable_if<std::is_trivial<T>::value, T>::type void_cast(void* val)
{
    if(sizeof(T) <= sizeof(void*))
    {
        union OCULAR_INTERNAL_VoidCast<T> vcintern;
        vcintern.ptr = val;

        return vcintern.var;
    }
    else
    {
        // Hit on double, int64_t, etc. on 32-bit builds 
        return *(T*)(val);
    }
}

template<typename T>
static typename std::enable_if<std::is_trivial<T>::value, void*>::type void_cast(T const& t)
{
    if(sizeof(T) <= sizeof(void*))
    {
        union OCULAR_INTERNAL_VoidCast<T> vcintern;
        vcintern.var = t;

        return vcintern.ptr;
    }
    else
    {
        // Hit on double, int64_t, etc. on 32-bit builds
        return (void*)(&t);
    }
}

template<typename T>
static typename std::enable_if<!std::is_trivial<T>::value, T>::type void_cast(void* val) 
{
    // Potentially undefined behavior (if sizeof(T) != data size at address pointed to in void*)
    // But unions only allow trivial members, so no other option
    return *(T*)(val);
}

template<typename T>
static typename std::enable_if<!std::is_trivial<T>::value, void*>::type void_cast(T const& t) 
{
    // Potentially undefined behavior (if sizeof(T) != data size at address pointed to in void*)
    // But unions only allow trivial members, so no other option
    return (void*)(&t);
}

//------------------------------------------------------------------------------------------

#endif