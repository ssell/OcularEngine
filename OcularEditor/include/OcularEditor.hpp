/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#ifndef __H__OCULAR_EDITOR__H__
#define __H__OCULAR_EDITOR__H__

#include "Widgets/MainWindow.hpp"
#include "Scene/ComponentFactory.hpp"

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Properties/PropertiesDisplayBox.hpp"
#include "Widgets/Properties/Renderables/RenderableDisplay.hpp"

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
         *
         */
        class Editor
        {
        public:

            static Editor& get();
            ~Editor();

            //------------------------------------------------------------
            // Application Lifetime Methods
            //------------------------------------------------------------

            bool initialize(int argc, char** argv);
            void shutdown();
            bool run();

            //------------------------------------------------------------
            // Primary Getters
            //------------------------------------------------------------
            
            /**
             * \return Pointer to the main Qt window for the editor application.
             */
            MainWindow* getMainWindow();

            /**
             * \return Pointer to the editor-specific camera used to view scenes.
             */
            Core::Camera* getEditorCamera();

            //------------------------------------------------------------
            // Misc Methods
            //------------------------------------------------------------
            
            /**
             * Sets the status text displayed in the main window status bar.
             *
             * \note If more control is required over the output status message/format/widget,
             *       the status bar may be retrieved via OcularEditor->getMainWindow()->getMainStatusBar()
             *
             * \param[in] message Text message to be displayed
             */
            void setStatusNormal(std::string const& message);

            /**
             * Sets a permanent status message that is not obstructed by any other messages.
             * It is typically placed on the far-right side of the status bar.
             *
             * \note If more control is required over the output status message/format/widget,
             *       the status bar may be retrieved via OcularEditor->getMainWindow()->getMainStatusBar()
             *
             * \param[in] message Text message to be displayed
             */
            void setStatusPermanent(std::string const& message);

            /**
             * Sets a temporary status message to be displayed for the specified amount of milliseconds.
             *
             * Typically used for tool-tip explanations, mouse-overs, etc.
             *
             * \note If more control is required over the output status message/format/widget,
             *       the status bar may be retrieved via OcularEditor->getMainWindow()->getMainStatusBar()
             *
             * \param[in] message  Text message to be displayed
             * \param[in] lifetime Duration of the message on range in milliseconds
             */
            void setStatusTemporary(std::string const& message, uint32_t lifetime);

            /**
             * Sets the status text displayed in the main window status bar, accompanied
             * by a progress bar widget.
             *
             * \param[in] message  Text message to be displayed
             * \param[in] progress Progress bar progress on range [0, 100]
             */
            void setStatusNormalProgress(std::string const& message, uint32_t progress);

            //------------------------------------------------------------
            // Widget Factories
            //------------------------------------------------------------

            /**
             * Attempts to create a property widget for the specified type.
             *
             * \param[in] displayName Name of the property widget (display on left-hand side of widget)
             * \param[in] type        Type name of the property to be represented. See Utils::TypeName (ie Utils::TypeName<Vector3f>::name)
             *
             * \return Pointer to new widget, if matching constructor was found for specified type.
             *         Otherwise, returns NULL. The caller must assume ownership of the object.
             */
            PropertyWidget* createPropertyWidget(std::string const& displayName, std::string const& type);

            /**
             * \return Reference to the property widget factory used by the Editor
             */
            Core::ComponentFactory<PropertyWidget>& getPropertyWidgetFactory();
            
            /**
             * Attempts to create a custom display for the specified type.
             *
             * \param[in] type Type name of the property to be represented. See Utils::TypeName (ie Utils::TypeName<Vector3f>::name)
             *
             * \return Pointer to new display, if matching constructor was found for specified type.
             *         Otherwise, returns NULL. The caller must assume ownership of the object.
             */
            PropertiesDisplayBox* createCustomDisplay(std::string const& type);

            /**
             * \return Reference to the custom display factory used by the Editor
             */
            Core::ComponentFactory<PropertiesDisplayBox>& getCustomDisplayFactory();

            /**
             *
             */
            RenderableDisplay* createRenderableDisplay(std::string const& type);

            /**
             *
             */
            Core::ComponentFactory<RenderableDisplay>& getRenderableDisplayFactory();

            //------------------------------------------------------------
            // Static Methods
            //------------------------------------------------------------

            /**
             * Checks if the provided name is an object name belongs to either Object or SceneObject base members.
             */
            static bool IsCommonName(std::string const& name);

            /**
             *
             */
            static std::string FormatName(std::string const& name);

        protected:

        private:

            Editor();
            Editor(Editor const&) = delete;
            void operator=(Editor const&) = delete;

            bool setupEditorCamera();

            //------------------------------------------------------------------------------

            QApplication* m_QtApp;

            MainWindow* m_MainWindow;
            Core::Camera* m_EditorCamera;

            Core::ComponentFactory<PropertyWidget> m_PropertyWidgetFactory;
            Core::ComponentFactory<PropertiesDisplayBox> m_CustomDisplayFactory;
            Core::ComponentFactory<RenderableDisplay> m_RenderableDisplayFactory;
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

#define OcularEditor Ocular::Editor::Editor::get()

//------------------------------------------------------------------------------------------

#endif