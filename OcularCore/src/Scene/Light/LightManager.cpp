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

#include "Scene/Light/LightManager.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        LightManager::LightManager()
        {

        }

        LightManager::~LightManager()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        void LightManager::updateLights(bool const cullVisible)
        {
            std::vector<LightSource*> visibleLights;

            getVisibleLights(visibleLights, cullVisible);
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void LightManager::registerLightSource(LightSource* light)
        {
            if(light)
            {
                const std::string uuidStr = light->getUUID().toString();
                auto find = m_Lights.find(uuidStr);

                if(find == m_Lights.end())
                {
                    m_Lights.insert(std::make_pair(uuidStr, light));
                }
            }
        }

        void LightManager::unregisterLightSource(LightSource* light)
        {
            if(light)
            {
                const std::string uuidStr = light->getUUID().toString();
                auto find = m_Lights.find(uuidStr);

                if(find == m_Lights.end())
                {
                    m_Lights.erase(find);
                }
            }
        }

        void LightManager::getVisibleLights(std::vector<LightSource*>& visibleLights, bool cull)
        {
            visibleLights.reserve(m_Lights.size());

            if(cull)
            {

            }
            else
            {
                for(auto pair : m_Lights)
                {
                    visibleLights.emplace_back(pair.second);
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}