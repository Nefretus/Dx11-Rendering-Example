struct VSOut 
{
	float4 pos: SV_POSITION;
	float3 color: COLOR;
};

VSOut main( float2 pos : POSITION , float3 color: COLOR)
{
	VSOut vo;
	vo.pos = float4(pos.x, pos.y, 0.0f, 1.0f);
	vo.color = color;
	return vo;
}