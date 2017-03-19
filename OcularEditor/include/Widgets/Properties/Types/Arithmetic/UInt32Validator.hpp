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
#ifndef __H__OCULAR_EDITOR_UINT32_VALIDATOR__H__
#define __H__OCULAR_EDITOR_UINT32_VALIDATOR__H__

#include <QtGui/qvalidator.h>

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
         * \class UIntValidator
         *
         * Implementation of QValidator which handles 32-bit unsigned integers.
         * This is needed as the built-in QIntValidator only supports 32-bit signed.
         */
        class UInt32Validator : public QValidator
        {
        public:

            UInt32Validator(QObject* parent = nullptr);
            virtual ~UInt32Validator();

            virtual State validate(QString& input, int& pos) const override;

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