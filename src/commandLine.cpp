#include "commandLine.h"

#include <queue>
#include <string>

#include "exception_d.h"

void CommandLine::parse(int argc, const char * const argv[]) {
  if (argc != 4) {
    throw bad_format_cmdline("invalid command line"); 
  }
  std::queue<std::string> args_list{};
  for (int i = 1; i < argc; i++) {
    args_list.push(argv[i]);
  }
  while(!args_list.empty()) {
    std::string arg{args_list.front()};
    args_list.pop();
    if (arg == "-o") {
      if (!args_list.empty()) {
        _output_path = args_list.front();
        args_list.pop();
      }
    }
    else {
      _file_path = arg;
    }
  }
  if (_file_path.length() == 0 || _output_path.length() == 0) {
    throw bad_format_cmdline("invalid command line");
  }
}

