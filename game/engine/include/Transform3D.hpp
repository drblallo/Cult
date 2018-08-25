//
// Created by massimo on 03/08/18.
//

#ifndef CULT_TRANSFORM3D_HPP
#define CULT_TRANSFORM3D_HPP
#define GLM_FORCE_RADIANS
#include <functional>
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace utils
{
	template<typename T>
	class TreeItem;
}
namespace engine
{
	class Transform3D
	{
		public:
		Transform3D();
		Transform3D(std::function<Transform3D*()> parent);

		inline void setTranslation(const glm::vec3& newTranslation)
		{
			markDirty();
			translation = newTranslation;
		}
		inline void setRotation(const glm::quat& newRotation)
		{
			markDirty();
			rotation = newRotation;
		}
		inline void setScale(const glm::vec3& newScale)
		{
			markDirty();
			scaling = newScale;
		}

		inline void setTranslation(float x, float y = 0, float z = 0)
		{
			setTranslation(glm::vec3(x, y, z));
		}
		inline void setRotation(float x, float y = 0, float z = 0)
		{
			setRotation(glm::vec3(x, y, z));
		}
		inline void setScale(float x, float y = 0, float z = 0)
		{
			setScale(glm::vec3(x, y, z));
		}

		inline void translate(const glm::vec3& newTranslation)
		{
			markDirty();
			translation += newTranslation;
		}
		inline void rotate(const glm::vec3& newRotation)
		{
			markDirty();
			rotation = glm::quat(glm::eulerAngles(rotation) + newRotation);
		}
		inline void scale(const glm::vec3& newScale)
		{
			markDirty();
			scaling += newScale;
		}

		inline void translate(float x, float y = 0.0f, float z = 0.0f)
		{
			translate(glm::vec3(x, y, z));
		}

		inline void rotate(float x, float y = 0.0f, float z = 0.0f)
		{
			rotate(glm::vec3(x, y, z));
		}

		inline void scale(float x, float y = 0.0f, float z = 0.0f)
		{
			scale(glm::vec3(x, y, z));
		}

		inline const glm::vec3& getTranslation() const { return translation; }
		inline const glm::vec3& getScale() const { return scaling; }
		inline glm::vec3 getRotation() const { return glm::eulerAngles(rotation); }
		const glm::mat4& getProjection() const;
		const glm::mat4& getInvertedProjection() const;

		void setParentGetter(const std::function<Transform3D*()>& getter)
		{
			parentGetter = getter;
			markDirty();
		}

		void setParentGetter(std::function<Transform3D*()>&& getter)
		{
			setParentGetter(getter);
		}

		private:
		void markDirty()
		{
			projectionDirty					= true;
			invertedProjectionDirty = true;
		}

		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 scaling;
		mutable glm::mat4 cachedProjection;
		mutable bool projectionDirty;
		mutable glm::mat4 cachedInvertedProjection;
		mutable bool invertedProjectionDirty;

		std::function<Transform3D*()> parentGetter;
	};
}	// namespace engine

#endif	// CULT_TRANSFORM3D_HPP
