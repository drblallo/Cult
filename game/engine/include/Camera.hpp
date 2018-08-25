#ifndef CAMERA_H
#define CAMERA_H

#include "Transform3D.hpp"

namespace engine
{
	class Camera
	{
		public:
		Camera(float width, float height, float fow = glm::pi<float>() / 2.0f);
		~Camera();
		Camera(const Camera& other);
		Camera(Camera&& other) noexcept;
		Camera& operator=(const Camera& other);
		// methods

		// setter and getters
		const Transform3D& getTransform() const { return transform; }
		const glm::mat4& getWorldToScreen() const;
		float getFow() const { return fow; }
		float getWidth() const { return width; }
		float getHeight() const { return height; }

		void setFow(float newFow)
		{
			fow		= newFow;
			dirty = true;
		}
		void setWidth(float newWidth)
		{
			width = newWidth;
			dirty = true;
		}

		void setHeight(float newHeight)
		{
			height = newHeight;
			dirty	= true;
		}

		private:
		// members
		Transform3D transform;
		float fow;
		mutable bool dirty;
		float width;
		float height;
		mutable glm::mat4 cachedWtS;

		// helpers
	};

}	// namespace engine
#endif /* CAMERA_H */
