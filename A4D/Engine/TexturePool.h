#pragma once
class TextureInfo
{
public:
	IDirect3DTexture9 * pTex;
	int referenceNum;
	D3DXIMAGE_INFO texInfo;
};

class TexturePool
{
public:
	TexturePool();
	~TexturePool();
	bool getItem(string tex, IDirect3DTexture9 ** pTex, D3DXIMAGE_INFO ** pInfo = NULL);
	void recover(IDirect3DTexture9 * pTex);
	map<string, TextureInfo*> pool;
};

