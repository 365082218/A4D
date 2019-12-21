#pragma once
class SceneManager
{
	static SceneManager * _Instance;
public:
	static SceneManager * Instance()
	{
		if (SceneManager::_Instance == NULL)
			SceneManager::_Instance = new SceneManager();
		return SceneManager::_Instance;
	}
	SceneManager();
	~SceneManager();
public: 
	static int sceneCount;
	static int sceneCountInBuildSettings;
	static Scene * CreateScene(string sceneName)
	{
		return new Scene(sceneName);
	}
	static Scene * pActiveScene;
	static Scene * GetActiveScene()
	{
		return pActiveScene;
	}

	static void SetActiveScene(Scene * scene)
	{
		SceneManager::pActiveScene = scene;
	}

	static list<Scene*> * GetAllScene()
	{
		return NULL;
	}
	static Scene * GetSceneAt(int index)
	{
		return NULL;
	}
	static Scene * GetSceneByBuildIndex(int buildIndex)
	{
		return NULL;
	}
	static Scene * GetSceneByName(string name)
	{
		return NULL;
	}
	static Scene * GetSceneByPath(string scenePath)
	{
		return NULL;
	}
	static void LoadScene(string sceneName)
	{
		//加载一个场景.
	}
	static void LoadScene(int sceneBuildIndex)
	{

	}
	static void LoadScene(string sceneName, int loadMode)
	{

	}
	static void LoadScene(int sceneBuildIndex, int loadMode)
	{

	}
	static void UnloadScene(string sceneName)
	{

	}
	static void UnloadScene(Scene * scene)
	{

	}
	static void UnloadScene(int sceneBuildIndex)
	{

	}
	/*static AsyncOperation * LoadSceneAsync(string sceneName);
	static AsyncOperation * LoadSceneAsync(int sceneBuildIndex);
	static AsyncOperation * LoadSceneAsync(int sceneBuildIndex, int loadMode);
	static AsyncOperation * LoadSceneAsync(string sceneName, int loadMode);
	static AsyncOperation * UnloadSceneAsync(string sceneName);
	static AsyncOperation * UnloadSceneAsync(int sceneBuildIndex);*/

};