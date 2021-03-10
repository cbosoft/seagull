# seagull

CPU, RAM, GPU, VRAM utilisation.

Uses [annacrombie's plot library](https://github.com/annacrombie/plot) to plot system usage, as reported by `top` and `nvidia-smi`.

If `nvidia-smi` is not found, GPU reporting is disabled.


# Installation

Clone, make, make install:

```bash
git clone https://github.com/cbosoft/seagull
cd seagull
make
sudo make install
```

To uninstall
```bash
sudo make uninstall
```

# Why bother?

`htop` is awesome. `nvidia-smi` does the job, I guess. I wanted to graphically
show the combined output from both as rarely do I only care about CPU+RAM
utilization alone.
