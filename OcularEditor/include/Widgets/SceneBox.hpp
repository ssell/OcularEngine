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
#ifndef __H__OCULAR_EDITOR_SCENE_BOX__H__
#define __H__OCULAR_EDITOR_SCENE_BOX__H__

#include <QtWidgets/qgroupbox.h>

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
        class SceneTree;

        /**
         * \class SceneBox
         * \brief 
         */
        class SceneBox : public QGroupBox
        {
        public:

            SceneBox(QWidget* parent = nullptr);
            ~SceneBox();

            virtual QSize sizeHint() const override;

            SceneTree* getSceneTree() const;

        protected:

        private:
            
            QVBoxLayout* m_Layout;
            SceneTree* m_SceneTree;
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
