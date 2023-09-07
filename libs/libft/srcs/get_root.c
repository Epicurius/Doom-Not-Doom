/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin
 */

#if __linux__

#include <linux/limits.h>
#include <unistd.h>

int	get_root(char *root, int size)
{
    int len;

    len = readlink("/proc/self/exe", root, size - 1);
    if (len <= 0)
        return 0;

    len -= 1;
    while (root[len] != '/') {
        root[len] = '\0';
        len--;
    }

    return (len + 1);
}

#elif __APPLE__

#include <mach-o/dyld.h>

int	get_root(char *root, int size)
{
    uint32_t len;

    len = size;
    if (_NSGetExecutablePath(root, &len) != 0)
        return 0;

	len = 0;
	while (root[len])
		len++;
    while (root[len] != '/') {
        root[len] = '\0';
        len--;
    }

    return (len + 1);
}

#elif _WIN32

#include <Windows.h>

int	get_root(char *root, int size)
{
    int len;

	len = GetModuleFileName(NULL, root, size);
    if (len <= 0)
        return 0;

    len -= 1;
    while (root[len] != '\\') {
        root[len] = '\0';
        len--;
    }

    return (len + 1);
}

#endif