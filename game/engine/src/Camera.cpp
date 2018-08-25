#include "Camera.hpp"

namespace engine
{
	Camera::Camera(float sWidth, float sHeight, float sFow)
			: transform(), fow(sFow), dirty(true), width(sWidth), height(sHeight)
	{
	}
	Camera::~Camera() {}
	Camera::Camera(const Camera& other)
			: transform(other.transform),
				fow(other.fow),
				dirty(other.dirty),
				width(other.width),
				height(other.height),
				cachedWtS(other.cachedWtS)
	{
	}
	Camera::Camera(Camera&& other) noexcept
			: transform(other.transform),
				fow(other.fow),
				dirty(other.dirty),
				width(other.width),
				height(other.height),
				cachedWtS(other.cachedWtS)
	{
	}
	Camera& Camera::operator=(const Camera& other)
	{
		transform = other.transform;
		fow				= other.fow;
		dirty			= other.dirty;
		width			= other.width;
		height		= other.height;
		cachedWtS = other.cachedWtS;
		return *this;
	}

	const glm::mat4& Camera::getWorldToScreen() const
	{
		if (dirty)
		{
			cachedWtS = glm::perspectiveFov(fow, width, height, 0.1f, 100.0f);
			dirty			= false;
		}
		return cachedWtS;
	}

}	// namespace engine
