#include "commandLine.h"

#include "exception_d.h"
#include "gmock/gmock.h"

class CommandLineTest : public ::testing::Test {
public:
  CommandLine commandLine;
 };

TEST_F(CommandLineTest, throwExceptionIfInvalidCommandLine) {
  const char *cmdLine[] {"clrinvert"};
  ASSERT_THROW(commandLine.parse(sizeof(cmdLine)/sizeof(char*), cmdLine), bad_format_cmdline);
}

TEST_F(CommandLineTest, checkArgsIfOutputOptionIsInFirstPosition) {
  const char *cmdLine[] {"clrinvert", "-o", "../res/output/image.bmp", "../res/image.bmp"};
  commandLine.parse(sizeof(cmdLine)/sizeof(char*), cmdLine);
  ASSERT_THAT(commandLine.file_path(), testing::Eq("../res/image.bmp"));
  ASSERT_THAT(commandLine.output_path(), testing::Eq("../res/output/image.bmp"));
}
 
TEST_F(CommandLineTest, checkArgsIfOutputOptionIsInMiddlePosition) {
  const char *cmdLine[] {"clrinvert", "../res/image.bmp", "-o", "../res/output/image.bmp"};
  commandLine.parse(sizeof(cmdLine)/sizeof(char*), cmdLine);
  ASSERT_THAT(commandLine.file_path(), testing::Eq("../res/image.bmp"));
  ASSERT_THAT(commandLine.output_path(), testing::Eq("../res/output/image.bmp"));
}

