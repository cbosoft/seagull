# seagull

<center>
<img src="https://raw.githubusercontent.com/cbosoft/seagull/master/screen1.png?raw=true" width="80%"/>
</center>

CPU, RAM, GPU, VRAM utilisation.

Uses [annacrombie's plot library](https://github.com/annacrombie/plot) to plot
system usage, as reported by `top` and `nvidia-smi`.  Offending processes are
marked along the top, colour coded by their biggest used measurement. Per-process
GPU usage is unavailable, unfortunately.

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
