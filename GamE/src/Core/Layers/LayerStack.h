#pragma once

#include "Layer.h"

namespace GE {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push_front(Layer* layer);
		void push_back(Layer* layer);

		void pop_front(Layer* layer);
		void pop_back(Layer* layer);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
	private:
		std::vector<Layer*>_layers;
		std::vector<Layer*>::iterator _mid_ptr;
	};

}