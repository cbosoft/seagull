#pragma once
#include <map>
#include <vector>
#include <string>

class ProcessData {
  public:
    ProcessData(const std::string &name);
    std::string name;
    float cpu, ram, gpu, vram;

    float biggest_value() const;

    bool operator<(const ProcessData &other) const
    {
      return this->biggest_value() < other.biggest_value();
    }
};

class ProcessesData {
  public:

    void clear();
    void add_process_cpuinfo(const std::string &name, float cpu, float ram);
    void add_process_gpuinfo(const std::string &name, float gpu, float vram);
    std::vector<std::string> get_info_lines() const;

  private:
    std::map<std::string, ProcessData *> _data;
};
