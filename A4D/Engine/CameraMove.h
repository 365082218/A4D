#pragma once
#include "Script.h"
class CameraMove :
	public Script
{
public:
	CameraMove();
	~CameraMove();
	void Update();
	void OnKeyDown(KeyEvent * context);
	void OnKeyUp(KeyEvent * context);
	void OnMouseDown(MouseEvent * context);
	void OnMouseUp(MouseEvent * context);
	void OnEnable(Event * context);
	void OnDisable(Event * context);//组件disable
	size_t type_id()
	{
		return typeid(CameraMove).hash_code();
	}
	float intensity;//移动强度.
};

