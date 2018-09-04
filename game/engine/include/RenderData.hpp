#ifndef RENDERDATA_H
#define RENDERDATA_H

namespace engine
{
	class RenderData
	{
		public:
		RenderData(std::shared_ptr<Program> p);
		~RenderData();
		RenderData(const RenderData& other);
		RenderData(RenderData&& other) noexcept;
		RenderData& operator=(const RenderData& other);
		// methods

		// setter and getters

		private:
		// members
		Transform3D transform;
		std::shared_ptr<Program> program;

		// helpers
	};

}	// namespace engine
#endif /* RENDERDATA_H */
