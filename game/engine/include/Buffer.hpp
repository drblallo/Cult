#ifndef BUFFER_H
#define BUFFER_H
#include <cassert>
#include <vector>

#include "glad/glad.h"

namespace engine
{
	template<typename T>
	class Buffer
	{
		public:
		Buffer(): dirty(true), bufferID(0), data() { createBuffer(); }

		Buffer(const std::vector<T>& vector): dirty(true), bufferID(0), data(vector)
		{
			createBuffer();
		}

		Buffer(std::vector<T>&& vector)
				: dirty(true), bufferID(0), data(std::move(vector))
		{
			createBuffer();
		}

		~Buffer()
		{
			if (bufferID)
				glDeleteBuffers(1, &bufferID);
		}

		Buffer(const Buffer& other): dirty(true), bufferID(0), data(other.data)
		{
			createBuffer();
		}

		Buffer(Buffer&& other) noexcept
				: dirty(other.dirty),
					bufferID(other.bufferID),
					data(std::move(other.data))
		{
			other.bufferID = 0;
		}

		Buffer& operator=(const Buffer& other)
		{
			data = other.data;
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
			dirty = true;
			return *this;
		}

		// methods

		// setter and getters
		const std::vector<T>& getData() const { return data; }
		inline void set(T newVal, unsigned index)
		{
			dirty = true;
			data[index] = newVal;
		}

		inline void directSet(T newVal, unsigned index)
		{
			data[index] = newVal;
			glBufferSubData(bufferID, index, sizeof(T), &newVal);
		}

		private:
		// members
		mutable bool dirty;
		GLuint bufferID;
		std::vector<T> data;

		// helpers
		void createBuffer()
		{
			assert(bufferID == 0);
			glGenBuffers(1, &bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, bufferID);
		}

		void load() const
		{
			assert(bufferID != 0);
			dirty = false;
			glBufferData(bufferID, sizeof(T), data[0], GL_DYNAMIC_DRAW);
		}
	};

}	// namespace engine
#endif /* BUFFER_H */
