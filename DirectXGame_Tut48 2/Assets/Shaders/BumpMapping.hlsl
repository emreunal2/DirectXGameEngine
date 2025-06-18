#include "Common.hlsl"

Texture2D NormalMap : register(t0);
sampler NormalSampler : register(s0);

VPS_INOUT vsmain(VS_INPUT input)
{
	VPS_INOUT output = (VPS_INOUT)0;

	output.position = mul(input.position, world);
	output.worldPosition = output.position.xyz;

	output.position = mul(output.position, camera.view);
	output.position = mul(output.position, camera.proj);

	output.texcoord = input.texcoord;

	// Transform normal to world space (still needed for TBN later)
	output.normal = normalize(mul(input.normal, (float3x3)world));

	return output;
}

float4 psmain(VPS_INOUT input) : SV_TARGET
{
	// Sample normal map
	float3 normalMap = NormalMap.Sample(NormalSampler, input.texcoord).rgb;
	normalMap = normalMap * 2.0f - 1.0f;

	// Approximate TBN (you can improve this later by passing tangent from mesh)
	float3 up = float3(0, 1, 0);
	float3 tangent = normalize(cross(up, input.normal));
	float3 bitangent = cross(input.normal, tangent);
	float3x3 TBN = float3x3(tangent, bitangent, input.normal);

	float3 bumpedNormal = normalize(mul(normalMap, TBN));

	// Use a fixed base color (light gray) instead of a texture
	float3 baseColor = float3(0.8, 0.8, 0.8);

	// Compute lighting with bumped normal
	float3 final_light = computePhongLighting(
		camera,
		light,
		input.worldPosition,
		bumpedNormal,

		4,
		baseColor * float3(0.09, 0.09, 0.09),

		0.7,
		baseColor,

		0.2,
		light.color.rgb,

		32.0);

	final_light = ComputeFogColor(fog, camera, input.worldPosition, final_light);

	return float4(final_light, 1.0);
}
