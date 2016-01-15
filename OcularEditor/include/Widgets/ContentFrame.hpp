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
#ifndef __H__OCULAR_EDITOR_CONTENT_FRAME__H__
#define __H__OCULAR_EDITOR_CONTENT_FRAME__H__

#include <QtWidgets/qframe.h>

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
        class RenderFrame;
        class SceneFrame;
        class DetailsFrame;

        /**
         * \class ContentFrame
         * \brief 
         */
        class ContentFrame : public QFrame
        {
        public:

            ContentFrame(QWidget* parent = nullptr);
            ~ContentFrame();

            virtual QSize sizeHint() const override;

        protected:

        private:
            
            QHBoxLayout* m_LayoutContent;
            QSplitter*   m_pSplitter;

            RenderFrame*   m_RenderFrame;
            SceneFrame*    m_SceneFrame;
            DetailsFrame*  m_DetailsFrame;
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
