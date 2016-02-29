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

#include "Math/Vector4.hpp"
#include "Utilities/StringRegistrar.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        OCULAR_REGISTER_TO_STRING(Vector4f, OCULAR_TO_STRING_LAMBDA 
        { 
            std::string result;

            if(raw)
            {
                Vector4f vector = void_cast<Vector4f>(raw);
                std::stringstream sstream;
        
                for(uint32_t i = 0; i < 4; i++)
                {
                    sstream << vector[i] << " ";
                }

                result = sstream.str();
            }

            return result; 
        });

        OCULAR_REGISTER_FROM_STRING(Vector4f, OCULAR_FROM_STRING_LAMBDA
        {
            static Vector4f result;

            uint32_t index = 0;
            size_t cumulativePos = 0;
            size_t nextPos = 0;

            try
            {
                float value = 0.0f;

                while((cumulativePos < str.size()) && (index < 4))
                {
                    result[index] = std::stof(str.substr(cumulativePos), &nextPos);
                    cumulativePos += nextPos;
                    index += 1;
                }
            }
            catch(std::invalid_argument const& e)
            {
                OcularLogger->error("Failed to convert string '", str, "' to Vector4f with error: ", e.what(), OCULAR_INTERNAL_LOG("Vector4f", "FromString"));
            }

            return void_cast<Vector4f>(result);
        });

        bool Vector4f::OCULAR_INTERNAL_Force = false;

        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}