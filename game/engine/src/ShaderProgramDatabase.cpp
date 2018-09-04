#include "ShaderProgramDatabase.hpp"

#include "Program.hpp"
#include "g3log/g3log.hpp"

namespace engine
{
	ShaderProgramDatabase::ShaderProgramDatabase(): data(), database() {}

	ShaderProgramDatabase::~ShaderProgramDatabase() {}

	ShaderProgramDatabase::ShaderProgramDatabase(
			ShaderProgramDatabase&& other) noexcept
			: data(std::move(other.data)), database(std::move(other.database))
	{
	}

	std::shared_ptr<Program> ShaderProgramDatabase::get(
			const std::string& vShaderName, const std::string& fShaderName)
	{
		std::string key = vShaderName + fShaderName;
		if (data.find(key) != data.end())
			return data[key];

		const std::string& vertex(database.get(vShaderName));
		const std::string& fragment(database.get(fShaderName));

		Shader vertexShader(vertex, GL_VERTEX_SHADER);
		if (!vertexShader.good())
		{
			LOG(WARNING) << "Could not create shader " << vShaderName;
			throw std::invalid_argument("Could not create shader " + vShaderName);
		}

		Shader fragmentShader(fragment, GL_FRAGMENT_SHADER);
		if (!fragmentShader.good())
		{
			LOG(WARNING) << "Could not create shader " << fShaderName;
			throw std::invalid_argument("Could not create shader " + fShaderName);
		}

		auto p = std::make_shared<Program>(vertexShader, fragmentShader);

		if (!p->good())
		{
			LOG(WARNING) << "Could not link " << fShaderName << " and "
									 << vShaderName;
			throw std::invalid_argument("Could not link program");
		}

		data.insert(std::pair<std::string, std::shared_ptr<Program>>(key, p));
		return p;
	}

}	// namespace engine
