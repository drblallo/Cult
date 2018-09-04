#ifndef SHADERPROGRAMDATABASE_H
#define SHADERPROGRAMDATABASE_H

#include <memory>
#include <string>
#include <unordered_map>

#include "TextFileDatabase.hpp"

namespace engine
{
	class Program;
	class ShaderProgramDatabase
	{
		public:
		ShaderProgramDatabase();
		~ShaderProgramDatabase();
		ShaderProgramDatabase(const ShaderProgramDatabase& other) = delete;
		ShaderProgramDatabase(ShaderProgramDatabase&& other) noexcept;
		ShaderProgramDatabase& operator=(const ShaderProgramDatabase& other) =
				delete;
		// methods
		std::shared_ptr<Program> get(
				const std::string& vShaderName, const std::string& fShaderName);

		private:
		// members
		std::unordered_map<std::string, std::shared_ptr<Program>> data;
		TextFileDatabase database;

		// helpers
	};

}	// namespace engine
#endif /* SHADERPROGRAMDATABASE_H */
