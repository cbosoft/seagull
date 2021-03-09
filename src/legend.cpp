#include "legend.hpp"
#include <vector>
#include <algorithm>
#include <sstream>

class LegendItem {
  public:
    LegendItem(float value, const std::string &name)
      : _value(value)
      , _name(name)
    {
    }

    bool operator<(const LegendItem &other) const
    {
      // backwards for descending sort
      return this->_value > other._value;
    }

    const std::string &name()
    {
      return this->_name;
    }

  private:
    float _value;
    std::string _name;
};

std::string get_ordered_legend(CpuData *cd, GpuData *gd)
{
  std::vector<LegendItem> items = {
     {cd->cpu_perc, "\033[32mCPU"},
     {cd->ram_perc, "\033[31mRAM"}
  };

  if (gd) {
    items.push_back(LegendItem(gd->gpu_perc, "\033[34mGPU"));
    items.push_back(LegendItem(gd->vram_perc, "\033[33mVRAM"));
  }

  std::sort(items.begin(), items.end());

  std::stringstream ss;
  for (size_t i = 0; i < items.size(); i++) {
    ss << items[i].name() << "\033[0m";
    if (i < items.size()-1) {
      ss << ">";
    }
  }

  if (!gd) {
    ss << " (no GPU)";
  }

  return ss.str();
}
