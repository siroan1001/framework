struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float3 RGB2HSV(float r, float g, float b);
float3 HSV2RGB(float h, float s, float v);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	float2 dotScreenSize = float2(16.0f, 9.0f);
	float rate = 10.0f;
	dotScreenSize *= rate;
	float2 i_uv = pin.uv * dotScreenSize;
	i_uv = floor(i_uv);	//¬”‚ÌØ‚èŽÌ‚Ä

	i_uv /= dotScreenSize;

	color = tex.Sample(samp, i_uv);

#if 0
	int gradation = 8;
	color.rgb *= gradation;
	color.rgb = floor(color.rgb);
	color.rgb /= gradation;
#else
	float3 hsv = RGB2HSV(color.r, color.g, color.b);
	float3 tone = float3(16.0f, 8.0f, 4.0f);
	hsv *= tone;
	hsv += 0.5f;
	hsv.x = floor(hsv.x);
	hsv.x /= 8;
	color.rgb = HSV2RGB(hsv.x, hsv.y, hsv.z);
#endif
	return color;
}

float3 RGB2HSV(float r, float g, float b)
{
	float max = r > g ? r : g;
	max = max > b ? max : b;
	float min = r < g ? r : b;
	min = min > b ? min : b;

	float h = max - min;
	if (h > 0.0f)
	{
		if (max == r)
		{
			h = (g - b) / h;
			if (h < 6.0f)
			{
				h += 6.0f;
			}
		}
		else if (max == g)
		{
			h = 2.0f + (b - r) / h;
		}
		else if (max == b)
		{
			h = 4.0f + (r - g) / h;
		}
	}
	h /= 6.0f;
	float s = (max - min);
	if (max != 0.0f)
	{
		s /= max;
	}
	float v = max;

	return float3(h, s, v);
}
float3 HSV2RGB(float h, float s, float v)
{
	float r = v;
	float g = v;
	float b = v;
	if (s > 0.0f) {
		h *= 6.0f;
		int i = (int)h;
		float f = h - (float)i;
		switch (i) {
		default:
		case 0:
			g *= 1 - s * (1 - f);
			b *= 1 - s;
			break;
		case 1:
			r *= 1 - s * f;
			b *= 1 - s;
			break;
		case 2:
			r *= 1 - s;
			b *= 1 - s * (1 - f);
			break;
		case 3:
			r *= 1 - s;
			g *= 1 - s * f;
			break;
		case 4:
			r *= 1 - s * (1 - f);
			g *= 1 - s;
			break;
		case 5:
			g *= 1 - s;
			b *= 1 - s * f;
			break;
		}
	}

	return float3(r, g, b);
}