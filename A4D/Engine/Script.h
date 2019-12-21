#pragma once
#include "Component.h"
class Script :
	public Component
{
public:
	Script();
	~Script();
	void OnEnable(Event * context);
	void OnDisable(Event * context);//���disable
	void OnMeshChanged(Event * context);//meshrender�յ�meshfilter�ı���mesh
	void OnKeyDown(KeyEvent * context);
	void OnKeyUp(KeyEvent * context);
	void OnMouseDown(MouseEvent * context);
	void OnMouseUp(MouseEvent * context);
	void OnMouseMove(MouseEvent * context);
};

