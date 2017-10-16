#pragma once

#include <exception>

class bad_format_cmdline : public std::exception {
private:
  std::string message;
public:
  bad_format_cmdline(const std::string &message) : message(message) {}
  ~bad_format_cmdline() = default;
  bad_format_cmdline(const bad_format_cmdline&) = default;
  bad_format_cmdline& operator=(const bad_format_cmdline&) = default;
  bad_format_cmdline(bad_format_cmdline&&) = default;
  bad_format_cmdline& operator=(bad_format_cmdline&&) = default;

  const char* what() const noexcept override { return message.c_str(); }
};


class opening_file_error : public std::exception {
private:
  std::string message;
public:
  opening_file_error(const std::string &message) : message(message) {}
  ~opening_file_error() = default;
  opening_file_error(const opening_file_error&) = default;
  opening_file_error& operator=(const opening_file_error&) = default;
  opening_file_error(opening_file_error&&) = default;
  opening_file_error& operator=(opening_file_error&&) = default;

  const char* what() const noexcept override { return message.c_str(); }
};


