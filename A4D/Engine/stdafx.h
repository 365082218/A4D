// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <list>
#include <vector>
#include <map>

#include <d3d9.h>
#include <d3dx9tex.h>
#include "Console.h"
#include "DirectoryWatcher.h"
#include "node.h"
#include "Scene.h"
#include "WInputModel.h"
#include "WGraphics.h"
#include "W4DCommon.h"
#include "../A4D.h"
#include "Mesh.h"
#include "global.h"
#include "Transform.h"
#include "Camera.h"
#include "resource.h"
#include "MeshGenerator.h"
#include "GameObject.h"
#include "object.h"
#include "Time.h"
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
// TODO: 在此处引用程序需要的其他头文件
#include "MouseMgr.h"