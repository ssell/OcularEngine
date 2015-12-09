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
#ifndef __H__OCULAR_CORE_ROUTINE_FREE_FLY_CONTROLLER__H__
#define __H__OCULAR_CORE_ROUTINE_FREE_FLY_CONTROLLER__H__

#include "Scene/ARoutine.hpp"
#include "Math/Vector3.hpp"

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
         * \class FreeFlyController
         */
        class FreeFlyController : public ARoutine
        {
        public:

            FreeFlyController();
            virtual ~FreeFlyController();

            virtual void onCreation() override;
            virtual void onUpdate(float const delta) override;
            virtual bool onEvent(std::shared_ptr<AEvent> event) override;

        protected:

        private:

            Math::Vector3f m_MovementModifier;

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