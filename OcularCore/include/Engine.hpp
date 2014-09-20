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

#ifndef __H__OCULAR_ENGINE__H__
#define __H__OCULAR_ENGINE__H__

#include "Common.hpp"
#include "Logger\Logger.hpp"
#include "Time\Clock.hpp"
#include "Renderer\Window\WindowManager.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
        * \class Engine
        */
    class Engine
    {
    public:

        Engine();
        ~Engine();

        bool initialize();
        bool shutdown();

        //----------------------------------------

        const Core::Logger Logger;
        const Core::Clock Clock;
        const Core::WindowManager WindowManager;
        
    protected:

    private:

        void setupLogger();
    
    };
}
/**
 * @} End of Doxygen Groups
 */

#endif