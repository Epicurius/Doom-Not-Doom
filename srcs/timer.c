/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/29 12:22:09 nneronin
 * Updated: 2021/12/29 16:05:29 nneronin
 */

#include "doom.h"

struct timespec	g_doom_timer_start;

void	doom_timer_start(void)
{
	clock_gettime(CLOCK_MONOTONIC, &g_doom_timer_start);
}

double	doom_timer_end(void)
{
	struct timespec	finish;
	double			elapsed;

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - g_doom_timer_start.tv_sec);
	elapsed += (finish.tv_nsec - g_doom_timer_start.tv_nsec) / 1000000000.0;
	return (elapsed);
}
