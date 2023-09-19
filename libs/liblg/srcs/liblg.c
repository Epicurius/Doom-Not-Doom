/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "liblg.h"

static const char *lg_levels[] = {
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR"
};

static const char *lg_colors[] = {
	"\x1b[36m",
	"\x1b[32m",
	"\x1b[33m",
	"\x1b[31m"
};

struct g_log	lg_global = {
	.fp=NULL,
	.stdlvl=-1,
	.filelvl=-1,
	.mutex=PTHREAD_MUTEX_INITIALIZER
};

int	lg_setFile(FILE *fp)
{
	if (lg_global.fp && fp != NULL) {
		LG_INFO("File already set.");
		return (0);
	}

	lg_global.fp = fp;
	return (1);
}

int	lg_openFile(char *file, char *mode)
{
	lg_global.fp = fopen(file, mode);
	if (lg_global.fp == NULL)
		return (0);

	return (1);
}

void	lg_closeFile(void)
{
	if (lg_global.fp == NULL)
		return ;

	fclose(lg_global.fp);
}

void	lg_setLevel(int std, int file)
{
	lg_global.stdlvl = std;
	lg_global.filelvl = file;
}

void	lg_fwrite(int lvl, const char *file, int line, const char *time,
	const char *fmt, va_list ap)
{
	pthread_mutex_lock(&lg_global.mutex);
#ifdef LG_USE_LIBPF
	ft_fprintf(lg_global.fp, "%s %-5s %s:%d\n\t",
		time, lg_levels[lvl], file, line);
	ft_vfprintf(lg_global.fp, fmt, ap);
#else
	fprintf(lg_global.fp, "%s %-5s %s:%d\n\t",
		time, lg_levels[lvl], file, line);
	vfprintf(lg_global.fp, fmt, ap);
	fflush(lg_global.fp);
#endif
	fwrite("\n", 1, 1, lg_global.fp);
	pthread_mutex_unlock(&lg_global.mutex);
}

void	lg_write(int lvl, const char *file, int line, const char *fmt,
	va_list ap)
{
	pthread_mutex_lock(&lg_global.mutex);
#ifdef LG_USE_LIBPF
	ft_fprintf(LG_PRINT_STD, "\n%s%-5s\x1b[0m \x1b[90m%s:%d\x1b[0m : ",
		lg_colors[lvl], lg_levels[lvl], file, line);
	ft_vfprintf(LG_PRINT_STD, fmt, ap);
#else
	fprintf(LG_PRINT_STD, "\n%s%-5s\x1b[0m \x1b[90m%s:%d\x1b[0m : ",
		lg_colors[lvl], lg_levels[lvl], file, line);
	vfprintf(LG_PRINT_STD, fmt, ap);
	fflush(LG_PRINT_STD);
#endif
	fwrite("\n", 1, 1, LG_PRINT_STD);
	pthread_mutex_unlock(&lg_global.mutex);
}

void	lg_log(int lvl, const char *time, const char *file, int line,
	const char *fmt, ...)
{
	va_list ap;
	if (lvl >= lg_global.stdlvl)
	{
		va_start(ap, fmt);
		lg_write(lvl, file, line, fmt, ap);
		va_end(ap);
	}
	if (lg_global.fp && lvl >= lg_global.filelvl)
	{
		va_start(ap, fmt);
		lg_fwrite(lvl, file, line, time, fmt, ap);
		va_end(ap);
	}

	if (lvl == LEVEL_ERROR) {
		lg_closeFile();
		exit (1);
	}
}
