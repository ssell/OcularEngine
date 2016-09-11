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

#include "OcularLighting.hlsl"

//------------------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------------------

struct VSOutput
{
    float4 position : SV_Position;
    float4 color    : COLOR0;
    float4 normal   : NORMAL0;
    float4 uv0      : TEXCOORD0;
    float4 worldPos : TEXCOORD4;
};

struct PSOutput
{
    float4 color : SV_Target;
};

Texture2D g_DiffuseTexture : register(t0);

SamplerState Sampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = CLAMP;
    AddressV = CLAMP;
};

//------------------------------------------------------------------------------------------
// Vertex Shader
//------------------------------------------------------------------------------------------

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    
    output.worldPos = mul(input.position, _ModelMatrix);
    output.position = mul(input.position, _ModelViewProjMatrix);
    output.normal   = normalize(mul(input.normal, _NormalMatrix));
    output.color    = input.color;
    output.uv0      = input.uv0;

    return output;
}

//------------------------------------------------------------------------------------------
// Pixel Shader
//------------------------------------------------------------------------------------------

PSOutput PSMain(VSOutput input) : SV_Target
{
    PSOutput output;

    const float4 texColor = g_DiffuseTexture.Sample(Sampler, input.uv0.xy);
    const float4 light = calcRadiancePhong(input.worldPos, input.normal);

    output.color = (texColor * light);

    return output;
}