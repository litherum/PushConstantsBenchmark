// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

cbuffer Constants : register(b0, space0)
{
	float i0;
	float i1;
	float i2;
	float i3;
	float i4;
	float i5;
	float i6;
	float i7;
};

// A pass-through function for the (interpolated) color data.
float4 main(PixelShaderInput input, uint primitiveID : SV_PrimitiveID) : SV_TARGET
{
	float result = 0;
	for (int i = 0; i < 100000; ++i) {
		result += i0;
		result += i1;
		result += i2;
		result += i3;
		result += i4;
		result += i5;
		result += i6;
		result += i7;
	}
	return float4(result, result, result, 1.0f);
}
