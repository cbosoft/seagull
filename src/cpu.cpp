#include<iostream>
#include<string>
#include<sstream>

#include "cpu.hpp"
#include "runsh.hpp"

float parse_cpu_perc(std::string &line)
{
  std::stringstream ss(line);
  std::string buff;
  for (int i = 0; i < 4; i++) std::getline(ss, buff, ',');
  ss.str(buff);
  std::getline(ss, buff, 'i');
  return 100.0 - std::stof(buff);
}

float parse_ram_perc(std::string &line)
{
  std::stringstream ss(line);
  std::string buff;
  std::getline(ss, buff, ':');
  std::getline(ss, buff, 't');
  float total = std::stof(buff);
  std::getline(ss, buff, ',');
  std::getline(ss, buff, 'f');
  float free = std::stof(buff);
  return 100.0*(1. - free/total);
}


CpuData get_cpu_data()
{
  auto raw = runsh("top bn1");
  CpuData rv = {0, 0};

  std::stringstream ss(raw);
  std::string buff;
  for (int i = 0; i < 3; i++) std::getline(ss, buff, '\n');
  rv.cpu_perc = parse_cpu_perc(buff);
  std::getline(ss, buff, '\n');
  rv.ram_perc = parse_ram_perc(buff);
  return rv;
}
