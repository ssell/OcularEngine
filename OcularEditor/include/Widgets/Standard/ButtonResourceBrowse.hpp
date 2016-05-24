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
#ifndef __H__OCULAR_BUTTON_RESOURCE_BROWSE__H__
#define __H__OCULAR_BUTTON_RESOURCE_BROWSE__H__

#include <QtWidgets/qpushbutton.h>
#include "Resources/Resource.hpp"

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
         * \class ButtonResourceBrowse
         *
         * Helper class implementation of QPushButton for selecting resources.
         */
        class ButtonResourceBrowse : public QPushButton
        {
            Q_OBJECT

        public:

            ButtonResourceBrowse(QWidget* parent = nullptr);
            virtual ~ButtonResourceBrowse();

            virtual QSize sizeHint() const override;
            
            /**
             * \param[in] reset If TRUE, then the edited flag is reset back to FALSE.
             * \return TRUE if the user has modifed this edit. 
             */
            bool wasEdited(bool reset = true);

            /**
             *
             */
            void setResourceType(Core::ResourceType type);
            
            /**
             *
             */
            std::string const& getSelectedResource() const;

        protected:
            
        private slots :

            void onButtonClick();

        private:

            bool m_WasEdited;

            Core::ResourceType m_Type;
            std::string m_SelectedResource;
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