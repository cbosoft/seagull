#pragma once
#include "data.hpp"

class CpuData: AveragedData {
  public:

    void update();

    float cpu() const;
    float ram() const;

    void add_cpu_value(float val);
    void add_ram_value(float val);

  private:
    std::vector<float> _cpu;
    std::vector<float> _ram;
};
