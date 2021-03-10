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


void CpuData::update()
{
  auto raw = runsh("top bn1");

  std::stringstream ss(raw);
  std::string buff;
  for (int i = 0; i < 3; i++) std::getline(ss, buff, '\n');
  this->add_cpu_value(parse_cpu_perc(buff));
  std::getline(ss, buff, '\n');
  this->add_ram_value(parse_ram_perc(buff));
}

void CpuData::add_cpu_value(float val) { this->add_val_to_vec(this->_cpu, val); }
void CpuData::add_ram_value(float val) { this->add_val_to_vec(this->_ram, val); }

float CpuData::cpu() const { return this->get_average(this->_cpu); }
float CpuData::ram() const { return this->get_average(this->_ram); }
