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

#ifndef __H__OCULAR_EDITOR_INPUT_TRANSLATOR__H__
#define __H__OCULAR_EDITOR_INPUT_TRANSLATOR__H__

#include "Input/Keys.hpp"

//------------------------------------------------------------------------------------------

class QEvent;

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        /**
         * \class InputTranslator
         * \brief Translates QT input events into Ocular input events
         */
        class InputTranslator
        {
        public:
    
            static bool TranslateKeyPress(QEvent* event);
            static bool TranslateKeyRelease(QEvent* event);
            static bool TranslateMousePress(QEvent* event);
            static bool TranslateMouseRelease(QEvent* event);
            static bool TranslateMouseMove(QEvent* event);

        protected:

            static Core::KeyboardKeys ConvertKey(int32_t key);
            static Core::MouseButtons ConvertButton(int32_t button);

        private:
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