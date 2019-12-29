#pragma once
#include "Component.h"
class Script :
	public Component
{
public:
	Script();
	~Script();
	void OnEnable(AEvent * context);
	void OnDisable(AEvent * context);//���disable
	void OnMeshChanged(AEvent * context);//meshrender�յ�meshfilter�ı���mesh
	void OnKeyDown(KeyEvent * context);
	void OnKeyUp(KeyEvent * context);
	void OnMouseDown(MouseEvent * context);
	void OnMouseUp(MouseEvent * context);
	void OnMouseMove(MouseEvent * context);
};

