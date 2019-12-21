#pragma once
/*
×µ½ØÌå²Ã¼ô
*/
class FrustumCulling
{
public:
	FrustumCulling();
	~FrustumCulling();
	static void renderObjectCullingNoBoundFrustum(Scene * scene, Camera * camera, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView);
};

