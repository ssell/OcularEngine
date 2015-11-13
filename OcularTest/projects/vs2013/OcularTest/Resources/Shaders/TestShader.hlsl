// Quick test HLSL shader

struct VSIn
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

struct VSOut
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

VSOut VSMain(VSIn input)
{
    VSOut result;
    result.Position = input.Position;
    result.Color = input.Color;

    return result;
}

float4 PSMain(VSOut input) : COLOR0
{
    return input.Color;
}