
#include "RenderData.hpp"

namespace engine
{
	RenderData::RenderData(std::shared_ptr<Program> p): transform(), program(p) {}

	RenderData::~RenderData() {}

	RenderData::RenderData(const RenderData& other)
			: transform(other.transform), program(other.program)
	{
	}

	RenderData::RenderData(RenderData&& other) noexcept
			: transform(other.transform), program(std::move(other.program))
	{
	}

	RenderData::operator=(const RenderData other)
	{
		transform = other.transform;
		program		= other.program;
		return *this;
	}

}	// namespace engine
