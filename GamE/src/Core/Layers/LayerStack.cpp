#include "pch.h"
#include "LayerStack.h"

namespace GE {

	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		// new outside
		for (Layer* layer : _layers)
			delete layer;
	}

	void LayerStack::insert_front(Layer * layer)
	{
		_layers.emplace(_layers.begin()+ (_layers_midInd++), layer);
	}
	void LayerStack::insert_back(Layer * layer)
	{
		_layers.emplace_back(layer);
	}

	void LayerStack::pop_front(Layer * layer)
	{
		auto it = std::find(_layers.begin(), _layers.end(), layer);

		if (it != _layers.end())
			_layers.erase(it), _layers_midInd--;
	}
	void LayerStack::pop_back(Layer * layer)
	{
		auto it = std::find(_layers.begin(), _layers.end(), layer);

		if (it != _layers.end())
			_layers.erase(it);
	}

}