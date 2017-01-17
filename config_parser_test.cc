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

TEST_F(NSCP_Fixture_Test, ServerName) {
	EXPECT_TRUE(ParseString("server_name foo.com;"));
	EXPECT_EQ("server_name", out_config_.statements_.at(0)->tokens_.at(0));
	EXPECT_EQ("foo.com", out_config_.statements_.at(0)->tokens_.at(1));
}

TEST_F(NSCP_Fixture_Test, ListenTime) {
	EXPECT_TRUE(ParseString("listen 80;"));
	EXPECT_EQ("80", out_config_.statements_.at(0)->tokens_.at(1));
}