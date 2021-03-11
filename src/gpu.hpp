#pragma once
#include "process.hpp"
#include "data.hpp"

class GpuData: AveragedData{
  public:
    GpuData(ProcessesData *pdata);

    void update();
    float gpu() const;
    float vram() const;

    void add_gpu_value(float val);
    void add_vram_value(float val);

  private:
    std::vector<float> _gpu;
    std::vector<float> _vram;
    ProcessesData *_pdata;
};

GpuData *check_has_gpu(ProcessesData *pd);
