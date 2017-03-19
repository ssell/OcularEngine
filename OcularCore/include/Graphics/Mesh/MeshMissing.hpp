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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_MESH_MISSING__H__
#define __H__OCULAR_GRAPHICS_MESH_MISSING__H__

#include "Mesh.hpp"

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
         * \class MeshMissing
         * \brief Special default 'missing' Mesh. Typically used internally.
         */
        class MeshMissing : public Mesh
        {
        public:

            MeshMissing();
            virtual ~MeshMissing();

            /**
             * \return Always returns TRUE while performing no action.
             */
            virtual bool bind() override;

            /**
             * Performs no action.
             */
            virtual void unbind() override;

            /**
             * Performs no action.
             */
            virtual void unload() override;

        protected:

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