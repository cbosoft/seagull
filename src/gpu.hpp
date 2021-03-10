#pragma once
#include "data.hpp"

class GpuData: AveragedData{
  public:
    GpuData();

    void update();
    float gpu() const;
    float vram() const;

    void add_gpu_value(float val);
    void add_vram_value(float val);

  private:
    std::vector<float> _gpu;
    std::vector<float> _vram;
};

GpuData *check_has_gpu();
