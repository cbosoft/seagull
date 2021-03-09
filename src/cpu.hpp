#pragma once

typedef struct {
  float cpu_perc;
  float ram_perc;
} CpuData;

CpuData get_cpu_data();
