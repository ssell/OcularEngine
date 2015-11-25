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
              m_ActiveCamera(nullptr)
        {

        }

        CameraManager::~CameraManager()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------=

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
                    m_Cameras.push_back(camera);

                    // If it is the first/only camera, it automatically becomes the main camera
                    if(m_Cameras.size() == 1)
                    {
                        m_MainCamera = camera;
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