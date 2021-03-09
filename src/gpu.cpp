#include <sstream>
#include <iostream>

#include "gpu.hpp"
#include "runsh.hpp"

GpuData::GpuData()
  : _gpu(0)
  , _vram(0)
{
  // do nothing
}

void GpuData::update()
{
  std::string raw = runsh("nvidia-smi --query-gpu=utilization.gpu,utilization.memory --format=csv,noheader,nounits");
  
  std::stringstream ss(raw);

  std::string gpu_s, vram_s;
  std::getline(ss, gpu_s, ',');
  std::getline(ss, vram_s, '\n');

  this->_gpu = std::stof(gpu_s);
  this->_vram = std::stof(vram_s);
}

GpuData *check_has_gpu()
{
  if (system("which nvidia-smi > /dev/null 2>&1")) {
    return nullptr;
  }

  return new GpuData();
}

float GpuData::gpu() const { return this->_gpu; }
float GpuData::vram() const { return this->_vram; }
