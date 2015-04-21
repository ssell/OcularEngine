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
#ifndef __H__OCULAR_EVENTS_EVENT_SNOOPER__H__
#define __H__OCULAR_EVENTS_EVENT_SNOOPER__H__

#include "Events/EventManager.hpp"

#include <string>
#include <memory>

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
         * \class EventSnooper
         *
         * Logs all events that are generated. <br/>
         * Has the following customization options: <br/><br/>
         *
         * <ul>
         *     <li>Ignore specified priority levels</li>
         *     <li>Ignore duplicate event types</li>
         * </ul><br/>
         *
         * By default, no events are ignored.
         */
        class EventSnooper : public AEventListener
        {
        public:
            
            EventSnooper();
            ~EventSnooper();

            /**
             * \param ignore If set to TRUE, the snooper will ignore any duplicate events that come in simultaneously.
             */
            void setIgnoreDuplicates(bool ignore);

            /**
             * \param priority Priority level to ignore
             * \param ignore   If set to TRUE, the snooper will ignore the specified priority level. <br/>
             *                 If FALSE, it will stop ignoring the priority level.
             */
            void setIgnorePriorityLevel(EventPriority priority, bool ignore);

        protected:

            virtual bool onEvent(std::shared_ptr<AEvent> event);

        private:

            bool m_IgnoreDuplicates;
            std::string m_LastEventType;

            bool m_IgnorePriorityMonitor;
            bool m_IgnorePriorityCritical;
            bool m_IgnorePriorityHigh;
            bool m_IgnorePriorityMedium;
            bool m_IgnorePriorityLow;
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