#include "Common.hlsl"

VPS_INOUT vsmain(VS_INPUT input)
{
	VPS_INOUT output = (VPS_INOUT)0;

	//WORLD SPACE
	output.position = mul(input.position, world);
	output.worldPosition = output.position.xyz;

	output.position = mul(output.position, camera.view);
	output.position = mul(output.position, camera.proj);
	output.texcoord = input.texcoord;
	output.normal = normalize(mul(input.normal, (float3x3)world));
	return output;
}

Texture2D Color : register(t0);
sampler ColorSampler : register(s0);

float4 psmain(VPS_INOUT input) : SV_TARGET
{
	// Sample texture as base color
	float4 color = Color.Sample(ColorSampler, input.texcoord);

// Simple Toon-like Phong Lighting
float3 light_direction = -normalize(light.direction.xyz);
float3 view_direction = normalize(camera.position.xyz - input.worldPosition);
float3 normal = normalize(input.normal);

// === Ambient ===
float3 ambient = 4 * (color.rgb * float3(0.09, 0.09, 0.09));

// === Diffuse - Quantized ===
float NdotL = max(dot(normal, light_direction), 0.0);
float levels = 5.0;
float quantizedDiffuse = floor(NdotL * levels) / levels;
float3 diffuse = 0.7 * color.rgb * quantizedDiffuse;

// === No specular for cleaner toon look (optional)
float3 final_light = ambient + diffuse;

// Apply fog
final_light = ComputeFogColor(fog, camera, input.worldPosition.xyz, final_light);

return float4(final_light, 1.0);
}