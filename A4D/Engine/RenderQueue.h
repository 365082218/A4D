#pragma once
class RenderElement;
class RenderState;

class RenderQueue
{
public:
	RenderQueue(Scene * scene);
	~RenderQueue();
	static int _uniqueIDCounter;
	int _id;
	/**@private */
	bool _needSort;
	/**@private */
	vector<RenderElement*> _renderElements;
	/**@private */
	vector<RenderElement*> _dynamicBatchCombineRenderElements;
	/**@private */
	vector<RenderElement*> _finalElements;
	/**@private */
	Scene * _scene;
	void _clearRenderElements();
	void _preRender(RenderState * rs);
	void _addRenderElement(RenderElement * element);
	void _render(RenderState * rs, bool yes);
};

