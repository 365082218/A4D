#pragma once
//������ƫ���ݵģ��ڲ���������������֯���ṹ.
class GameObject;
class Scene
{
private:
public:
	Scene(string name = "");
	~Scene();
	int m_nBuildIndex;
	bool m_bIsDirty;//�ڱ༭��Ϊ������ʱ.
	bool m_bIsLoaded;
	string path;
	string name;
	//void initOctree(int width, int height, int depth, int center, int level);
	int handle;
	void addChild(GameObject * gameObject);
	void removeChild(GameObject * gameObject);
	vector<GameObject *> rootGameObjects;
};

