/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_EDITOR_PROPERTIES_PANEL__H__
#define __H__OCULAR_EDITOR_PROPERTIES_PANEL__H__

#include <QtWidgets/qframe.h>
#include "Events/AEventListener.hpp"

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
        class CommonDisplay;
        class CustomObjectDisplay;
        class RenderableDisplay;
        class RoutineDisplay;

        /**
         * \class PropertiesPanel
         */
        class PropertiesPanel : public QFrame, public Ocular::Core::AEventListener
        {
        public:

            PropertiesPanel(QWidget* parent = nullptr);
            ~PropertiesPanel();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            void update();
            void selectObject(Core::SceneObject* object);

        protected:

            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;

            void objectDeselected();

            void initializeCommon();
            void initializeCustom();
            void initializeRenderable();
            void initializeRoutines();

        private:

            QVBoxLayout* m_Layout;

            Core::SceneObject* m_CurrentObject;
            Core::UUID         m_CurrentObjectUUID;

            CommonDisplay*        m_CommonProperties;
            PropertiesDisplayBox* m_CustomProperties;
            RenderableDisplay*    m_RenderableProperties;

            std::vector<RoutineDisplay*> m_RoutineProperties;
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