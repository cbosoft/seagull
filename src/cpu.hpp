#pragma once

class CpuData {
  public:
    CpuData();

    void update();

    float cpu() const;
    float ram() const;

  private:
    float _cpu;
    float _ram;
};
