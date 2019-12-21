#include "stdafx.h"
#include "Scene.h"
#include "SceneManager.h"
int SceneManager::sceneCount = 0;
int SceneManager::sceneCountInBuildSettings = 0;
SceneManager * SceneManager::_Instance = NULL;
Scene * SceneManager::pActiveScene = NULL;
SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}