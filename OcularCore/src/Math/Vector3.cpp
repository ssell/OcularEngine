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

#include "Math/Vector3.hpp"
#include "Utilities/StringRegistrar.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        OCULAR_REGISTER_TO_STRING(Vector3f, OCULAR_TO_STRING_LAMBDA 
        { 
            std::string result;

            if(raw)
            {
                if(!isPointer)
                {
                    Vector3f vector = void_cast<Vector3f>(raw);

                    std::stringstream sstream;
                    sstream << vector.x << " " << vector.y << " " << vector.z;

                    result = sstream.str();
                }
                else
                {
                    Vector3f* vector = void_cast<Vector3f*>(raw);

                    if(vector)
                    {
                        std::stringstream sstream;
                        sstream << vector->x << " " << vector->y << " " << vector->z;

                        result = sstream.str();
                    }
                }
            }

            return result; 
        });

        OCULAR_REGISTER_FROM_STRING(Vector3f, OCULAR_FROM_STRING_LAMBDA
        {
            if(out)
            {
                Vector3f* result = void_cast<Vector3f*>(out);

                if(result)
                {
                    size_t cumulativePos = 0;
                    size_t nextPos = 0;

                    try
                    {
                        result->x = std::stof(str.substr(cumulativePos), &nextPos);
                        cumulativePos += nextPos;
                        
                        result->y = std::stof(str.substr(cumulativePos), &nextPos);
                        cumulativePos += nextPos;
                        
                        result->z = std::stof(str.substr(cumulativePos), &nextPos);
                    }
                    catch(std::invalid_argument const& e)
                    {
                        OcularLogger->error("Failed to convert string '", str, "' to Vector3f with error: ", e.what(), OCULAR_INTERNAL_LOG("Vector3f", "FromString"));
                    }
                }
            }
        });

        bool Vector3f::OCULAR_INTERNAL_Force = false;

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