/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#ifndef LIBLG_H
# define LIBLG_H

# include <pthread.h>

# define LG_USE_LIBPF

#ifdef LG_USE_LIBPF
# include "../libpf/libpf.h"
# include "../libft/libft.h"
#else
# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
#endif

enum
{
	LEVEL_DEBUG,
	LEVEL_INFO,
	LEVEL_WARN,
	LEVEL_ERROR
};

# define LG_PRINT_STD	stderr 

# define LG_DEBUG(...)	lg_log(LEVEL_DEBUG, __TIME__, __FILE__, __LINE__, __VA_ARGS__)
# define LG_INFO(...)	lg_log(LEVEL_INFO, __TIME__, __FILE__, __LINE__, __VA_ARGS__)
# define LG_WARN(...)	lg_log(LEVEL_WARN, __TIME__, __FILE__, __LINE__, __VA_ARGS__)
# define LG_ERROR(...)	lg_log(LEVEL_ERROR, __TIME__, __FILE__, __LINE__, __VA_ARGS__)

typedef struct g_log
{
	FILE			*fp;
	int				stdlvl;
	int				filelvl;
	pthread_mutex_t	mutex;
}				g_log;

/* File: ./liblg.c */
void		lg_setLevel(int std, int file);
int			lg_setFile(FILE *fp);
int			lg_openFile(char *file, char *mode);
void		lg_closeFile(void);
void		lg_fwrite(int lvl, const char *file, int line, const char *time,
					  const char *fmt, va_list ap);
void		lg_write(int lvl, const char *file, int line,
					 const char *fmt, va_list ap);
void		lg_log(int lvl, const char *time, const char *file,
				   int line, const char *fmt, ...);
#endif
