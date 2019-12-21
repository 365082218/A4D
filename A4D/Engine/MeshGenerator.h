#pragma once
class MeshGenerator
{
public:
	MeshGenerator();
	~MeshGenerator();
	static void CreateSphere(float radius);//Բ����
	static void CreateCapsule();//������=�ϰ���+Բ����+�°���
	static void CreateCylinder(Mesh ** ppMesh, float radiusTop, float radiusBottom, float height);//Բ׶��
	static void CreateBox(Mesh ** ppMesh, float width, float height, float depth);//������
	void CreatePlane(Mesh ** ppMesh, float width, float height);//ƽ��
};

