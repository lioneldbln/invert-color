#pragma once

#include <string>

class CommandLine {
private:
  uint32_t _args_count;
  std::string _file_path;
  std::string _output_path;

public:
  CommandLine() : _args_count{}, _file_path{}, _output_path{} {}
  ~CommandLine() = default;
  CommandLine(const CommandLine&) = default;
  CommandLine& operator=(const CommandLine&) = default;
  CommandLine(CommandLine&&) = default;
  CommandLine& operator=(CommandLine&&) = default;

  uint32_t args_count() { return _args_count; }
  std::string file_path() { return _file_path; }
  std::string output_path() { return _output_path; }

  void parse(int argc, const char * const argv[]);
};

