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
#ifndef __H__OCULAR_CORE_UTILS_STRING_REGISTRAR__H__
#define __H__OCULAR_CORE_UTILS_STRING_REGISTRAR__H__

#include "OcularEngine.hpp"

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
        template<typename T>
        class ToStringRegistrar
        {
        public:

            ToStringRegistrar(std::function<std::string(void*, bool)> func)
            {
                OcularString->registerToString<T>(func);
            }
        };

        template<typename T>
        class FromStringRegistrar
        {
        public:

            FromStringRegistrar(std::function<void(std::string const&, void*)> func)
            {
                OcularString->registerFromString<T>(func);
            }
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

/**
 * Helper macro to assist in registering ToString functions with the Ocular::Utils::String class.
 * Can be envoked anywhere, including globally (outside of a function).
 *
 * Example:
 *
 *     OCULAR_REGISTER_TO_STRING(float, OCULAR_TO_STRING_LAMBDA { return std::to_string(void_cast<float>(raw)); });
 *
 * This registers the above lambda function (which makes use of the void_cast helper to transform the raw void*
 * into a float) to be used whenever Ocular::Utils::String::ToString<float>() is called.
 */
#define OCULAR_REGISTER_TO_STRING(X,Y) const Ocular::Utils::ToStringRegistrar<X> OCULAR_INTERNAL_ToStringRegister(Y)

/**
 * Helper macro to assist in registering FromString functions with the Ocular::Utils::String class.
 * Can be envoked anywhere, including globally (outside of a function).
 *
 * Example:
 *
 *     OCULAR_REGISTER_FROM_STRING(float, OCULAR_FROM_STRING_LAMBDA { return void_cast<float>(std::stof(string, nullptr)); });
 *
 * This registers the above lambda function (which makes use of the void_cast helper to transform the raw float
 * into a raw void*) to be used whenever Ocular::Utils::String::FromString<float>() is called.
 */
#define OCULAR_REGISTER_FROM_STRING(X,Y) const Ocular::Utils::FromStringRegistrar<X> OCULAR_INTERNAL_FromStringRegister(Y)

/**
 * Helper macro to make registering ToString lambda functions easier.
 *
 *     OCULAR_REGISTER_TO_STRING(float, [](void* raw)->std::string { ... });
 *
 * to
 *
 *     OCULAR_REGISTER_TO_STRING(float, OCULAR_TO_STRING_LAMBDA { ... });
 */
#define OCULAR_TO_STRING_LAMBDA [](void* raw, bool isPointer)->std::string

/**
 * Helper macro to make registering FromString lambda functions easier.
 *
 *     OCULAR_REGISTER_FROM_STRING(float, [](std::string const& str)->void* { ... });
 *
 * to
 *
 *     OCULAR_REGISTER_FROM_STRING(float, OCULAR_FROM_STRING_LAMBDA { ... });
 */
#define OCULAR_FROM_STRING_LAMBDA [](std::string const& str, void* out)

//------------------------------------------------------------------------------------------

#endif