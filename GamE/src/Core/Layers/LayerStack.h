#pragma once

#include "Layer.h"

namespace GE {

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void insert_front(Layer* layer);
		void insert_back(Layer* layer);

		void pop_front(Layer* layer);
		void pop_back(Layer* layer);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
	private:
		std::vector<Layer*>_layers;
		int _layers_midInd = 0;
	};

}