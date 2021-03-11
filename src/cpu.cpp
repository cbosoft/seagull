#include<iostream>
#include<string>
#include<sstream>

#include "trim.hpp"
#include "cpu.hpp"
#include "runsh.hpp"

CpuData::CpuData(ProcessesData *pdata)
  : _pdata(pdata)
{
  // do nothing
}

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

static bool parse_proc(const std::string &procline, int &pid, std::string &name, float &cpu, float &ram)
{
  static float nproc = -1;

  if (nproc < 0) {
    std::string nproc_s = runsh("nproc");
    nproc = std::stof(nproc_s);
  }

  auto start = procline.begin();
  // PID,USER,PR,NI,VIRT,RES,SHR,S,CPU%,MEM%,TIME+,COMMAND
  //   7,  10, 4, 4,   8,  7,  7,2,   6,   6,   10, rest
  std::string buf(start, start+7);
  int _pid = std::stoi(buf);
  
  start = start+7+10+4+4+8+7+7+2;
  buf = std::string(start, start+6);
  int _cpu = std::stof(buf)/nproc;

  start = start + 6;
  buf = std::string(start, start+6);
  int _ram = std::stof(buf);

  start = start + 16;
  buf = std::string(start, procline.end());

  if (_cpu > 10.0 || _ram > 10.0) {
    pid = _pid;
    name = buf;
    trim(name);
    cpu = _cpu;
    ram = _ram;
    return true;
  }

  return false;
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
  for (int i = 0; i < 3; i++) std::getline(ss, buff, '\n');

  int pid = 0;
  std::string name;
  float cpu=0, ram=0;
  while (std::getline(ss, buff, '\n')) {
    if (parse_proc(buff, pid, name, cpu, ram)) {
      this->_pdata->add_process_cpuinfo(name, cpu, ram);
    }
    else {
      break;
    }
  }
}

void CpuData::add_cpu_value(float val) { this->add_val_to_vec(this->_cpu, val); }
void CpuData::add_ram_value(float val) { this->add_val_to_vec(this->_ram, val); }

float CpuData::cpu() const { return this->get_average(this->_cpu); }
float CpuData::ram() const { return this->get_average(this->_ram); }
