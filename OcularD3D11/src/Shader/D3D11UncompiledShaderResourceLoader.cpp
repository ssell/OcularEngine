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

#include "stdafx.hpp"
#include "Shader/D3D11UncompiledShaderResourceLoader.hpp"

#include "D3D11GraphicsDriver.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"
#include "Shader/D3D11VertexShader.hpp"
#include "Shader/D3D11GeometryShader.hpp"
#include "Shader/D3D11FragmentShader.hpp"
#include "Shader/D3D11PreTesselationShader.hpp"
#include "Shader/D3D11PostTesselationShader.hpp"

#include <d3dcompiler.h>

//------------------------------------------------------------------------------------------

static const std::array<LPCSTR, 4> VertexEntryPoints   = { "VertexMain", "VertMain", "VSMain", "MainVS" };
static const std::array<LPCSTR, 3> GeometryEntryPoints = { "GeometryMain", "GSMain", "MainGS" };
static const std::array<LPCSTR, 8> FragmentEntryPoints = { "FragmentMain", "FragMain", "FSMain", "MainFS", "PixelMain", "PixMain", "PSMain", "MainPS" };
static const std::array<LPCSTR, 5> PreTessEntryPoints  = { "PreTesselationMain", "PreTessMain", "HullMain", "HSMain", "MainHS" };
static const std::array<LPCSTR, 5> PostTessEntryPoints = { "PostTesselationMain", "PostTessMain", "DomainMain", "DSMain", "MainDS" };

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11UncompiledShaderResourceLoader::D3D11UncompiledShaderResourceLoader()
            : Core::AResourceLoader(".hlsl"),
              m_D3DDevice(nullptr)
        {
        
        }

        D3D11UncompiledShaderResourceLoader::~D3D11UncompiledShaderResourceLoader()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        bool D3D11UncompiledShaderResourceLoader::loadResource(Core::Resource* &resource, Core::File const& file)
        {
            bool result = false;

            if(isFileValid(file) && getD3DDevice())
            {
                ShaderProgram* program = new ShaderProgram();
                program->setSourceFile(file);

                //--------------------------------------------------------
                // Convert the file path to wchar

                std::string strPath = file.getFullPath();
                std::wstring wstrPath = std::wstring(strPath.begin(), strPath.end());
                LPCWSTR lpcwstrPath = wstrPath.c_str();

                //--------------------------------------------------------
                
                compileVertexShader(file, lpcwstrPath, program);
                compileGeometryShader(file, lpcwstrPath, program);
                compileFragmentShader(file, lpcwstrPath, program);
                compilePreTesselationShader(file, lpcwstrPath, program);
                compilePostTesselationShader(file, lpcwstrPath, program);

                //--------------------------------------------------------

                resource = program;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        bool D3D11UncompiledShaderResourceLoader::getD3DDevice()
        {
            bool result = true;

            if(m_D3DDevice == nullptr)
            {
                D3D11GraphicsDriver* driver = dynamic_cast<D3D11GraphicsDriver*>(OcularGraphics.get());

                if(driver)
                {
                    m_D3DDevice = driver->getD3DDevice();

                    if(m_D3DDevice == nullptr)
                    {
                        // Still null?
                        result = false;
                    }
                }
                else
                {
                    result = false;
                }
            }

            return result;
        }

        void D3D11UncompiledShaderResourceLoader::compileVertexShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a Vertex Shader from all of our entry points

                for(uint32_t i = 0; i < VertexEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, NULL, VertexEntryPoints[i], "vs_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                }

                //--------------------------------------------------------
                // If we compiled successfully, then attempt to create the actual shader interface

                if(hResult == S_OK)
                {
                    ID3D11VertexShader* d3dShader = nullptr;
                    hResult = m_D3DDevice->CreateVertexShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, &d3dShader);

                    if(hResult == S_OK)
                    {
                        D3D11VertexShader* shader = new D3D11VertexShader(m_D3DDevice);
                        shader->setD3DShader(d3dShader);
                        shader->setSourceFile(file);

                        program->setVertexShader(shader);
                    }
                    else
                    {
                        OcularLogger->error("Failed to create Vertex Shader with error ", hResult, OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileVertexShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        void D3D11UncompiledShaderResourceLoader::compileGeometryShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a Geometry Shader from all of our entry points

                for(uint32_t i = 0; i < GeometryEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, NULL, VertexEntryPoints[i], "gs_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                }

                //--------------------------------------------------------
                // If we compiled successfully, then attempt to create the actual shader interface

                if(hResult == S_OK)
                {
                    ID3D11GeometryShader* d3dShader = nullptr;
                    hResult = m_D3DDevice->CreateGeometryShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, &d3dShader);

                    if(hResult == S_OK)
                    {
                        D3D11GeometryShader* shader = new D3D11GeometryShader(m_D3DDevice);
                        shader->setD3DShader(d3dShader);
                        shader->setSourceFile(file);

                        program->setGeometryShader(shader);
                    }
                    else
                    {
                        OcularLogger->error("Failed to create Geometry Shader with error ", hResult, OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileGeometryShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        void D3D11UncompiledShaderResourceLoader::compileFragmentShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a Fragment Shader from all of our entry points

                for(uint32_t i = 0; i < FragmentEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, NULL, FragmentEntryPoints[i], "ps_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                }

                //--------------------------------------------------------
                // If we compiled successfully, then attempt to create the actual shader interface

                if(hResult == S_OK)
                {
                    ID3D11PixelShader* d3dShader = nullptr;
                    hResult = m_D3DDevice->CreatePixelShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, &d3dShader);

                    if(hResult == S_OK)
                    {
                        D3D11FragmentShader* shader = new D3D11FragmentShader(m_D3DDevice);
                        shader->setD3DShader(d3dShader);
                        shader->setSourceFile(file);

                        program->setFragmentShader(shader);
                    }
                    else
                    {
                        OcularLogger->error("Failed to create Fragment Shader with error ", hResult, OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileFragmentShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        void D3D11UncompiledShaderResourceLoader::compilePreTesselationShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a PreTesselation Shader from all of our entry points

                for(uint32_t i = 0; i < PreTessEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, NULL, PreTessEntryPoints[i], "hs_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                }

                //--------------------------------------------------------
                // If we compiled successfully, then attempt to create the actual shader interface

                if(hResult == S_OK)
                {
                    ID3D11HullShader* d3dShader = nullptr;
                    hResult = m_D3DDevice->CreateHullShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, &d3dShader);

                    if(hResult == S_OK)
                    {
                        D3D11PreTesselationShader* shader = new D3D11PreTesselationShader(m_D3DDevice);
                        shader->setD3DShader(d3dShader);
                        shader->setSourceFile(file);

                        program->setPreTesselationShader(shader);
                    }
                    else
                    {
                        OcularLogger->error("Failed to create PreTesselation Shader with error ", hResult, OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compilePreTesselationShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        void D3D11UncompiledShaderResourceLoader::compilePostTesselationShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a PostTesselation Shader from all of our entry points

                for(uint32_t i = 0; i < PostTessEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, NULL, PostTessEntryPoints[i], "ds_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                }

                //--------------------------------------------------------
                // If we compiled successfully, then attempt to create the actual shader interface

                if(hResult == S_OK)
                {
                    ID3D11DomainShader* d3dShader = nullptr;
                    hResult = m_D3DDevice->CreateDomainShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, &d3dShader);

                    if(hResult == S_OK)
                    {
                        D3D11PostTesselationShader* shader = new D3D11PostTesselationShader(m_D3DDevice);
                        shader->setD3DShader(d3dShader);
                        shader->setSourceFile(file);

                        program->setPostTesselationShader(shader);
                    }
                    else
                    {
                        OcularLogger->error("Failed to create PostTesselation Shader with error ", hResult, OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compilePostTesselationShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}