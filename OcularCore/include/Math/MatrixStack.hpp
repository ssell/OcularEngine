/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_MATH_MATRIX_STACK__H__
#define __H__OCULAR_MATH_MATRIX_STACK__H__

#include "Matrix4x4.hpp"
#include "Exception.hpp"
#include <stack>

//------------------------------------------------------------------------------------------

/**
* \addtogroup Ocular
* @{
*/
namespace Ocular
{
    /**
    * \addtogroup Math
    * @{
    */
    namespace Math
    {
        /**
         * \class MatrixStack
         */
        template<typename T>
        class MatrixStack
        {
        public:

            MatrixStack()
            {
            
            }

            ~MatrixStack()
            {
            
            }

            //------------------------------------------------------------------------------

            /**
             * Places an identity matrix on the top of the stack.
             */
            void loadIdentity()
            {
                m_Stack.push(Matrix4x4<T>());
            }

            /**
             * Combines the matrix (via concatenation) at the top of the
             * matrix stack with the provided matrix.<br/><br/>
             *
             * If the stack is empty, the matrix is placed directly onto
             * the stack unmodified.
             *
             * \param[in] matrix Matrix to combine with the top of the stack.
             */
            void combine(Matrix4x4<T> const matrix)
            {
                if(empty())
                {
                    m_Stack.push(matrix);
                }
                else 
                {
                    Matrix4x4<T> top;
                    pop(&top);

                    top *= matrix;

                    m_Stack.push(top);
                }
            }

            /**
             * Pushes the provided matrix directly on top of the stack.<br/>
             * Note that this does not combine matrices like combine does.
             *
             * \param[in] matrix Matrix to place at the top of the stack.
             */
            void push(Matrix4x4<T> const matrix)
            {
                m_Stack.push(matrix);
            }

            /**
             * Removes the matrix at the top of the stack and places it at 
             * the provided address reference.
             *
             * \param[in] matrix Matrix to copy the top of the stack onto.
             * \return True if there was a matrix to pop, else false.
             */
            bool pop(Matrix4x4<T>* matrix)
            {
                bool result = false;

                if(!empty())
                {
                    if(matrix != nullptr)
                    {
                        *matrix = m_Stack.top();
                    }

                    m_Stack.pop();
                    result = true;
                }

                return result;
            }

            /**
             * Copies the matrix at the top of the stack into the specified reference.
             *
             * \param[in] matrix Matrix to copy the top of the stack onto.
             * \return True if there was a matrix to peek, else false.
             */
            bool peek(Matrix4x4<T>* matrix)
            {
                bool result = false;

                if(!empty())
                {
                    if(matrix != nullptr)
                    {
                        *matrix = m_Stack.top();
                    }

                    result = true;
                }

                return result;
            }

            /**
             * \return True if the matrix stack is empty.
             */
            bool empty()
            {
                return m_Stack.empty();
            }

            /**
             * \return The number of element in the stack.
             */
            unsigned size()
            {
                return static_cast<unsigned>(m_Stack.size());
            }

            /**
             * Removes all elements from the stack.
             */
            void clear()
            {
                while(!m_Stack.empty())
                {
                    m_Stack.pop();
                }
            }

        protected:

        private:

            std::stack<Matrix4x4<T>> m_Stack;
        };

        typedef MatrixStack<double> MatrixStackd;
        typedef MatrixStack<float> MatrixStackf;
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