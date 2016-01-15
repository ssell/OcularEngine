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
#ifndef __H__OCULAR_EDITOR_SCENE_FRAME__H__
#define __H__OCULAR_EDITOR_SCENE_FRAME__H__

#include <QtWidgets/qframe.h>
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
        class SceneBox;
        class ConsoleBox;

        /**
         * \class SceneFrame
         * \brief 
         */
        class SceneFrame : public QFrame
        {
        public:

            SceneFrame(QWidget* parent = nullptr);
            ~SceneFrame();

            virtual QSize sizeHint() const override;

        protected:

        private:

            QVBoxLayout* m_Layout;
            QSplitter* m_pSplitter;

            SceneBox* m_SceneBox;
            ConsoleBox* m_ConsoleBox;
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
