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

std::string get_ordered_legend(float cpu_perc, float ram_perc, float gpu_perc, float vram_perc)
{
  std::vector<LegendItem> items = {
     {cpu_perc, "\033[32mCPU"},
     {ram_perc, "\033[31mRAM"},
     {gpu_perc, "\033[34mGPU"},
     {vram_perc, "\033[33mVRAM"}
  };

  std::sort(items.begin(), items.end());

  std::stringstream ss;
  ss << items[0].name() << ">";
  ss << items[1].name() << ">";
  ss << items[2].name() << ">";
  ss << items[3].name();

  ss << "\033[0m";
  return ss.str();
}
