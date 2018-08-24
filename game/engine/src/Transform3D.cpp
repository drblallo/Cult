//
// Created by massimo on 03/08/18.
//

#include "Transform3D.hpp"

#include <algorithm>

namespace engine
{
	Transform3D::Transform3D()
			: translation(),
				rotation(),
				scaling(1),
				cachedProjection(1),
				projectionDirty(false),
				cachedInvertedProjection(1),
				invertedProjectionDirty(false)
	{
	}

	Transform3D::Transform3D(std::function<Transform3D*()> parent)
			: translation(),
				rotation(),
				scaling(1),
				cachedProjection(1),
				projectionDirty(false),
				cachedInvertedProjection(1),
				invertedProjectionDirty(false),
				parentGetter(parent)

	{
	}
	const glm::mat4& Transform3D::getProjection() const
	{
		if (projectionDirty)
		{
			cachedProjection = glm::translate(glm::mat4(1), translation);
			cachedProjection = glm::scale(cachedProjection, scaling);
			cachedProjection *= glm::mat4_cast(rotation);

			if (parentGetter && parentGetter())
				cachedProjection = parentGetter()->getProjection() * cachedProjection;

			projectionDirty = false;
		}
		return cachedProjection;
	}

	const glm::mat4& Transform3D::getInvertedProjection() const
	{
		if (invertedProjectionDirty)
		{
			cachedInvertedProjection = glm::inverse(getProjection());
			invertedProjectionDirty	= false;
		}
		return cachedInvertedProjection;
	}
}	// namespace engine
