#pragma once
//场景是偏数据的，内部不含操作，仅组织树结构.
class GameObject;
class Scene
{
private:
public:
	Scene(string name = "");
	~Scene();
	int m_nBuildIndex;
	bool m_bIsDirty;//在编辑器为跑引擎时.
	bool m_bIsLoaded;
	string path;
	string name;
	//void initOctree(int width, int height, int depth, int center, int level);
	int handle;
	void addChild(GameObject * gameObject);
	void removeChild(GameObject * gameObject);
	vector<GameObject *> rootGameObjects;
};

