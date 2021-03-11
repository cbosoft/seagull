#include "process.hpp"
#include <sstream>
#include <algorithm>


ProcessData::ProcessData(const std::string &name)
  : name(name)
{
  this->cpu = this->ram = this->gpu = this->vram = -1;
}

float ProcessData::biggest_value() const
{
  std::vector<float> values{this->cpu, this->ram, this->gpu, this->vram};
  std::sort(values.rbegin(), values.rend());
  return values[0];
}


void ProcessesData::clear()
{
  for (const auto &kv : this->_data)
    delete kv.second;
  this->_data.erase(this->_data.begin(), this->_data.end());
}


void ProcessesData::add_process_cpuinfo(const std::string &name, float cpu, float ram)
{
  auto it = this->_data.find(name);
  if (it != this->_data.end()) {
    auto *pd = it->second;
    pd->cpu += cpu;
    pd->ram += ram;
  }
  else {
    auto *pd = new ProcessData(name);
    pd->cpu = cpu;
    pd->ram = ram;
    this->_data[name] = pd;
  }

}


void ProcessesData::add_process_gpuinfo(const std::string &name, float gpu, float vram)
{
  auto it = this->_data.find(name);
  if (it != this->_data.end()) {
    auto *pd = it->second;
    pd->gpu += gpu;
    pd->vram += vram;
  }
  else {
    auto *pd = new ProcessData(name);
    pd->gpu = gpu;
    pd->vram = vram;
    this->_data[name] = pd;
  }

}


typedef struct {
  float value;
  int colour;
} Measurement;

bool measure_compare(const Measurement&left, const Measurement &right)
{
  return left.value < right.value;
}

bool proc_data_ptr_compare(const ProcessData *left, const ProcessData *right)
{
  return *left < *right;
}

std::vector<std::string> ProcessesData::get_info_lines() const
{
  std::vector<ProcessData *> pds;
  for (const auto &kv : this->_data) {
    pds.push_back(kv.second);
  }

  std::sort(pds.rbegin(), pds.rend(), proc_data_ptr_compare);

  std::vector<std::string> rv;
  for (const auto &pd : pds) {
    std::stringstream ss;
    std::vector<Measurement> meas{
        {pd->cpu, 32},
        {pd->ram, 31},
        {pd->vram, 33}
    };

    std::sort(meas.rbegin(), meas.rend(), measure_compare);
    ss 
      << "\033[" << meas[0].colour << "m"
      << pd->name << " "
      << pd->biggest_value()
      << "\033[0m"
      ;
    rv.push_back(ss.str());
  }
  return rv;
}
