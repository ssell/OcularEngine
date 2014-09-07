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
#ifndef __H__OCULAR_EXCEPTION__H__
#define __H__OCULAR_EXCEPTION__H__

#include <stdexcept>

#define THROW_EXCEPTION(msg) throw Ocular::Exception(msg, __FILE__, __LINE__)

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular 
{
	/**
	 * \class Exception
	 */
	class Exception : public std::runtime_error
	{
	public:

		Exception(const std::string &msg, const std::string file, const int line)
			: runtime_error(msg), m_File(file), m_Line(line)
		{}

		inline std::string getMessage()
		{
			return what();
		}

		inline std::string getFile()
		{
			return m_File;
		}

		inline int getLine()
		{
			return m_Line;
		}

	protected:

	private:

		std::string m_File;
		int m_Line;
	};
}
/**
 * @} End of Doxygen Groups
 */

//------------------------------------------------------------------------------------------

#endif