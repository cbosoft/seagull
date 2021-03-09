#include <iostream>
#include <unistd.h>
#include "cpu.hpp"
#include "gpu.hpp"

void display_one(CpuData &cd, GpuData &gd)
{
  std::cout
    << cd.cpu_perc << " "
    << cd.ram_perc << " "
    << gd.gpu_perc << " "
    << gd.vram_perc
    << std::endl;
}

int main()
{
  unsigned int delay = 1000*1000;

  for (int i = 0; i < 100; i++) {
    auto cd = get_cpu_data();
    auto gd = get_gpu_data();
    display_one(cd, gd);
    usleep(delay);
  }
}
