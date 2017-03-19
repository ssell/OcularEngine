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
#ifndef __H__OCULAR_EXCEPTION__H__
#define __H__OCULAR_EXCEPTION__H__

#include <stdexcept>

#define THROW_EXCEPTION(msg) throw Ocular::Core::Exception(msg, __FILE__, __LINE__)

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
	     * \class Exception
	     */
	    class Exception : public std::runtime_error
	    {
	    public:

		    Exception(std::string const& msg, std::string const file, int const line)
			    : runtime_error(msg), m_File(file), m_Line(line)
		    {
                m_Message = what();
            }

		    inline std::string getMessage()
		    {
			    return m_Message;
		    }

		    inline std::string getFile() const
		    {
			    return m_File;
		    }

		    inline int getLine() const
		    {
			    return m_Line;
		    }

	    protected:

	    private:

		    std::string m_File;
            std::string m_Message;

		    int m_Line;
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