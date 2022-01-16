/*
 * Niklas Neronin <niklas.neronin@gmail.com>
 * https://github.com/Epicurius
 * 
 * Created: 2022/01/07 15:52:46 Niklas Neronin
 * Updated: 2022/01/16 12:49:18 Niklas Neronin
 * Copyright (c) 2022
 */

#include "liblg.h"

struct g_log	lg_global = {NULL, -1, -1};

int	lg_openFile(char *file, char *mode)
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

void	lg_closeFile(void)
{
	LG_INFO("Log Closed.");
	fclose(lg_global.fp);
}

void	lg_setLevel(int std, int file)
{
	if (std < 3)
		lg_global.stdlvl = std;
	if (file < 3)
		lg_global.filelvl = file;
}

static void	lg_write(lg_event *ev)
{
	char		buff[100];
	const char	*l[] = {"DEBUG", "INFO", "WARN", "ERROR"};
	const char	*c[] = {"\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m"};

	vsnprintf(buff, 100, ev->fmt, ev->ap);
	if (ev->lvl >= lg_global.stdlvl)
	{
		fprintf(LG_PRINT_STD, "%s[%-5s]\x1b[0m \x1b[90m%s:%d\x1b[0m : ",
			c[ev->lvl], l[ev->lvl], ev->func, ev->line);
		fprintf(LG_PRINT_STD, "%s\n", buff);
		fflush(LG_PRINT_STD);
	}
	if (ev->lvl >= lg_global.filelvl)
	{
		fprintf(lg_global.fp, "%s %-5s:\t\t%s\t\t", ev->time, l[ev->lvl], buff);
		fprintf(lg_global.fp, "[%s : %s : %d]\n", ev->file, ev->func, ev->line);
		fflush(lg_global.fp);
	}
}

void	lg_log(int lvl, const char *time, const char *file, const char *func,
	int line, const char *fmt, ...)
{
	lg_event	ev;

	if ((lg_global.fp && lvl >= lg_global.filelvl) || lvl >= lg_global.stdlvl)
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
