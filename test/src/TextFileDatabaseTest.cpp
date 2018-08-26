#include "gtest/gtest.h"
#include <memory>

#include "SoutSink.hpp"
#include "TextFileDatabase.hpp"

class TextFileDatabaseTest: public testing::Test
{
	public:
	virtual void SetUp()
	{
		utils::initLogger(false);
		database.reset(new engine::TextFileDatabase());
	}
	virtual void TearDown() {}
	std::unique_ptr<engine::TextFileDatabase> database;
};

TEST_F(TextFileDatabaseTest, notExistingFileCauseException)
{
	EXPECT_THROW(database->get("adsa"), std::invalid_argument);
}

TEST_F(TextFileDatabaseTest, exstingFilCanBeRead)
{
	EXPECT_EQ(database->get("./resources/test/example.txt"), "hereItIs\n");
}
