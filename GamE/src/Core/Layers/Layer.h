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
		virtual void onUpdate() {}
		virtual void onEvent(Event& e) {}

		inline const std::string& getName() const { return _layerName; }
	private:
		std::string _layerName;
	};

}