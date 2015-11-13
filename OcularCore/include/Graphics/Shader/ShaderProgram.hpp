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

#pragma once
#ifndef __H__OCULAR_GRAPHICS_SHADER_PROGRAM__H__
#define __H__OCULAR_GRAPHICS_SHADER_PROGRAM__H__

#include "Resources/Resource.hpp"

#include "VertexShader.hpp"
#include "GeometryShader.hpp"
#include "FragmentShader.hpp"
#include "PreTesselationShader.hpp"
#include "PostTesselationShader.hpp"

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
         * \class ShaderProgram
         *
         * A ShaderProgram is a collection of individual shader objects.
         *
         * When a shader file is loaded (.hlsl, .glsl, etc.), a ShaderProgram
         * object is created that contains all individual shaders found within 
         * the file.
         *
         */
        class ShaderProgram : public Core::Resource 
        {
        public:

            ShaderProgram();
            ~ShaderProgram();

            virtual void unload() override;

            /**
             * Sets the Vertex Shader that belongs to this shader program.
             * \param[in] shader
             */
            void setVertexShader(VertexShader* shader);

            /**
             * Returns a pointer to the Vertex Shader that belongs to this shader program.
             * \return Pointer to the Vertex Shader; Returns NULL if no Vertex Shader is present.
             */
            VertexShader* getVertexShader();

            /**
             * Sets the Geometr Shader that belongs to this shader program.
             * \param[in] shader
             */
            void setGeometryShader(GeometryShader* shader);

            /**
             * Returns a pointer to the Geometry Shader that belongs to this shader program.
             * \return Pointer to the Geometry Shader; Returns NULL if no Geometry Shader is present.
             */
            GeometryShader* getGeometryShader();

            /**
             * Sets the Fragment Shader that belongs to this shader program.
             * \param[in] shader
             */
            void setFragmentShader(FragmentShader* shader);

            /**
             * Returns a pointer to the Fragment Shader that belongs to this shader program.
             * \return Pointer to the Fragment Shader; Returns NULL if no Fragment Shader is present.
             */
            FragmentShader* getFragmentShader();

            /**
             * Sets the Pre-Tesselation Shader that belongs to this shader program.
             * \param[in] shader
             */
            void setPreTesselationShader(PreTesselationShader* shader);

            /**
             * Returns a pointer to the Pre-Tesselation Shader that belongs to this shader program.
             * \return Pointer to the Pre-Tesselation Shader; Returns NULL if no Pre-Tesselation Shader is present.
             */
            PreTesselationShader* getPreTesselationShader();

            /**
             * Sets the Post-Tesselation Shader that belongs to this shader program.
             * \param[in] shader
             */
            void setPostTesselationShader(PostTesselationShader* shader);

            /**
             * Returns a pointer to the Post-Tesselation Shader that belongs to this shader program.
             * \return Pointer to the Post-Tesselation Shader; Returns NULL if no Post-Tesselation Shader is present.
             */
            PostTesselationShader* getPostTesselationShader();

            /**
             * Sets the Pixel Shader that belongs to this shader program.
             *
             * \note This method is identical to ShaderProgram::setPixelShader
             * \param[in] shader
             */
            void setPixelShader(PixelShader* shader);

            /**
             * Returns a pointer to the Pixel Shader that belongs to this shader program.
             *
             * \note This method is identical to ShaderProgram::setFragmentShader
             * \return Pointer to the Pixel Shader; Returns NULL if no Pixel Shader is present.
             */
            PixelShader* getPixelShader();

            /**
             * Sets the Hull Shader that belongs to this shader program.
             *
             * \note This method is identical to ShaderProgram::setPreTesselationShader
             * \param[in] shader
             */
            void setHullShader(HullShader* shader);

            /**
             * Returns a pointer to the Hull Shader that belongs to this shader program.
             *
             * \note This method is identical to ShaderProgram::getPreTesselationShader
             * \return Pointer to the Hull Shader; Returns NULL if no Hull Shader is present.
             */
            HullShader* getHullShader();

            /**
             * Sets the Domain Shader that belongs to this shader program.
             *
             * \note This method is identical to ShaderProgram::setPostTesselationShader
             * \param[in] shader
             */
            void setDomainShader(DomainShader* shader);

            /**
             * Returns a pointer to the Domain Shader that belongs to this shader program.
             *
             * \note This method is identical to ShaderProgram::setPostTesselationShader
             * \return Pointer to the Domain Shader; Returns NULL if no Domain Shader is present.
             */
            DomainShader* getDomainShader();

        protected:
            
            VertexShader*          m_VertexShader;
            GeometryShader*        m_GeometryShader;
            FragmentShader*        m_FragmentShader;
            PreTesselationShader*  m_PreTesselationShader;
            PostTesselationShader* m_PostTesselationShader;

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