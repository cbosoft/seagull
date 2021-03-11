#pragma once
#include "process.hpp"
#include "data.hpp"

class CpuData: AveragedData {
  public:

    CpuData(ProcessesData *pdata);

    void update();

    float cpu() const;
    float ram() const;

    void add_cpu_value(float val);
    void add_ram_value(float val);

  private:
    std::vector<float> _cpu;
    std::vector<float> _ram;
    ProcessesData *_pdata;
};
