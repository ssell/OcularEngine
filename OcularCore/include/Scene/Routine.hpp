/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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

#ifndef __H__OCULAR_CORE_SCENE_ROUTINE__H__
#define __H__OCULAR_CORE_SCENE_ROUTINE__H__

#include "Events/AEventListener.hpp"

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
         * \class Routine
         */
        class Routine : public AEventListener
        {
        public:

            virtual void onSceneStart();
            virtual void onSceneEnd();

            virtual void onCreation();
            virtual void onDestruction();

            virtual void onPause();
            virtual void onUnpause();

            virtual void onUpdate();
            virtual float onUpdateTimed();

            virtual void onPreRender();
            virtual void onRender();
            virtual void onPostRender();

            virtual bool onEvent(std::shared_ptr<AEvent> event);

        protected:

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