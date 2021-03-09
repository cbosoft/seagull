#pragma once

class GpuData {
  public:
    GpuData();

    void update();
    float gpu() const;
    float vram() const;

  private:
    float _gpu;
    float _vram;
};

GpuData *check_has_gpu();
