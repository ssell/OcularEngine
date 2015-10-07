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

#pragma once
#ifndef __H__OCULAR_EVENTS_EVENT_MANAGER__H__
#define __H__OCULAR_EVENTS_EVENT_MANAGER__H__

#include <memory>
#include "AEventListener.hpp"
#include "Utilities/Structures/PriorityMultiQueue.hpp"
#include "Utilities/Structures/PriorityList.hpp"

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
         * \class EventManager
         */
        class EventManager
        {
        public:

            EventManager();
            ~EventManager();

            void processEvents(uint64_t duration);
           
            void registerListener(AEventListener* listener, uint32_t const priority);
            void unregisterListener(AEventListener* listener);

            void queueEvent(std::shared_ptr<AEvent> event);
            void fireEvent(std::shared_ptr<AEvent> event);

        protected:

        private:

            int findListener(AEventListener* pListener);
            void triggerEvent(std::shared_ptr<AEvent> event);

            Ocular::Utils::PriorityList<AEventListener*, 256> m_Listeners;
            Ocular::Utils::PriorityMultiQueue<std::shared_ptr<AEvent>, 256> m_Events;

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