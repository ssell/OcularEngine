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

#ifndef __HLSL_OCULAR_LIGHTING_HLSL__
#define __HLSL_OCULAR_LIGHTING_HLSL__

#include "OcularCommon.hlsl"

//------------------------------------------------------------------------------------------

struct GPULight
{
    float4 position;
    float4 direction;
    float4 color;
    float4 attenuation;   // .x = constant; .y = linear; .z = quadratic; .w = range
    float4 parameters;    // .x = intensity; .y = angle; .z = light type
};

StructuredBuffer<GPULight> _LightBuffer : register(t8);

//------------------------------------------------------------------------------------------

/**
 * Calculates a simple lambertian diffuse term.
 */
float4 calcLambertianDiffuse(in float4 color)
{
	return (color * PI_UNDER_ONE);
}

/**
 * Calculates the ideal reflection vector.
 */
float4 calcReflectionVector(in float4 normal, in float4 toLight)
{
	return normalize(2.0f * dot(normal, toLight) * normal - toLight);
}

/**
 * Calculates the attenuation term using the standard Constant-Linear-Quadratic model.
 *
 * \param[in] toLight     Unnormalized vector pointing from the surface to the light source.
 * \param[in] attenuation .x = constant term; .y = linear term; .z = quadratic term; .w = range.
 */
float calcAttenuation(in float4 toLight, in float4 attenuation)
{
    const float dist = length(toLight);

    float result = 0.0f;

    if(dist < attenuation.w)
    {
    	const float constant  = attenuation.x;
	    const float linearr   = attenuation.y * dist;
	    const float quadratic = attenuation.z * dist * dist;

	    const float denom = constant + linearr + quadratic;

	    result = 1.0f / denom;
    }

	return result;
}

/**
 * Calculates the clamped cosine of the angle between vector A and vector B.
 */
float ccosAngle(in float4 vecA, in float4 vecB)
{
	return saturate(dot(vecA, vecB));
}

/**
 * Implementation of the Phong BRDF.
 *
 * Is reflection-vector-based instead of half-vector-based. 
 * A more realistic, half-vector implementation is the blinnPhongBRDF function.
 *
 * \param[in] normal    The macroscopic surface normal. (n)
 * \param[in] toLight   Normalized direction vector pointing to the light source. (l)
 * \param[in] toView    Normalized direction vector pointing to the eye point. (v)
 * \param[in] diffuse   The material/object diffuse color. (cdiff)
 * \param[in] specular  The material/object specular color. (cspec)
 * \param[in] roughness Controls surface roughness. (m)
 */
float4 phongBRDF(in float4 normal, in float4 toLight, in float4 toView, in float4 diffuse, in float4 specular, in float roughness)
{
	const float4 colorDiff = calcLambertianDiffuse(diffuse);

	const float4 reflVector = calcReflectionVector(normal, toLight);
	const float  angleReflection = ccosAngle(toLight, reflVector);
	const float4 colorSpecular = ((roughness + 2) * PI_TWO_UNDER_ONE) * specular * pow(angleReflection, roughness);

	return (colorDiff + colorSpecular);
}

float4 calcRadiancePhong(in float4 pixWorldPos, in float4 normal)
{
	const float4 toView = normalize(_EyePosition - pixWorldPos);
    const float4 ambient = _LightBuffer[0].color * _LightBuffer[0].parameters.x;

    float4 radiance = float4(0.0f, 0.0f, 0.0f, 1.0f);

    // Loop over each dynamic light 
    // In the ambient light (index 0) we store the number of lights in the type slot (includes ambient light in count)

    [loop]
    for(uint i = 1; i < _LightBuffer[0].parameters.z; i++)
    {
        const float4 toLight     = _LightBuffer[i].position - pixWorldPos;
        const float4 toLightNorm = normalize(toLight);
        const float4 brdf        = phongBRDF(normal, toLightNorm, toView, float4(1.0f, 1.0f, 1.0f, 1.0f), float4(0.1f, 0.1, 0.1, 1.0f), 4.0f);
        const float4 light       = _LightBuffer[i].color * _LightBuffer[i].parameters.x;
        const float  attenuation = calcAttenuation(toLight, _LightBuffer[i].attenuation);

        radiance += light * brdf * attenuation * ccosAngle(normal, toLightNorm);
    }

    return (ambient + radiance);
}

//------------------------------------------------------------------------------------------

#endif