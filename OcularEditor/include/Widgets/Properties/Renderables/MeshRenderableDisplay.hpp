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
#ifndef __H__OCULAR_EDITOR_MESH_RENDERABLE_DISPLAY__H__
#define __H__OCULAR_EDITOR_MESH_RENDERABLE_DISPLAY__H__

#include "RenderableDisplay.hpp"

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
        class MeshRenderableDisplayMaterial;
        class ButtonResourceBrowse;
        class ResourceProperty;

        /**
         * \class MeshRenderableDisplay
         */
        class MeshRenderableDisplay : public RenderableDisplay
        {
            Q_OBJECT

        public:

            MeshRenderableDisplay(QWidget* parent = nullptr);
            virtual ~MeshRenderableDisplay();

            //------------------------------------------------------------

            virtual void updateProperties() override;

        protected:

            virtual void buildProperties() override;
            virtual void removeProperties() override;
            
        private slots:
        
            void onButtonAddMaterialClick();
            void onButtonRemoveMaterialClick();

        private:

            void buildMeshProperty();
            void buildMaterialProperties();
            void buildMaterialAddRemove();

            //------------------------------------------------------------

            ResourceProperty* m_MeshProperty;
            std::vector<MeshRenderableDisplayMaterial*> m_MaterialProperties;

            QFrame* m_FrameAddRemove;
            QHBoxLayout* m_LayoutAddRemove;

            QPushButton* m_ButtonAddMaterial;
            QPushButton* m_ButtonRemoveMaterial;
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