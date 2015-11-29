/**
 * Copyright 2014-2015 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Scene/Camera/CameraManager.hpp"
#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        CameraManager::CameraManager()
            : m_MainCamera(nullptr),
              m_ActiveCamera(nullptr),
              m_UniformBuffer(nullptr)
        {

        }

        CameraManager::~CameraManager()
        {
            if(m_UniformBuffer)
            {
                delete m_UniformBuffer;
                m_UniformBuffer = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------=

        void CameraManager::initialize()
        {
            m_UniformBuffer = OcularGraphics->createUniformBuffer(Graphics::UniformBufferType::PerCamera);
        }

        Camera* CameraManager::getMainCamera() const
        {
            return m_MainCamera;
        }

        Camera* CameraManager::getActiveCamera() const
        {
            return m_ActiveCamera;
        }

        void CameraManager::setMainCamera(Camera* camera)
        {
            m_MainCamera = camera;
        }

        void CameraManager::setActiveCamera(Camera* camera)
        {
            m_ActiveCamera = camera;

            if(m_ActiveCamera && m_UniformBuffer)
            {
                m_UniformPerCamera.eyePosition = camera->getTransform().getPosition();
                m_UniformPerCamera.viewMatrix  = camera->getViewMatrix();
                m_UniformPerCamera.projMatrix  = camera->getProjectionMatrix();

                m_UniformBuffer->setFixedData(sizeof(Graphics::UniformPerCamera), &m_UniformPerCamera);
                m_UniformBuffer->bind();
            }
        }

        std::vector<Camera*> const& CameraManager::getCameras() const
        {
            return m_Cameras;
        }


        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void CameraManager::addCamera(Camera* camera)
        {
            if(camera)
            {
                bool alreadyTracked = false;

                for(auto iter = m_Cameras.begin(); iter != m_Cameras.end(); ++iter)
                {
                    if((*iter) == camera)
                    {
                        alreadyTracked = true;
                        break;
                    }
                }

                if(!alreadyTracked)
                {
                    if(m_Cameras.empty())
                    {
                        m_Cameras.push_back(camera);
                        m_MainCamera = camera;
                    }
                    else
                    {
                        bool inserted = false;
                        Priority priority = camera->getPriority();

                        for(auto iter = m_Cameras.begin(); iter != m_Cameras.end(); ++iter)
                        {
                            if(priority < (*iter)->getPriority())
                            {
                                m_Cameras.insert(iter, camera);
                                inserted = true;

                                break;
                            }
                        }

                        if(!inserted)
                        {
                            m_Cameras.push_back(camera);
                        }
                    }
                }
            }
        }

        void CameraManager::removeCamera(Camera* camera)
        {
            if(camera)
            {
                for(auto iter = m_Cameras.begin(); iter != m_Cameras.end(); ++iter)
                {
                    if((*iter) == camera)
                    {
                        m_Cameras.erase(iter);

                        if(camera == m_MainCamera)
                        {
                            if(m_Cameras.size() > 0)
                            {
                                m_MainCamera = m_Cameras[0];
                            }
                            else
                            {
                                m_MainCamera = nullptr;
                            }
                        }

                        if(camera == m_ActiveCamera)
                        {
                            m_ActiveCamera = nullptr;
                        }

                        break;
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}