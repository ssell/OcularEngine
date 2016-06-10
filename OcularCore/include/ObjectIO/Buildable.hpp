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
#ifndef __H__OCULAR_CORE_BUILDABLE__H__
#define __H__OCULAR_CORE_BUILDABLE__H__

#include "BuilderNode.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        /**
         * \class Buildable
         *
         * When inheriting from Buildable, a class is allowing for itself to be loaded 
         * from, and saved to, various file formats. All loading/saving is done via
         * a generic node chain system implemented through the BuilderNode class.
         *
         * Buildables, and their node chains, are typically used when loading/saving:
         *
         *     - Scene files (.oscene)
         *     - SceneObject files (.opref)
         *     - Material files (.omat)
         *
         * A class that inherits from Buildable may also see special automatic behaviour
         * when also inheriting from the Exposable class. This typically includes 
         * automatic building from, and saving to, BuilderNode chains.
         */
        class Buildable
        {
        public:

            /**
             * Alternate creation method (opposed to the constructor) in which one is
             * provided with a BuilderNode chain. This chain may be explored to retrieve
             * any relevant variables, and their values, that may have been stored in it.
             *
             * This method will typically mirror the onSave, in which relevant values are
             * stored within the chain.
             *
             * \param[in] node Node to extract variable information from
             */
            virtual void onLoad(BuilderNode const* node);

            /**
             * Method used to add an object's data to an existing node chain in preparation
             * for being save to a file.
             *
             * \param[in] node Node to place variable information in
             */
            virtual void onSave(BuilderNode* node) const;

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