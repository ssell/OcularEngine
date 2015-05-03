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

#include "Math/Noise/SimplexNoise.hpp"
#include "Math/MathCommon.hpp"

//------------------------------------------------------------------------------------------

// The gradients are the midpoints of the vertices of a cube.
static const int grad3[12][3] = {
    {1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
    {1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
    {0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};

// Permutation table.  The same list is repeated twice.
static const int perm[512] = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
    250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
    189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
    172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
    228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
    107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,

    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
    250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
    189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,
    172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,
    228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
    107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};


// A lookup table to traverse the simplex around a given point in 4D.
static const int simplex[64][4] = {
    {0,1,2,3},{0,1,3,2},{0,0,0,0},{0,2,3,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,2,3,0},
    {0,2,1,3},{0,0,0,0},{0,3,1,2},{0,3,2,1},{0,0,0,0},{0,0,0,0},{0,0,0,0},{1,3,2,0},
    {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
    {1,2,0,3},{0,0,0,0},{1,3,0,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,3,0,1},{2,3,1,0},
    {1,0,2,3},{1,0,3,2},{0,0,0,0},{0,0,0,0},{0,0,0,0},{2,0,3,1},{0,0,0,0},{2,1,3,0},
    {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},
    {2,0,1,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,0,1,2},{3,0,2,1},{0,0,0,0},{3,1,2,0},
    {2,1,0,3},{0,0,0,0},{0,0,0,0},{0,0,0,0},{3,1,0,2},{0,0,0,0},{3,2,0,1},{3,2,1,0}
};

float dot(const int* g, const float x, const float y) 
{ 
    return (g[0] * x) + (g[1] * y); 
}

float dot(const int* g, const float x, const float y, const float z) 
{ 
    return (g[0] * x) + (g[1] * y) + (g[2] * z); 
}

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Math
    {
        namespace Noise
        {
            //------------------------------------------------------------------------------
            // CONSTRUCTORS
            //------------------------------------------------------------------------------

            SimplexNoise::SimplexNoise()
                : ANoise()
            {
                m_Octaves = 6;
                m_Persistence = 0.5f;
                m_Scale = 0.01f;
            }

            SimplexNoise::~SimplexNoise()
            {
            
            }

            //------------------------------------------------------------------------------
            // PUBLIC METHODS
            //------------------------------------------------------------------------------

            float SimplexNoise::getValue(float const x, float const y)
            {
                float result       = 0.0f;
                float frequency    = m_Scale;
                float amplitude    = 1.0f;
                float maxAmplitude = 0.0f;

                for(uint32_t i = 0; i < m_Octaves; i++)
                {
                    result += getRawNoise((x * frequency), (y * frequency)) * amplitude;
                    
                    frequency *= 2.0f;
                    maxAmplitude += amplitude;
                    amplitude *= m_Persistence;
                }

                return (result / maxAmplitude);
            }

            float SimplexNoise::getValue(float const x, float const y, float const z)
            {
                float result       = 0.0f;
                float frequency    = m_Scale;
                float amplitude    = 1.0f;
                float maxAmplitude = 0.0f;

                for(uint32_t i = 0; i < m_Octaves; i++)
                {
                    result += getRawNoise((x * frequency), (y * frequency), (z * frequency)) * amplitude;
                    
                    frequency *= 2.0f;
                    maxAmplitude += amplitude;
                    amplitude *= m_Persistence;
                }

                return (result / maxAmplitude);
            }

            void SimplexNoise::setOctaves(uint32_t octaves)
            {
                m_Octaves = octaves;
            }

            void SimplexNoise::setPersistence(float persistence)
            {
                m_Persistence = persistence;
            }

            void SimplexNoise::setScale(float scale)
            {
                m_Scale = scale;
            }

            //------------------------------------------------------------------------------
            // PROTECTED METHODS
            //------------------------------------------------------------------------------

            float SimplexNoise::getRawNoise(float const x, float const y)
            {
                float n0 = 0.0f;                         // Noise contributions from the three corners
                float n1 = 0.0f;
                float n2 = 0.0f;
                float F2 = 0.5f * (sqrtf(3.0f) - 1.0f);  // Skew the input space to determine which simplex cell we're in
                float s  = (x + y) * F2;                 // Hairy factor for 2D

                int i = Floor(x + s);
                int j = Floor(y + s);

                float G2 = (3.0f - sqrtf(3.0f)) / 6.0f;
                float t  = (i + j) * G2;
                
                float X0 = i - t;                        // Unskew the cell origin back to (x,y) space
                float Y0 = j - t;
                
                float x0 = x - X0;                       // The x,y distances from the cell origin
                float y0 = y - Y0;

                //--------------------------------------------------------------------------
                // For the 2D case, the simplex shape is an equilateral triangle.
                // Determine which simplex we are in.

                int i1;
                int j1; 
                
                // Offsets for second (middle) corner of simplex in (i,j) coords
                if(x0 > y0) 
                {
                    i1 = 1;  // lower triangle, XY order: (0,0)->(1,0)->(1,1)
                    j1 = 0;
                } 
                else 
                {
                    i1 = 0;  // upper triangle, YX order: (0,0)->(0,1)->(1,1)
                    j1 = 1;
                } 

                //--------------------------------------------------------------------------
                // A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
                // a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
                // c = (3-sqrt(3))/6

                float x1 = x0 - i1 + G2;          // Offsets for middle corner in (x,y) unskewed coords
                float y1 = y0 - j1 + G2;
                float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
                float y2 = y0 - 1.0f + 2.0f * G2;

                // Work out the hashed gradient indices of the three simplex corners
                int ii  = i & 255;
                int jj  = j & 255;
                int gi0 = perm[ii + perm[jj]] % 12;
                int gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
                int gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

                //--------------------------------------------------------------------------
                // Calculate the contribution from the three corners

                float t0 = 0.5f - (x0 * x0) - (y0 * y0);

                if(t0 < 0.0f) 
                {
                    n0 = 0.0f;
                }
                else 
                {
                    t0 *= t0;
                    n0  = t0 * t0 * dot(grad3[gi0], x0, y0); // (x,y) of grad3 used for 2D gradient
                }

                float t1 = 0.5f - (x1 * x1) - (y1 * y1);

                if(t1 < 0.0f) 
                {
                    n1 = 0.0f;
                }
                else 
                {
                    t1 *= t1;
                    n1  = t1 * t1 * dot(grad3[gi1], x1, y1);
                }

                float t2 = 0.5f - (x2 * x2) - (y2 * y2);

                if(t2 < 0.0f)
                {
                    n2 = 0.0f;
                }
                else 
                {
                    t2 *= t2;
                    n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
                }

                //--------------------------------------------------------------------------
                // Add contributions from each corner to get the final noise value.
                // The result is scaled to return values in the interval [-1,1].

                return 70.0f * (n0 + n1 + n2);
            }

            float SimplexNoise::getRawNoise(float const x, float const y, float const z)
            {
                float n0 = 0.0f;                         // Noise contributions from the four corners
                float n1 = 0.0f;
                float n2 = 0.0f;
                float n3 = 0.0f;
                float F3 = 1.0f / 3.0f;                  // Skew the input space to determine which simplex cell we're in
                float s  = (x + y + z) * F3;             // Very nice and simple skew factor for 3D

                int i = Floor(x + s);
                int j = Floor(y + s);
                int k = Floor(z + s);

                float G3 = 1.0f / 6.0f;                  // Very nice and simple unskew factor, too
                float t  = (i + j + k) * G3;
                float X0 = i - t;                        // Unskew the cell origin back to (x,y,z) space
                float Y0 = j - t;
                float Z0 = k - t;
                float x0 = x - X0;                       // The x,y,z distances from the cell origin
                float y0 = y - Y0;
                float z0 = z - Z0;

                //--------------------------------------------------------------------------
                // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
                // Determine which simplex we are in.

                int i1;      // Offsets for second corner of simplex in (i,j,k) coords
                int j1;
                int k1; 
                int i2;      // Offsets for third corner of simplex in (i,j,k) coords
                int j2;
                int k2;

                if(x0 >= y0) 
                {
                    if(y0 >= z0)  // X Y Z order
                    { 
                        i1 = 1; 
                        j1 = 0; 
                        k1 = 0; 
                        i2 = 1; 
                        j2 = 1; 
                        k2 = 0;
                    } 
                    else if(x0 >= z0)  // X Z Y order
                    { 
                        i1 = 1; 
                        j1 = 0; 
                        k1 = 0; 
                        i2 = 1; 
                        j2 = 0; 
                        k2 = 1; 
                    } 
                    else  // Z X Y order
                    { 
                        i1 = 0; 
                        j1 = 0; 
                        k1 = 1; 
                        i2 = 1; 
                        j2 = 0; 
                        k2 = 1; 
                    } 
                }
                else  // x0<y0
                { 
                    
                    if(y0 < z0)  // Z Y X order
                    { 
                        i1 = 0; 
                        j1 = 0; 
                        k1 = 1; 
                        i2 = 0; 
                        j2 = 1; 
                        k2 = 1; 
                    } 
                    else if(x0 < z0)  // Y Z X order
                    { 
                        i1 = 0; 
                        j1 = 1; 
                        k1 = 0; 
                        i2 = 0; 
                        j2 = 1; 
                        k2 = 1; 
                    } 
                    else  // Y X Z order
                    { 
                        i1 = 0; 
                        j1 = 1; 
                        k1 = 0; 
                        i2 = 1; 
                        j2 = 1; 
                        k2 = 0; 
                    } 
                }

                //--------------------------------------------------------------------------
                // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
                // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
                // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
                // c = 1/6.

                float x1 = x0 - i1 + G3;            // Offsets for second corner in (x,y,z) coords
                float y1 = y0 - j1 + G3;
                float z1 = z0 - k1 + G3;
                float x2 = x0 - i2 + 2.0f * G3;     // Offsets for third corner in (x,y,z) coords
                float y2 = y0 - j2 + 2.0f * G3; 
                float z2 = z0 - k2 + 2.0f * G3;
                float x3 = x0 - 1.0f + 3.0f * G3;   // Offsets for last corner in (x,y,z) coords
                float y3 = y0 - 1.0f + 3.0f * G3;
                float z3 = z0 - 1.0f + 3.0f * G3;

                // Work out the hashed gradient indices of the four simplex corners
                int ii = i & 255;
                int jj = j & 255;
                int kk = k & 255;
                int gi0 = perm[ii + perm[jj + perm[kk]]] % 12;
                int gi1 = perm[ii + i1 + perm[jj + j1 + perm[kk + k1]]] % 12;
                int gi2 = perm[ii + i2 + perm[jj + j2 + perm[kk + k2]]] % 12;
                int gi3 = perm[ii + 1 + perm[jj + 1 + perm[kk + 1]]] % 12;

                //--------------------------------------------------------------------------
                // Calculate the contribution from the four corners

                float t0 = 0.6f - (x0 * x0) - (y0 * y0) - (z0 * z0);

                if(t0 < 0.0f)
                {
                    n0 = 0.0f;
                }
                else 
                {
                    t0 *= t0;
                    n0  = t0 * t0 * dot(grad3[gi0], x0, y0, z0);
                }

                float t1 = 0.6f - (x1 * x1) - (y1 * y1) - (z1 * z1);

                if(t1 < 0.0f)
                {
                    n1 = 0.0f;
                }
                else 
                {
                    t1 *= t1;
                    n1  = t1 * t1 * dot(grad3[gi1], x1, y1, z1);
                }

                float t2 = 0.6f - (x2 * x2) - (y2 * y2) - (z2 * z2);

                if(t2 < 0.0f) 
                {
                    n2 = 0.0f;
                }
                else 
                {
                    t2 *= t2;
                    n2  = t2 * t2 * dot(grad3[gi2], x2, y2, z2);
                }

                float t3 = 0.6f - (x3 * x3) - (y3 * y3) - (z3 * z3);

                if(t3 < 0.0f) 
                {
                    n3 = 0.0f;
                }
                else 
                {
                    t3 *= t3;
                    n3  = t3 * t3 * dot(grad3[gi3], x3, y3, z3);
                }

                //--------------------------------------------------------------------------
                // Add contributions from each corner to get the final noise value.
                // The result is scaled to stay just inside [-1,1]

                return 32.0f * (n0 + n1 + n2 + n3);
            }

            //------------------------------------------------------------------------------
            // PRIVATE METHODS
            //------------------------------------------------------------------------------
        }
    }
}