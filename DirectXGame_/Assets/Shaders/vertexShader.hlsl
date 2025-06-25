#include "Common.hlsl"

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float4 lighting : TEXCOORD1; // Use TEXCOORD, not COLOR
};

Texture2D Color : register(t0);
sampler ColorSampler : register(s0);

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    float4 worldPos = mul(input.position, world);
    float3 worldNormal = normalize(mul(input.normal, (float3x3)world));

    float3 baseColor = float3(1.0, 1.0, 1.0); // White, for lighting intensity

    float3 litColor = computePhongLighting(
        camera,
        light,
        worldPos.xyz,
        worldNormal,

        4,
        baseColor * float3(0.09, 0.09, 0.09), // ambient

        0.7,
        baseColor,                            // diffuse

        0.0,
        float3(1, 1, 1),                      // no specular

        10.0);

    output.lighting = float4(litColor, 1.0f);
    output.position = mul(worldPos, camera.view);
    output.position = mul(output.position, camera.proj);
    output.texcoord = input.texcoord;

    return output;
}

float4 psmain(VS_OUTPUT input) : SV_TARGET
{
    float4 texColor = Color.Sample(ColorSampler, input.texcoord);
    float3 finalColor = texColor.rgb * input.lighting.rgb;

    finalColor = ComputeFogColor(fog, camera, input.lighting.rgb, finalColor);

    return float4(finalColor, 1.0f);
}
