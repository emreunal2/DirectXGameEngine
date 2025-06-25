#include "Common.hlsl"

Texture2D HeightMap : register(t0);
sampler HeightMapSampler : register(s0);

VPS_INOUT vsmain(VS_INPUT input)
{
	VPS_INOUT output = (VPS_INOUT)0;

	// Sample the heightmap
	float height = HeightMap.SampleLevel(HeightMapSampler, input.texcoord, 0).r;

	// Scale the displacement amount
	float displacementStrength = 0.03f;

	// Displace vertex along its normal
	float3 displacedPos = input.position.xyz + input.normal * (height * displacementStrength);

	float4 worldPos = mul(float4(displacedPos, 1.0f), world);

	output.position = mul(worldPos, camera.view);
	output.position = mul(output.position, camera.proj);

	output.worldPosition = worldPos.xyz;
	output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float3x3)world));

	return output;
}

float4 psmain(VPS_INOUT input) : SV_TARGET
{
	// Use a fixed color (or sample a texture if you want)
	float3 color = float3(0.7, 0.7, 0.7);

// Apply lighting
float3 lightColor = computePhongLighting(
	camera,
	light,
	input.worldPosition,
	input.normal,

	4,
	color * 0.09,

	0.7,
	color,

	0.1,
	light.color.rgb,

	16.0);

lightColor = ComputeFogColor(fog, camera, input.worldPosition, lightColor);

return float4(lightColor, 1.0);
}