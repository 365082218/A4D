#pragma once
class MaterialUnit
{
public:
	MaterialUnit();
	~MaterialUnit();
	string Texture;
	D3DCOLOR ColorKey;
	D3DCOLOR Ambient;
	D3DCOLOR Diffuse;
	D3DCOLOR Specular;
	D3DCOLOR Emissive;
	float Opacity;
	string Option;
	bool TwoSide;
};

