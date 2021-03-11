#include <sstream>
#include <iostream>

#include "gpu.hpp"
#include "runsh.hpp"
#include "trim.hpp"

GpuData::GpuData(ProcessesData *pdata)
  : _gpu(0)
  , _vram(0)
  , _pdata(pdata)
{
  // do nothing
}

void GpuData::update()
{
  std::string raw = runsh("nvidia-smi --query-gpu=utilization.gpu,utilization.memory,memory.total --format=csv,noheader,nounits");
  
  std::stringstream ss(raw), oss;

  std::string gpu_s, vram_s, vram_total_s;
  std::getline(ss, gpu_s, ',');
  std::getline(ss, vram_s, ',');
  std::getline(ss, vram_total_s, '\n');

  this->add_gpu_value(std::stof(gpu_s));
  this->add_vram_value(std::stof(vram_s));
  float vram_total = std::stof(vram_total_s);

  raw = runsh("nvidia-smi --query-compute-apps=pid,name,used_memory --format=csv,noheader,nounits");
  ss.str(raw);
  std::string name, buff, pid_s;
  float vram=0;
  while (std::getline(ss, buff, '\n')) {
    oss.str(buff);
    std::getline(oss, pid_s, ',');
    std::getline(oss, name, ',');
    trim(name);
    std::getline(oss, vram_s, '\n');
    vram = std::stof(vram_s)*100.0/vram_total;
    this->_pdata->add_process_gpuinfo(name, 0, vram);
  }
}

GpuData *check_has_gpu(ProcessesData *pd)
{
  if (system("which nvidia-smi > /dev/null 2>&1")) {
    return nullptr;
  }

  return new GpuData(pd);
}

void GpuData::add_gpu_value(float val) { this->add_val_to_vec(this->_gpu, val); }
void GpuData::add_vram_value(float val) { this->add_val_to_vec(this->_vram, val); }
float GpuData::gpu() const { return this->get_average(this->_gpu); }
float GpuData::vram() const { return this->get_average(this->_vram); }
