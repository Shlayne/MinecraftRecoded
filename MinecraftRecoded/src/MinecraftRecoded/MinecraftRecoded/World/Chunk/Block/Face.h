#pragma once

#include <Engine/Core/Int.h>

namespace mcr
{
	using Face_ = uint8;
	enum Face : Face_
	{
		Face_Bottom,
		Face_Top,
		Face_North,
		Face_South,
		Face_West,
		Face_East,

		Face_Count,
		Face_First = Face_Bottom
	};
}
