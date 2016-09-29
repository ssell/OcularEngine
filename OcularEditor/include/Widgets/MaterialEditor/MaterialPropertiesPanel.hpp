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
#ifndef __H__OCULAR_EDITOR_MATERIAL_PROPERTIES_PANEL__H__
#define __H__OCULAR_EDITOR_MATERIAL_PROPERTIES_PANEL__H__

#include <QtWidgets/qframe.h>

#include "Graphics/Material/Material.hpp"
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
        class PropertyWidget;
        class MaterialPropertiesDisplayBox;

        /**
         * \class MaterialPropertiesPanel
         */
        class MaterialPropertiesPanel : public QFrame, public Ocular::Core::AEventListener
        { 
            Q_OBJECT

        public:

            MaterialPropertiesPanel(QWidget* parent = nullptr);
            ~MaterialPropertiesPanel();

            virtual QSize sizeHint() const override;

            void setMaterial(std::string const& mapping);
            void onApply();

        protected:

            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;

            void buildBaseWidgets();
            void updateProperties();

        private slots:

        private:

            Graphics::Material* m_Material;
            std::string m_MaterialMapping;

            QVBoxLayout* m_LayoutMain;

            PropertyWidget* m_PropertyMapping;
            PropertyWidget* m_PropertyFile;

            MaterialPropertiesDisplayBox* m_PropertyBoxShaders;
            MaterialPropertiesDisplayBox* m_PropertyBoxUniforms;
            MaterialPropertiesDisplayBox* m_PropertyBoxTextures;
            MaterialPropertiesDisplayBox* m_PropertyBoxRenderStates;
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