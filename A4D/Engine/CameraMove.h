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
	void OnEnable(AEvent * context);
	void OnDisable(AEvent * context);//���disable
	size_t type_id()
	{
		return typeid(CameraMove).hash_code();
	}
	float intensity;//�ƶ�ǿ��.
};

