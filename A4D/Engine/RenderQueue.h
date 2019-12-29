#pragma once
class RenderElement;
class RenderState;

class RenderQueue
{
public:
	RenderQueue();
	~RenderQueue();
	static int _uniqueIDCounter;
	int _id;
	bool _needSort;
	vector<RenderElement*> _renderElements;
	vector<RenderElement*> _dynamicBatchCombineRenderElements;
	vector<RenderElement*> _finalElements;
	void _clearRenderElements();
	void _preRender(RenderState * rs);
	void _addRenderElement(RenderElement * element);
	void _render(RenderState * rs, bool yes);
};

