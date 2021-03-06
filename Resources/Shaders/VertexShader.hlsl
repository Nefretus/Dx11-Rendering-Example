struct VSOut 
{
	float4 pos: SV_POSITION;
	float3 color: COLOR;
};

cbuffer cBuff {
	 matrix rotation;
};

VSOut main( float2 pos : POSITION , float3 color: COLOR)
{
	VSOut vo;
	vo.pos = mul(float4(pos.x, pos.y, 0.0f, 1.0f), rotation);
	vo.color = color;
	clamp(1, 2, 3);
	return vo;
}