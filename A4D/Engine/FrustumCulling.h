#pragma once
/*
×µ½ØÌå²Ã¼ô
*/
class WGraphics;
class Camera;
class FrustumCulling
{
public:
	FrustumCulling();
	~FrustumCulling();
	static void renderObjectCullingNoBoundFrustum(WGraphics * graphic, Camera * camera, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView);
};

