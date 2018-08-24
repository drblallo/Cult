#ifndef CULT_RENDERO_OBJECT_HANDLE
#define CULT_RENDERO_OBJECT_HANDLE
#include <memory>

namespace utils
{
	template<typename T>
	class TreeItem;

}
namespace engine
{
	class RenderObject;
	class RenderObjectHandle
	{
		friend class Renderer;

		public:
		RenderObjectHandle(utils::TreeItem<std::unique_ptr<RenderObject>>* o)
				: ogg(o)
		{
		}
		RenderObject* get() const;
		int getChildCount() const;
		RenderObjectHandle getChild(int child) const;
		void setParent(RenderObjectHandle handle);

		private:
		utils::TreeItem<std::unique_ptr<RenderObject>>* getItem() const;
		utils::TreeItem<std::unique_ptr<RenderObject>>* ogg;
	};
}	// namespace engine

#endif /* ifndef CULT_RENDERO_OBJECT_HANDLE                                      \
																																							 \ \
 */
