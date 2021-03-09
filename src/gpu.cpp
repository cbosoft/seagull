#include <sstream>

#include "gpu.hpp"
#include "runsh.hpp"

GpuData get_gpu_data()
{
  std::string raw = runsh("nvidia-smi --query-gpu=utilization.gpu,utilization.memory --format=csv,noheader,nounits");
  
  std::stringstream ss(raw);

  std::string gpu_s, vram_s;
  std::getline(ss, gpu_s, ',');
  std::getline(ss, vram_s, '\n');

  GpuData rv = {0, 0};
  rv.gpu_perc = std::stof(gpu_s);
  rv.vram_perc = std::stof(vram_s);
  return rv;
}
