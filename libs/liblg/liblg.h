/*
 * Epicurius <niklas.neronin@gmail.com>
 * https://github.com/Epicurius
 * 
 * Created: 2022/01/06 11:32:01 Epicurius
 * Updated: 2022/01/07 4:06:35 Niklas Neronin
 * Copyright (c) 2022
 */

#ifndef LIBLG_H
# define LIBLG_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

enum
{
	LEVEL_DEBUG,
	LEVEL_INFO,
	LEVEL_WARN,
	LEVEL_ERROR
};

# define LG_DEBUG(...)	lg_log(LEVEL_DEBUG, __TIME__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
# define LG_INFO(...)	lg_log(LEVEL_INFO,	__TIME__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
# define LG_WARN(...)	lg_log(LEVEL_WARN,	__TIME__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
# define LG_ERROR(...)	lg_log(LEVEL_ERROR, __TIME__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

typedef struct s_lgEvent
{
	va_list		ap;
	const char	*fmt;
	const char	*time;
	const char	*file;
	const char	*func;
	int			line;
	int			lvl;
}				lg_event;

typedef struct g_log
{
	FILE		*fp;
	int			fd;
	int			fdlvl;
	int			fplvl;
}				g_log;

/* File: ./liblg.c */
int			lg_openFile(char *file, char *mode);
void		lg_addFile(FILE *fp);
void		lg_closeFile(void);
void		lg_setFpLevel(int lvl);
void		lg_setFdLevel(int lvl);
void		lg_log(int lvl, const char *time, const char *file,
				const char *func, int line, const char *fmt, ...);
#endif
