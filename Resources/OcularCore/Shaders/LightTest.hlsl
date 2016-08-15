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

 #include "OcularCommon.hlsl"

//------------------------------------------------------------------------------------------

struct GPULight
{
    float4 position;
    float4 direction;
    float4 color;
    float4 parameters;    // .x = intensity; .y = range; .z = angle; .w = type (1 = point, 2 = spot, 3 = directional)
};

StructuredBuffer<GPULight> LightBuffer : register(t8);

//------------------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------------------

struct VSOutput
{
    float4 position : SV_Position;
    float4 color    : COLOR0;
    float4 uv0      : TEXCOORD0;
};

struct PSOutput
{
    float4 color : SV_Target;
};

//------------------------------------------------------------------------------------------
// Vertex Shader
//------------------------------------------------------------------------------------------

VSOutput VSMain(VSInput input)
{
    matrix mvpMatrix = mul(_ModelMatrix, _ViewProjMatrix);

    VSOutput output;
    output.position = mul(input.position, mvpMatrix);
    output.color    = input.color;// * calcLightingIntensitySimpleCos(input.normal, float4(0.0, 1000.0, 0.0, 1.0)) * 0.75f;
    output.uv0      = input.uv0;

    return output;
}

//------------------------------------------------------------------------------------------
// Pixel Shader
//------------------------------------------------------------------------------------------

float4 PSMain(VSOutput input) : SV_Target
{
    float4 color = LightBuffer[0].color;
    return color;
}