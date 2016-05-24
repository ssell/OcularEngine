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

#pragma once
#ifndef __H__OCULAR_CORE_ROUTINE_FREE_FLY_CONTROLLER__H__
#define __H__OCULAR_CORE_ROUTINE_FREE_FLY_CONTROLLER__H__

#include "Scene/ARoutine.hpp"
#include "Math/Vector3.hpp"
#include "Math/Quaternion.hpp"

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
         *
         * Controller that allows for basic free-fly movement for any SceneObject it is attached to.
         * The following controls are employed:
         *
         * |     Key     |        Action        |
         * | ----------- | -------------------- |
         * | W           | Move forward         |
         * | A           | Move backward        |
         * | S           | Move left            |
         * | D           | Move right           |
         * | Q           | Move up              |
         * | Z           | Move down            |
         * | Up Arrow    | Move forward         |
         * | Down Arrow  | Move backward        |
         * | Left Arrow  | Move left            |
         * | Right Arrow | Move right           |
         * | Left Shift  | Apply movement burst |
         * | Spacebar    | Reset orientation    |
         * | Mouse       | Rotation             |
         *
         */
        class FreeFlyController : public ARoutine
        {
        public:

            FreeFlyController();
            virtual ~FreeFlyController();

            //------------------------------------------------------------
            // Inherited Methods
            //------------------------------------------------------------

            virtual void onUpdate(float const delta) override;
            virtual bool onEvent(std::shared_ptr<AEvent> event) override;

            //------------------------------------------------------------
            // Controller Specific Methods
            //------------------------------------------------------------

            /**
             * Sets the mouse look sensitivity modifier
             * \param[in] sensitivity Mouse sensitivity (default 1.0)
             */
            void setLookSensitivity(float sensitivity);

            /**
             * \return The mouse look sensitivity modifier.
             */
            float getLookSensitivity() const;

            /**
             * Sets the default movement speed in units per-second
             * \param[in] speed Movement speed in units per-second (default 1.0)
             */
            void setMovementSpeed(float speed);

            /**
             * \return The movement speed in units per-second
             */
            float getMovementSpeed() const;

            /**
             * Sets the burst speed modifier used when left-shift is being held down.
             * \param[in] modifier Burst speed modifier (default 5.0)
             */
            void setBurstSpeedModifier(float modifier);

            /**
             * \return The burst speed modifier
             */
            float getBurstSpeedModifier() const;

            /**
             * If TRUE, the controller will prevent any changes in the roll (z-axis rotation).
             * \param[in] prevent Whether to prevent rolling (default TRUE)
             */
            void setPreventRoll(bool prevent);
            
            /**
             * \return Whether roll changes are being prevented
             */
            bool getPreventRoll() const;

        protected:

            void handleMovement(float delta);
            void handleMouseRotation();

        private:
            
            Math::Vector3f m_Euler;             ///< Used to calculate mouse-based rotational changes when roll is prevented
            Math::Vector3f m_MovementVector;    ///< The current movement vector based off of user input (WASD and arrow keys)
            Math::Vector2i m_LastMousePos;      ///< Mouse position of last update

            float m_LookSensitivity;            ///< Mouse-look sensitivity modifier (default 1.0)
            float m_MovementSpeed;              ///< Controller movement speed (default 1.0)
            float m_BurstModifier;              ///< Controller burst speed modifier (default 5.0)

            bool m_PreventRoll;                 ///< If TRUE, the controller will not modify the roll when mouse looking
            bool m_IsInBurst;                   ///< If TRUE, the burst modifier is being applied to the movement speed
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