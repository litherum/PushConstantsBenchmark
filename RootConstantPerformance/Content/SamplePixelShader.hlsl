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
float4 main() : SV_TARGET
{
	return float4(i0 + i1, i2 + i3, i4 + i5, i6 + i7 + 1.0f);
}
