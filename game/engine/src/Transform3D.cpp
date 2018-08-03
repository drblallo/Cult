//
// Created by massimo on 03/08/18.
//

#include "Transform3D.hpp"

namespace GEngine
{
	Transform3D::Transform3D()
			: translation(),
				rotation(),
				scaling(1),
				projectionDirty(true),
				invertedProjectionDirty(true)
	{
	}

	glm::mat4 Transform3D::getProjection()
	{
		if (projectionDirty)
		{
			cachedProjection = glm::translate(glm::mat4(1), translation);
			cachedProjection = glm::scale(cachedProjection, scaling);
			cachedProjection *= glm::mat4_cast(rotation);
			projectionDirty = false;
		}
		return cachedProjection;
	}

	glm::mat4 Transform3D::getInvertedProjection()
	{
		if (invertedProjectionDirty)
		{
			cachedInvertedProjection = glm::inverse(getProjection());
			invertedProjectionDirty	= false;
		}
		return cachedInvertedProjection;
	}
}	// namespace GEngine