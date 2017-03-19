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
#ifndef __H__OCULAR_EDITOR_ROUTINE_DISPLAY__H__
#define __H__OCULAR_EDITOR_ROUTINE_DISPLAY__H__

#include "PropertiesDisplayBox.hpp"

//------------------------------------------------------------------------------------------

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
         * \class RoutineDisplay
         */
        class RoutineDisplay : public PropertiesDisplayBox
        {
        public:

            RoutineDisplay(std::string const& routineName, QWidget* parent = nullptr);
            ~RoutineDisplay();

            //------------------------------------------------------------

            virtual void setObject(Core::SceneObject* object) override;
            virtual void updateProperties() override;

        protected:

            void buildProperties();
            void removeProperties();

            //------------------------------------------------------------

            Core::ARoutine* m_Routine;
            std::string m_RoutineName;

        private:

            std::vector<PropertyWidget*> m_Properties;

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