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
#ifndef __H__OCULAR_GRAPHICS_VIEWPORT__H__
#define __H__OCULAR_GRAPHICS_VIEWPORT__H__

#include <cstdint>

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Graphics
     * @{
     */
    namespace Graphics
    {
        /**
         * \class Viewport
         */
        class Viewport
        {
        public:

            Viewport(float x, float y, float width, float height, float minDepth = 0.0f, float maxDepth = 1.0f);
            ~Viewport();

            virtual void bind();

            float getOriginX() const;
            float getOriginY() const;
            float getWidth() const;
            float getHeight() const;
            float getMinDepth() const;
            float getMaxDepth() const;

        protected:

            float m_OriginX;
            float m_OriginY;
            float m_Width;
            float m_Height;
            float m_MinDepth;
            float m_MaxDepth;

        private:
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