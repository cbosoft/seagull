/*

based on https://github.com/annacrombie/plot/blob/master/examples/simple_curses.c

but without the curses.

 */

#define _POSIX_C_SOURCE 200809L
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

#include <array>
#include <sstream>

#include "legend.hpp"
#include "process.hpp"
#include "cpu.hpp"
#include "gpu.hpp"
#include "plot.h"

void clear_screen()
{
  system("clear");
}

static bool resized = true;
static bool done = false;

static uint32_t
cpu_perc(void *cd_vptr, double *out, uint32_t out_max)
{
  (void) out_max;
  auto *cd = (CpuData *)cd_vptr;
  *out = double(cd->cpu());
	return 1;
}

static uint32_t
ram_perc(void *cd_vptr, double *out, uint32_t out_max)
{
  (void) out_max;
  auto *cd = (CpuData *)cd_vptr;
  *out = double(cd->ram());
	return 1;
}

static uint32_t
gpu_perc(void *gd_vptr, double *out, uint32_t out_max)
{
  (void) out_max;
  auto *gd = (GpuData *)gd_vptr;
  *out = double(gd->gpu());
	return 1;
}

static uint32_t
vram_perc(void *gd_vptr, double *out, uint32_t out_max)
{
  (void) out_max;
  auto *gd = (GpuData *)gd_vptr;
  *out = double(gd->vram());
	return 1;
}

static void
handle_sigwinch(int _)
{
  (void) _;
	resized = true;
}

static void
handle_sigint(int _)
{
  (void) _;
	done = true;
}

#define MAX_HEIGHT 256
#define MAX_WIDTH 256

void show_cursor() { std::cout << "\033[?25h" << std::endl; }
void hide_cursor() { std::cout << "\033[?25l" << std::endl; }

int
main(void)
{

	struct plot *p = plot_alloc(MAX_HEIGHT, MAX_WIDTH, 12);

  std::array<char, 10000> buffer;

  signal(SIGWINCH, handle_sigwinch);
  signal(SIGINT, handle_sigint);

  auto *pd = new ProcessesData();
  auto *cd = new CpuData(pd);
  cd->update();
	plot_add_dataset(p, plot_color_green, nullptr, 0, cpu_perc, cd);
	plot_add_dataset(p, plot_color_red, nullptr, 0, ram_perc, cd);

  auto *gd = check_has_gpu(pd);
  if (gd) {
    gd->update();
	  plot_add_dataset(p, plot_color_blue, nullptr, 0, gpu_perc, gd);
	  plot_add_dataset(p, plot_color_yellow, nullptr, 0, vram_perc, gd);
  }

  hide_cursor();
	while (!done) {
		if (resized) {
			struct winsize w;

			ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

			if ((p->width = w.ws_col) > MAX_WIDTH) {
				p->width = MAX_WIDTH;
			}

			p->width -= 20;

			if ((p->height = w.ws_row) > MAX_HEIGHT) {
				p->height = MAX_HEIGHT;
			}

			p->height -= 2;

			resized = false;
		}

    cd->update();
    if (gd) gd->update();
		plot_fetch(p, 1);
		plot_string(p, buffer.data(), buffer.size());
    auto info = pd->get_info_lines();
    size_t ninfo = info.size();

    if (true) {
      clear_screen();
      pd->clear();
      std::cout
        << "   \033[30;44mseagull\033[0m  │ "
        << get_ordered_legend(cd, gd) << "  │ ";
      for (size_t i = 0; i < 3 && i < ninfo; i++)
        std::cout << info[i] << " ";

      std::cout << '\n' << buffer.data() << std::flush;
    }

		usleep(1000*1000);
	}

  clear_screen();

  show_cursor();

	plot_free(p);
  delete cd;
  delete gd;
}
