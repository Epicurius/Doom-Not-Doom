/*
 * Niklas Neronin <niklas.neronin@gmail.com>
 * https://github.com/Epicurius
 * 
 * Created: 2022/01/07 3:52:46 Niklas Neronin
 * Updated: 2022/01/07 4:17:33 Niklas Neronin
 * Copyright (c) 2022
 */

#include "liblg.h"

struct g_log lg_global = {NULL, 1, -1, -1};

void	lg_closeFile(void)
{
	LG_INFO("Log Closed.");
	fclose(lg_global.fp);
}

int		lg_openFile(char *file, char *mode)
{
	lg_global.fp = fopen(file, mode);
	if (NULL)
		return (0);
	LG_INFO("Log Opened.");
	return (1);
}

void	lg_addFile(FILE *fp)
{
	lg_global.fp = fp;
}

void	lg_setFpLevel(int lvl)
{
	if (lvl < 3)
		lg_global.fplvl = lvl;
}

void	lg_setFdLevel(int lvl)
{
	if (lvl < 3)
		lg_global.fdlvl = lvl;
}

static void lg_write(lg_event *ev)
{
	char				buff[100];
	static const char	*level[] = {"DEBUG", "INFO", "WARN", "ERROR"};
	static const char	*color[] = {"\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m"};

	vsnprintf(buff, 100, ev->fmt, ev->ap);
	if (ev->lvl >= 0 && ev->lvl >= lg_global.fdlvl)
	{
		fprintf(stderr, "%s[%-5s]\x1b[0m \x1b[90m%s:%d\x1b[0m : ", color[ev->lvl], level[ev->lvl], ev->func, ev->line);
		fprintf(stderr, "%s\n", buff);
		fflush(stderr);
	}
	if (lg_global.fp && ev->lvl >= lg_global.fplvl)
	{
		fprintf(lg_global.fp, "%s %-5s:\t\t%s", ev->time, level[ev->lvl], buff);
		fprintf(lg_global.fp, "\t\t[%s : %s : %d]\n", ev->file, ev->func, ev->line);
		fflush(lg_global.fp);
	}
}

void lg_log(int lvl, const char *time, const char *file, const char *func, int line, const char *fmt, ...)
{
	lg_event	ev;

	if (lg_global.fd >= 0 || lg_global.fp)
	{
		ev.fmt = fmt;
		ev.time = time;
		ev.file = file;
		ev.func = func;
		ev.line = line;
		ev.lvl = lvl;
		va_start(ev.ap, fmt);
		lg_write(&ev);
		va_end(ev.ap);
	}
	if (lvl == LEVEL_ERROR)
		exit (1);
}
