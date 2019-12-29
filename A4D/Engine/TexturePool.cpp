#include "stdafx.h"
#include "TexturePool.h"
#include "../A4D.h"
#include "W4DCommon.h"
#include "Node.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "global.h"
#include "WGraphics.h"
#include "TexturePool.h"
#include "GameWorld.h"
#include "Console.h"
#include "WInputModel.h"
#include "MouseMgr.h"
#include "Pool.h"
#include "Time.h"
TexturePool::TexturePool()
{
}


TexturePool::~TexturePool()
{
}


bool TexturePool::getItem(string tex, IDirect3DTexture9 ** pTex, D3DXIMAGE_INFO ** pInfo)
{
	map<string, TextureInfo*>::iterator it = pool.find(tex);
	if (it != pool.end())
	{
		if (pTex != NULL)
			*pTex = it->second->pTex;
		if (pInfo != NULL)
			*pInfo = &it->second->texInfo;
		it->second->referenceNum += 1;
		return true;
	}

	TextureInfo * texInfo = new TextureInfo();
	texInfo->referenceNum = 1;

	HRESULT hr = D3DXCreateTextureFromFileExA(A4D::getInstance()->Graphics()->pEditorDevice, tex.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE,
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0, 0, 0, 255),
		&texInfo->texInfo,
		NULL,
		&texInfo->pTex);
	if (FAILED(hr))
		return false;
	*pTex = texInfo->pTex;
	if (pInfo != NULL)
		*pInfo = &texInfo->texInfo;
	pool[tex] = texInfo;
	return true;
}

void TexturePool::recover(IDirect3DTexture9 * pTex)
{
	
}
