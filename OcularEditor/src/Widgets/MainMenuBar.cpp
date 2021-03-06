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

#include "stdafx.h"

#include "Widgets/MainMenuBar.hpp"
#include "Widgets/MainWindow.hpp"
#include "Widgets/ScenePropertiesDialog.hpp"
#include "Widgets/MaterialEditor/MaterialEditorDialog.hpp"

#include "SceneObjectImporter.hpp"
#include "Scene/Renderables/MeshRenderable.hpp"

#include "Events/SceneObjectSelectedEvent.hpp"

//------------------------------------------------------------------------------------------

namespace
{
    const char* NameCubeMesh   = "Cube";
    const char* NameSphereMesh = "Sphere";
    const char* NameTorusMesh  = "Torus";
    const char* NamePlaneMesh  = "Plane";

    const char* NameLightPoint       = "Point Light";
    const char* NameLightSpot        = "Spot Light";
    const char* NameLightDirectional = "Directional Light";

    // The strings below will eventually be moved into config files

    const std::string PathCoreMaterials = "OcularCore/Materials/";
    const std::string PathCoreMeshes    = "OcularCore/Meshes/";
}

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        MainMenuBar::MainMenuBar(MainWindow* parent)
            : QMenuBar(parent),
              m_MenuFile(nullptr),
              m_MenuScene(nullptr),
              m_MenuSceneMesh(nullptr),
              m_MenuSceneLight(nullptr),
              m_MenuTools(nullptr),
              m_MenuHelp(nullptr)
        {
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            createFileMenu();
            createSceneMenu();
            createToolsMenu();
            createHelpMenu();
        }

        MainMenuBar::~MainMenuBar()
        {
            for(auto iter = m_MenuActions.begin(); iter != m_MenuActions.end(); ++iter)
            {
                delete (*iter);
            }

            m_MenuActions.clear();

            delete m_MenuFile;
            delete m_MenuScene;
            delete m_MenuTools;
            delete m_MenuHelp;
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        QSize MainMenuBar::sizeHint() const
        {
            // Some arbitrarily large size so that the frame always exapnds to fill all available space
            return QSize(99999, 99999);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void MainMenuBar::createFileMenu()
        {
            m_MenuFile = addMenu(tr("&File"));

            m_MenuActions.push_back(new QAction(tr("New Project"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileNewProject()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuActions.push_back(new QAction(tr("Open Project"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileOpenProject()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuActions.push_back(new QAction(tr("Close Project"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileCloseProject()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuFile->addSeparator();

            m_MenuActions.push_back(new QAction(tr("New Scene"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileNewScene()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuActions.push_back(new QAction(tr("Open Scene"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileOpenScene()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuActions.push_back(new QAction(tr("Save Scene"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileSaveScene()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuActions.push_back(new QAction(tr("Save Scene As..."), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileSaveSceneAs()));
            m_MenuFile->addAction(m_MenuActions.back());

            m_MenuActions.push_back(new QAction(tr("Close Scene"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileCloseScene()));
            m_MenuFile->addAction(m_MenuActions.back());
            
            m_MenuFile->addSeparator();

            m_MenuActions.push_back(new QAction(tr("Exit"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onFileExit()));
            m_MenuFile->addAction(m_MenuActions.back());
        }

        void MainMenuBar::createSceneMenu()
        {
            m_MenuScene = addMenu(tr("&Scene"));
            
            m_MenuActions.push_back(new QAction(tr("Add SceneObject"), this));
            m_MenuScene->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddObject()));

            //------------------------------------------------------------
            // Mesh Submenu

            m_MenuSceneMesh = m_MenuScene->addMenu(tr("Add Mesh"));
            
            m_MenuActions.push_back(new QAction(tr(NameCubeMesh), this));
            m_MenuSceneMesh->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddMesh()));

            m_MenuActions.push_back(new QAction(tr(NameSphereMesh), this));
            m_MenuSceneMesh->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddMesh()));
            
            m_MenuActions.push_back(new QAction(tr(NameTorusMesh), this));
            m_MenuSceneMesh->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddMesh()));
            
            m_MenuActions.push_back(new QAction(tr(NamePlaneMesh), this));
            m_MenuSceneMesh->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddMesh()));

            //------------------------------------------------------------
            // Light Submenu

            m_MenuSceneLight = m_MenuScene->addMenu(tr("Add Light"));

            m_MenuActions.push_back(new QAction(tr(NameLightPoint), this));
            m_MenuSceneLight->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddLight()));

            m_MenuActions.push_back(new QAction(tr(NameLightSpot), this));
            m_MenuSceneLight->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddLight()));

            m_MenuActions.push_back(new QAction(tr(NameLightDirectional), this));
            m_MenuSceneLight->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddLight()));
            
            //------------------------------------------------------------
            // Handlers for Custom SceneObjects

            auto objectTypes = OcularScene->getSceneObjectFactory().getRegisteredKeys();
            
            for(auto objectType : objectTypes)
            { 
                if(!Utils::String::IsEqual(objectType, "SceneObject") && !Utils::String::Contains(objectType, " Light"))
                {
                    const std::string label = "Add " + objectType;

                    m_MenuActions.push_back(new QAction(tr(label.c_str()), this));
                    m_MenuScene->addAction(m_MenuActions.back());
                    connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneAddObject()));
                }
            }

            //------------------------------------------------------------
            // Import Object
            
            m_MenuScene->addSeparator();
            
            m_MenuActions.push_back(new QAction(tr("Import SceneObject"), this));
            m_MenuScene->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneImportObject()));

            //------------------------------------------------------------
            // Properties

            m_MenuScene->addSeparator();

            m_MenuActions.push_back(new QAction(tr("Scene Properties..."), this));
            m_MenuScene->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onSceneProperties()));

            m_DialogSceneProperties = new ScenePropertiesDialog(this);  // Make member variable so we can non-modal ::show
        }

        void MainMenuBar::createToolsMenu()
        {
            m_MenuTools = addMenu(tr("&Tools"));

            m_MenuActions.push_back(new QAction(tr("Material Editor"), this));
            m_MenuTools->addAction(m_MenuActions.back());
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onToolsMaterialEditor()));

            m_DialogMaterialEditor = new MaterialEditorDialog(this);
        }

        void MainMenuBar::createHelpMenu()
        {
            m_MenuHelp = addMenu(tr("&Help"));

            m_MenuActions.push_back(new QAction(tr("About Ocular Editor"), this));
            connect(m_MenuActions.back(), SIGNAL(triggered()), this, SLOT(onHelpAbout()));
            m_MenuHelp->addAction(m_MenuActions.back());
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        void MainMenuBar::onFileNewProject()
        {

        }

        void MainMenuBar::onFileOpenProject()
        {

        }

        void MainMenuBar::onFileCloseProject()
        {

        }

        void MainMenuBar::onFileNewScene()
        {
            m_LastScenePath.clear();

            OcularEvents->queueEvent(std::make_shared<SceneObjectSelectedEvent>(nullptr));
            OcularScene->createScene("New Scene");
        }

        void MainMenuBar::onFileOpenScene()
        {
            const std::string searchPath = (m_LastScenePath.size() ? m_LastScenePath : OcularResources->getSourceDirectory());
            const std::string path = QFileDialog::getOpenFileName(this, tr("Open Scene"), searchPath.c_str(), tr("Ocular Scene Files (*.oscene)")).toStdString();

            Core::File openFile(path);

            if(openFile.exists() && openFile.canRead() && Utils::String::IsEqual(openFile.getExtension(), ".oscene"))
            {
                OcularEvents->queueEvent(std::make_shared<SceneObjectSelectedEvent>(nullptr));

                if(OcularScene->loadScene(openFile))
                {
                    m_LastScenePath = path;
                }
            }
        }

        void MainMenuBar::onFileSaveScene()
        {
            OcularEditor.setSelectedObject(nullptr);

            if(m_LastScenePath.size())
            {
                OcularScene->saveScene(Core::File(m_LastScenePath));
            }
            else
            {
                onFileSaveSceneAs();
            }
        }

        void MainMenuBar::onFileSaveSceneAs()
        {
            OcularEditor.setSelectedObject(nullptr);

            const std::string searchPath = (m_LastScenePath.size() ? m_LastScenePath : OcularResources->getSourceDirectory());
            const std::string path = QFileDialog::getSaveFileName(this, tr("Save Scene"), searchPath.c_str(), tr("Ocular Scene Files (*.oscene)")).toStdString();

            if(path.size())
            {
                Core::File saveFile(path);

                if(OcularScene->saveScene(saveFile))
                {
                    m_LastScenePath = path;
                }
            }
        }

        void MainMenuBar::onFileCloseScene()
        {

        }

        void MainMenuBar::onFileExit()
        {

        }

        void MainMenuBar::onSceneAddObject()
        {
            QAction* action = dynamic_cast<QAction*>(sender());

            if(action)
            {
                const std::string text = action->text().toStdString().substr(4);  // Cut off the "Add "

                OcularScene->createObjectOfType(text, text);
            }
        }

        void MainMenuBar::onSceneAddMesh()
        {
            QAction* action = dynamic_cast<QAction*>(sender());

            if(action)
            {
                const std::string text = action->text().toStdString();

                Core::SceneObject* object = new Core::SceneObject(text);
                object->setRenderable("MeshRenderable");

                Core::MeshRenderable* renderable = dynamic_cast<Core::MeshRenderable*>(object->getRenderable());

                if(renderable)
                {
                    renderable->setMaterial(PathCoreMaterials + "Default");

                    if(Utils::String::IsEqual(text, NameCubeMesh))
                    {
                        renderable->setMesh(PathCoreMeshes + "Cube/Cube");    // Our default models are stored as OBJs. So Cube is the file name, while the second Cube is the Mesh
                    }
                    else if(Utils::String::IsEqual(text, NameSphereMesh))
                    {
                        renderable->setMesh(PathCoreMeshes + "Sphere/Sphere");
                    }
                    else if(Utils::String::IsEqual(text, NameTorusMesh))
                    {
                        renderable->setMesh(PathCoreMeshes + "Torus/Torus");
                    }
                    else if(Utils::String::IsEqual(text, NamePlaneMesh))
                    {
                        renderable->setMesh(PathCoreMeshes + "Plane/Plane");
                    }
                }
            }
        }

        void MainMenuBar::onSceneAddLight()
        {
            QAction* action = dynamic_cast<QAction*>(sender());

            if(action)
            {
                const std::string text = action->text().toStdString();
                Core::SceneObject* object = OcularScene->createObjectOfType(text, text);
            }
        }

        void MainMenuBar::onSceneImportObject()
        {
            const std::string filePath = QFileDialog::getOpenFileName(this, tr("Select SceneObject"), OcularResources->getSourceDirectory().c_str(), "SceneObjects (*.opre *.obj)").toStdString();
            SceneObjectImporter::Import(filePath);
        }

        void MainMenuBar::onSceneProperties()
        {
            if(m_DialogSceneProperties)
            {
                m_DialogSceneProperties->show();
            }
        }

        void MainMenuBar::onToolsMaterialEditor()
        {
            if(m_DialogMaterialEditor)
            {
                m_DialogMaterialEditor->show();
            }
        }

        void MainMenuBar::onHelpAbout()
        {

        }
    }
}