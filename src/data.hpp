#pragma once
#include <vector>

class AveragedData {
  public:
    AveragedData(size_t w=10)
      : _w(w)
    {
    }

    void add_val_to_vec(std::vector<float> &vec, float val)
    {
      if (vec.size() == this->_w) {
        vec.erase(vec.begin());
      }
      vec.push_back(val);
    }

    float get_average(const std::vector<float> &vec) const
    {
      float total = 0, size = float(vec.size());
      for (float val : vec)
        total += val;
      return total/size;
    }

  private:
    size_t _w;
};
