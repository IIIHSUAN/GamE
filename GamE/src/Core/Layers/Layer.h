#pragma once

#include "Core/Events/Event.h"

namespace GE {

	class Layer
	{
	public:
		Layer(const std::string& name = "Default Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(const float& delta_second = 0.0f) {}
		virtual void onEvent(Event& e) { COUT_GRE("[{0}] {1}", _layerName, e.toString()); }

		inline const std::string& getName() const { return _layerName; }
	private:
		std::string _layerName;
	};

}