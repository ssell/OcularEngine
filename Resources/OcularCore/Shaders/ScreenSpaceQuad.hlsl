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

struct VSOutput
{
    float4 position : SV_Position;
};

struct PSInput
{
    float4 position : SV_Position;
    float2 uv0      : TEXCOORD0;
};

struct PSOutput
{
    float4 color : SV_Target;
};

Texture2DMS<float4> RenderTexture : register(t0);

SamplerState Sampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

//------------------------------------------------------------------------------------------
// Vertex Shader
//------------------------------------------------------------------------------------------

VSOutput VSMain(uint vertID : SV_VERTEXID) : SV_Position
{
    VSOutput output = (VSOutput)0;

    output.position = float4(0.0f, 0.0f, 0.0f, 1.0f);

    return output;
}

//------------------------------------------------------------------------------------------
// Geometry Shader
//------------------------------------------------------------------------------------------

[maxvertexcount(6)]
void GSMain(point VSOutput input[1], inout TriangleStream<PSInput> outputStream)
{
    //--------------------------------------------------------------------
    // Create bottom-left vertex
    
    PSInput bottomLeft = (PSInput)0;

    bottomLeft.position = float4(-1.0f, -1.0f, 0.0f, 1.0f);
    bottomLeft.uv0 = float2(0.0f, 1.0f);
    
    //--------------------------------------------------------------------
    // Create bottom-right vertex
    
    PSInput bottomRight = (PSInput)0;

    bottomRight.position = float4(1.0f, -1.0f, 0.0f, 1.0f);
    bottomRight.uv0 = float2(1.0f, 1.0f);
    
    //--------------------------------------------------------------------
    // Create top-right vertex
    
    PSInput topRight = (PSInput)0;

    topRight.position = float4(1.0f, 1.0f, 0.0f, 1.0f);
    topRight.uv0 = float2(1.0f, 0.0f);
    
    //--------------------------------------------------------------------
    // Create top-left vertex
    
    PSInput topLeft = (PSInput)0;

    topLeft.position = float4(-1.0f, 1.0f, 0.0f, 1.0f);
    topLeft.uv0 = float2(0.0f, 0.0f);

    //--------------------------------------------------------------------
    // Build stream 

    outputStream.Append(bottomLeft);
    outputStream.Append(bottomRight);
    outputStream.Append(topRight);

    outputStream.RestartStrip();

    outputStream.Append(topRight);
    outputStream.Append(topLeft);
    outputStream.Append(bottomLeft);
}


//------------------------------------------------------------------------------------------
// Pixel Shader
//------------------------------------------------------------------------------------------

PSOutput PSMain(PSInput input)
{
    PSOutput output;
    
    float width  = 0.0f;
    float height = 0.0f;
    float count  = 0.0f;

    RenderTexture.GetDimensions(width, height, count);

    float4 sumColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

    for(uint i = 0; i < (uint)count; ++i)
    {
        sumColor += RenderTexture.Load((int2)input.position, i);
    }

    output.color = sumColor * (1.0f / count);

    return output;
}