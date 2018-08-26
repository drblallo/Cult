#ifndef TEXTFILEDATABASE_H
#define TEXTFILEDATABASE_H

#include <string>
#include <unordered_map>

namespace engine
{
	class TextFileDatabase
	{
		public:
		TextFileDatabase();
		~TextFileDatabase();
		TextFileDatabase(const TextFileDatabase& other);
		TextFileDatabase(TextFileDatabase&& other) noexcept;
		TextFileDatabase& operator=(const TextFileDatabase& other);
		// methods
		const std::string& get(const std::string& fileName);

		// setter and getters

		private:
		// members
		std::unordered_map<std::string, std::string> data;

		// helpers
	};

}	// namespace engine
#endif /* TEXTFILEDATABASE_H */
