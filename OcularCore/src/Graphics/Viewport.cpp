/**
* Copyright 2014-2015 Steven T Sell (ssell@vertexfragment.com)
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

#include "Graphics/Viewport.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Viewport::Viewport(float const x, float const y, float const width, float const height, float const minDepth, float const maxDepth)
            : m_OriginX(x),
              m_OriginY(y),
              m_Width(width),
              m_Height(height),
              m_MinDepth(minDepth),
              m_MaxDepth(maxDepth)
        {
        
        }

        Viewport::~Viewport()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Viewport::bind()
        {
        
        }

        float Viewport::getOriginX() const
        {
            return m_OriginX;
        }

        float Viewport::getOriginY() const
        {
            return m_OriginY;
        }

        float Viewport::getWidth() const
        {
            return m_Width;
        }

        float Viewport::getHeight() const
        {
            return m_Height;
        }

        float Viewport::getMinDepth() const
        {
            return m_MinDepth;
        }

        float Viewport::getMaxDepth() const
        {
            return m_MaxDepth;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}