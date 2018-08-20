//
// Created by massimo on 03/08/18.
//

#ifndef CULT_TRANSFORM3D_HPP
#define CULT_TRANSFORM3D_HPP
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace engine
{
	class Transform3D
	{
		public:
		Transform3D();

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
		glm::mat4 getProjection();
		glm::mat4 getInvertedProjection();

		private:
		void markDirty()
		{
			projectionDirty					= true;
			invertedProjectionDirty = true;
		}

		glm::vec3 translation;
		glm::quat rotation;
		glm::vec3 scaling;
		glm::mat4 cachedProjection;
		bool projectionDirty;
		glm::mat4 cachedInvertedProjection;
		bool invertedProjectionDirty;
	};
}	// namespace engine

#endif	// CULT_TRANSFORM3D_HPP
