/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2023, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

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

Texture2D Color: register(t0);
sampler ColorSampler: register(s0);

float4 psmain(VPS_INOUT input) : SV_TARGET
{
	float g = 0.3 + abs(sin(time));

	float4 color = float4(1.0, 0.0, 0.0, 1.0);

	float3 final_light = computePhongLighting(
		camera,
		light,
		input.worldPosition.xyz,
		input.normal.xyz,

		4,
		color.rgb * float3(0.09, 0.09, 0.09),

		0.7,
		color.rgb,

		0.0,
		float3(1, 1, 1),

		10.0);

	final_light = ComputeFogColor(fog, camera, input.worldPosition.xyz, final_light);

	return float4(final_light, 1.0);
}