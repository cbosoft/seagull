#pragma once

typedef struct {
  float gpu_perc;
  float vram_perc;
} GpuData;

GpuData get_gpu_data();
