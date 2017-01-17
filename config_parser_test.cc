#include "gtest/gtest.h"
#include "config_parser.h"

class NSCP_Fixture_Test : public ::testing::Test {
protected:
 	bool ParseString(const std::string config_string) {
 		std::stringstream config_stream(config_string);
 		return parser_.Parse(&config_stream, &out_config_);
 	}
 	NginxConfigParser parser_;
 	NginxConfig out_config_;
 };

TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

TEST_F(NSCP_Fixture_Test, MissingEndBracket) {
	std::string test_string = "server { listen   80; ";
	EXPECT_FALSE(ParseString(test_string));
}

TEST_F(NSCP_Fixture_Test, MissingEndQuote) {
	EXPECT_FALSE(ParseString("foo \"bar;"));
}

TEST_F(NSCP_Fixture_Test, EmptyStatement) {
	EXPECT_TRUE(ParseString(";"));
}