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
#ifndef __H__OCULAR_EDITOR_MATERIAL_UNIFORMS_DISPLAY_BOX__H__
#define __H__OCULAR_EDITOR_MATERIAL_UNIFORMS_DISPLAY_BOX__H__

#include "MaterialPropertiesDisplayBox.hpp"

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

        /**
         * \class UniformsDisplayBox
         */
        class UniformsDisplayBox : public MaterialPropertiesDisplayBox
        {
            Q_OBJECT

        public:

            UniformsDisplayBox(QWidget* parent = nullptr);
            ~UniformsDisplayBox();

            //------------------------------------------------------------

            virtual void setMaterial(Graphics::Material* material) override;
            virtual void updateProperties() override;
            virtual void onApply() override;

        protected:

            void buildWidgets();
            void buildNewUniformWidget();

            void setUniform(std::string const& name, uint32_t& currRegister, std::string const& value, std::string const& type);

        private slots:

            void onUniformAdded();

        private:

            QVBoxLayout* m_UniformLayout;           ///< Holds all pre-existing properties
            QHBoxLayout* m_NewUniformLayout;        ///< Holds the fields for creating a new uniform property
            QHBoxLayout* m_NewUniformLeftLayout;
            QHBoxLayout* m_NewUniformRightLayout;

            QFrame* m_NewUniformLeftFrame;
            QFrame* m_NewUniformRightFrame;

            QLineEdit*   m_NewUniformNameEdit;
            QComboBox*   m_NewUniformTypeCombo;
            QPushButton* m_NewUniformAddButton;

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