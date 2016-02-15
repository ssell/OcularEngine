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

/**
 * A basic, generic flat shader. Simply renders the geometry in a single color.
 */

#include "OcularCommon.hlsl"
#include "OcularLighting.hlsl"

cbuffer cbPerMaterial : register(b3)
{
    float4 _Color;
};

struct VSOutput
{
    float4 position     : SV_Position;
    float4 color        : COLOR0;
    float4 normal       : COLOR1;
    float4 fragPosition : COLOR2;
};

struct PSOutput
{
    float4 color : SV_Target;
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.fragPosition = mul(input.position, _ModelMatrix);
    output.position     = mul(output.fragPosition, _ViewProjMatrix);
    output.normal       = mul(float4(input.normal.xyz, 1.0f), _ModelMatrix);
    output.color        = input.color;

    return output;
}

float4 PSMain(VSOutput input) : SV_Target
{
    float4 lightPos = float4(0.0f, 100.0f, 0.0f, 1.0f);
    float4 outColor = input.color;

    float angle = dot(input.normal, normalize(lightPos - input.fragPosition));

    outColor *= angle * _Color;

    return outColor;
}