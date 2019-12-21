#pragma once
class MeshGenerator
{
public:
	MeshGenerator();
	~MeshGenerator();
	static void CreateSphere(float radius);//圆球体
	static void CreateCapsule();//胶囊体=上半球+圆柱体+下半球
	static void CreateCylinder(Mesh ** ppMesh, float radiusTop, float radiusBottom, float height);//圆锥体
	static void CreateBox(Mesh ** ppMesh, float width, float height, float depth);//立方体
	void CreatePlane(Mesh ** ppMesh, float width, float height);//平面
};

