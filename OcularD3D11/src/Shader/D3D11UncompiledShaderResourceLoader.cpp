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

#include "stdafx.hpp"
#include "Shader/D3D11UncompiledShaderResourceLoader.hpp"
#include "Resources/ResourceLoaderRegistrar.hpp"

#include "D3D11GraphicsDriver.hpp"
#include "Graphics/Shader/ShaderProgram.hpp"
#include "Shader/D3D11VertexShader.hpp"
#include "Shader/D3D11GeometryShader.hpp"
#include "Shader/D3D11FragmentShader.hpp"
#include "Shader/D3D11PreTessellationShader.hpp"
#include "Shader/D3D11PostTessellationShader.hpp"

#include <d3dcompiler.h>

//------------------------------------------------------------------------------------------

OCULAR_REGISTER_RESOURCE_LOADER(Ocular::Graphics::D3D11UncompiledShaderResourceLoader)

static const std::array<LPCSTR, 4> VertexEntryPoints   = { "VertexMain", "VertMain", "VSMain", "MainVS" };
static const std::array<LPCSTR, 3> GeometryEntryPoints = { "GeometryMain", "GSMain", "MainGS" };
static const std::array<LPCSTR, 8> FragmentEntryPoints = { "FragmentMain", "FragMain", "FSMain", "MainFS", "PixelMain", "PixMain", "PSMain", "MainPS" };
static const std::array<LPCSTR, 5> PreTessEntryPoints  = { "PreTessellationMain", "PreTessMain", "HullMain", "HSMain", "MainHS" };
static const std::array<LPCSTR, 5> PostTessEntryPoints = { "PostTessellationMain", "PostTessMain", "DomainMain", "DSMain", "MainDS" };

static const char* EntryPointError = "entrypoint not found";    // The D3DBlob error reported when a specified shader entry wasn't valid

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Graphics
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        D3D11UncompiledShaderResourceLoader::D3D11UncompiledShaderResourceLoader()
            : Core::AResourceLoader(".hlsl", Core::ResourceType::ShaderProgram),
              m_D3DDevice(nullptr),
              m_D3DDeviceContext(nullptr)
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
            D3D11UncompiledShaderResourceLoader* other = new D3D11UncompiledShaderResourceLoader();

            bool result = false;

            if(isFileValid(file))
            {
                if(getD3DDevice())
                {
                    ShaderProgram* program = new ShaderProgram();
                    program->setSourceFile(file);

                    //--------------------------------------------------------
                    // Convert the file path to wchar

                    std::string strPath = file.getFullPath();
                    std::wstring wstrPath = std::wstring(strPath.begin(), strPath.end());
                    LPCWSTR lpcwstrPath = wstrPath.c_str();

                    //--------------------------------------------------------

                    if(compileVertexShader(file, lpcwstrPath, program))
                    {
                        // Getting here does not mean that vertex compilation necessarily succeeded.
                        // It just means there is no critical error in the file. See header comments for more.

                        compileGeometryShader(file, lpcwstrPath, program);
                        compileFragmentShader(file, lpcwstrPath, program);
                        compilePreTessellationShader(file, lpcwstrPath, program);
                        compilePostTessellationShader(file, lpcwstrPath, program);

                        resource = program;
                        result = true;
                    }
                    else
                    {
                        delete program;
                        program = nullptr;
                    }
                }
                else
                {
                    OcularLogger->error("Failed to retrieve D3D Device", OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "loadResource"));
                }
            }
            else
            {
                OcularLogger->error("Resource file at '", file.getFullPath(), "' is invalid", OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "loadResource"));
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
                    m_D3DDeviceContext = driver->getD3DDeviceContext();

                    if((m_D3DDevice == nullptr) || (m_D3DDeviceContext == nullptr))
                    {
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

        bool D3D11UncompiledShaderResourceLoader::compileVertexShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            bool result = true;

            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a Vertex Shader from all of our entry points

                for(uint32_t i = 0; i < VertexEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, VertexEntryPoints[i], "vs_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                    else if(errorLog)
                    {
                        if(!isEntryPointError(errorLog))
                        {
                            // If entry point is simply not found, we do not care.
                            // But if it is some other kind of compilation error then we wish to report it.

                            OcularLogger->error("Failed to compile shader with error: ", (char*)errorLog->GetBufferPointer(), OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileVertexShader"));
                            result = false;
                            
                            errorLog->Release();

                            break;
                        }

                        errorLog->Release();
                    }
                }

                //--------------------------------------------------------
                // If we compiled successfully, then attempt to create the actual shader interface

                if(result && hResult == S_OK)
                {
                    ID3D11VertexShader* d3dShader = nullptr;
                    hResult = m_D3DDevice->CreateVertexShader(compiled->GetBufferPointer(), compiled->GetBufferSize(), NULL, &d3dShader);

                    if(hResult == S_OK)
                    {
                        D3D11VertexShader* shader = new D3D11VertexShader(m_D3DDevice, m_D3DDeviceContext);
                        shader->setSourceFile(file);
                        shader->setD3DShader(d3dShader);
                        shader->setD3DBlob(compiled);

                        program->setVertexShader(shader);
                    }
                    else
                    {
                        if(compiled)
                        {
                            compiled->Release();
                        }

                        OcularLogger->error("Failed to create Vertex Shader with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileVertexShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }

            return result;
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
                    hResult = D3DCompileFromFile(source, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, VertexEntryPoints[i], "gs_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                    else if(errorLog)
                    {
                        errorLog->Release();
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
                        D3D11GeometryShader* shader = new D3D11GeometryShader(m_D3DDeviceContext);
                        shader->setSourceFile(file);
                        shader->setD3DShader(d3dShader);
                        shader->setD3DBlob(compiled);

                        program->setGeometryShader(shader);
                    }
                    else
                    {
                        if(compiled)
                        {
                            compiled->Release();
                        }

                        OcularLogger->error("Failed to create Geometry Shader with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileGeometryShader"));
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
                    hResult = D3DCompileFromFile(source, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, FragmentEntryPoints[i], "ps_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                    else if(errorLog)
                    {
                        errorLog->Release();
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
                        D3D11FragmentShader* shader = new D3D11FragmentShader(m_D3DDeviceContext);
                        shader->setSourceFile(file);
                        shader->setD3DShader(d3dShader);
                        shader->setD3DBlob(compiled);

                        program->setFragmentShader(shader);
                    }
                    else
                    {
                        if(compiled)
                        {
                            compiled->Release();
                        }

                        OcularLogger->error("Failed to create Fragment Shader with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compileFragmentShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        void D3D11UncompiledShaderResourceLoader::compilePreTessellationShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a PreTessellation Shader from all of our entry points

                for(uint32_t i = 0; i < PreTessEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, PreTessEntryPoints[i], "hs_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                    else if(errorLog)
                    {
                        errorLog->Release();
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
                        D3D11PreTessellationShader* shader = new D3D11PreTessellationShader(m_D3DDeviceContext);
                        shader->setSourceFile(file);
                        shader->setD3DShader(d3dShader);
                        shader->setD3DBlob(compiled);

                        program->setPreTessellationShader(shader);
                    }
                    else
                    {
                        if(compiled)
                        {
                            compiled->Release();
                        }

                        OcularLogger->error("Failed to create PreTessellation Shader with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compilePreTessellationShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        void D3D11UncompiledShaderResourceLoader::compilePostTessellationShader(Core::File const& file, LPCWSTR source, ShaderProgram* program)
        {
            if(source && program)
            {
                ID3DBlob* compiled = nullptr;
                ID3DBlob* errorLog = nullptr;

                HRESULT hResult = S_FALSE;

                //--------------------------------------------------------
                // Attempt to compile out a PostTessellation Shader from all of our entry points

                for(uint32_t i = 0; i < PostTessEntryPoints.size(); i++)
                {
                    hResult = D3DCompileFromFile(source, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, PostTessEntryPoints[i], "ds_5_0", 0, 0, &compiled, &errorLog);

                    if(hResult == S_OK)
                    {
                        // Found a valid entry point
                        break;
                    }
                    else if(errorLog)
                    {
                        errorLog->Release();
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
                        D3D11PostTessellationShader* shader = new D3D11PostTessellationShader(m_D3DDeviceContext);
                        shader->setSourceFile(file);
                        shader->setD3DShader(d3dShader);
                        shader->setD3DBlob(compiled);

                        program->setPostTessellationShader(shader);
                    }
                    else
                    {
                        if(compiled)
                        {
                            compiled->Release();
                        }

                        OcularLogger->error("Failed to create PostTessellation Shader with error ", Utils::String::FormatHex(hResult), OCULAR_INTERNAL_LOG("D3D11UncompiledShaderResourceLoader", "compilePostTessellationShader"));
                    }
                }
                // else
                // {
                    // Not finding an entry point is ok and not an error.
                    // The ShaderProgram will just have NULL for this particular shader type.
                // }
            }
        }

        bool D3D11UncompiledShaderResourceLoader::isEntryPointError(ID3DBlob* errorLog) const
        {
            bool result = false;
            const std::string stringLog((char*)errorLog->GetBufferPointer());

            if(stringLog.find(EntryPointError) != std::string::npos)
            {
                // Was an entrypoint error
                result = true;
            }

            return result;
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}