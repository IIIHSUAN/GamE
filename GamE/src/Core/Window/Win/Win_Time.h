#pragma once

#include "../Time.h"

namespace GE {

	class Win_Time: public Time
	{
	private:
		virtual inline float getSeconds_impl() final override;
	};

}