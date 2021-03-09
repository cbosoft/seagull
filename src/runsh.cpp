#include "runsh.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

std::string runsh(const std::string& command)
{
  const char *cmd_cstr = command.c_str();
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd_cstr, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen failed!");
  }

  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  return result;
}
