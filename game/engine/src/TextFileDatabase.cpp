#include "TextFileDatabase.hpp"

#include <fstream>

#include "g3log/g3log.hpp"

namespace engine
{
	TextFileDatabase::TextFileDatabase(): data() {}

	TextFileDatabase::~TextFileDatabase() {}

	TextFileDatabase::TextFileDatabase(const TextFileDatabase& other)
			: data(other.data)
	{
	}

	TextFileDatabase::TextFileDatabase(TextFileDatabase&& other) noexcept
			: data(std::move(other.data))
	{
	}

	TextFileDatabase& TextFileDatabase::operator=(const TextFileDatabase& other)
	{
		data = other.data;
		return *this;
	}

	const std::string& TextFileDatabase::get(const std::string& fileName)
	{
		if (data.find(fileName) != data.end())
			return data[fileName];

		std::ifstream ifs(fileName);

		if (!ifs.is_open() || !ifs.good())
		{
			LOG(WARNING) << "Could not open file " << fileName;
			throw std::invalid_argument("Could not open file " + fileName);
		}

		LOG(DEBUG) << "Loaded file " << fileName;
		data.insert(std::pair<std::string, std::string>(
				fileName,
				std::string(
						(std::istreambuf_iterator<char>(ifs)),
						(std::istreambuf_iterator<char>()))));

		return data[fileName];
	}

}	// namespace engine
