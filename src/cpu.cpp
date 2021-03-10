#include<iostream>
#include<string>
#include<sstream>

#include "cpu.hpp"
#include "runsh.hpp"

static float parse_cpu_perc(std::string &line)
{
  std::stringstream ss(line);
  std::string buff;
  for (int i = 0; i < 4; i++) std::getline(ss, buff, ',');
  ss.str(buff);
  std::getline(ss, buff, 'i');
  return 100.0 - std::stof(buff);
}

static float parse_ram_perc(std::string &line)
{
  std::stringstream ss(line);
  std::string buff;
  std::getline(ss, buff, ':');
  std::getline(ss, buff, 't');
  float total = std::stof(buff);
  std::getline(ss, buff, ',');
  std::getline(ss, buff, 'f');
  std::getline(ss, buff, ',');
  std::getline(ss, buff, 'u');
  float used = std::stof(buff);
  return 100.0*(used/total);
}

CpuData::CpuData()
  : _cpu(0)
  , _ram(0)
{
  // do nothing
}


void CpuData::update()
{
  auto raw = runsh("top bn1");

  std::stringstream ss(raw);
  std::string buff;
  for (int i = 0; i < 3; i++) std::getline(ss, buff, '\n');
  this->_cpu = parse_cpu_perc(buff);
  std::getline(ss, buff, '\n');
  this->_ram = parse_ram_perc(buff);
}

float CpuData::cpu() const { return this->_cpu; }
float CpuData::ram() const { return this->_ram; }
