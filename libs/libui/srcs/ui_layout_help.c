/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

char	*ui_get_file_content(t_ui_layout *layout, char *file)
{
	char	*content;
	char    line[256];
	char	*trim;
	FILE	*fp;

	fp = fopen(file, "r");
	content = NULL;
	while (fp)
	{
		if (fgets(line, 256, fp) == NULL)
			break ;
		trim = ft_supertrim(line);
		if (trim != NULL && !get_special(layout, trim))
			ft_stradd(&content, trim);
	}
	fclose(fp);
	if (!content)
		ft_printf("[%s] Couldn\'t open file <%s>\n", __FUNCTION__, file);
	return (content);
}

/*
 * Returns how many 'global' elements in the file;
 * One global elem is where the string ends in ';' and
 * the '{' count matches '}' count;
*/
void	elems_in_string(char *str, int *elem_pos, int *amount)
{
	int	i;
	int	close;
	int	open;
	int	prev_i;

	i = -1;
	open = 0;
	close = 0;
	prev_i = 0;
	*amount = 0;
	while (str[++i])
	{
		if (str[i] == ';' && open == close)
		{
			elem_pos[*amount] = prev_i;
			elem_pos[*amount + 1] = i - prev_i + 1;
			prev_i = i + 1;
			*amount += 2;
		}
		else if (str[i] == '{')
			open++;
		else if (str[i] == '}')
			close++;
	}
}

char	**split_string_into_array(char *str)
{
	char	**final;
	int		i;
	int		elem_count;
	int		elem_pos[1024];
	int		amount;

	i = 0;
	elem_count = -1;
	amount = 0;
	elems_in_string(str, elem_pos, &amount);
	final = malloc(sizeof(char *) * ((amount / 2) + 1));
	while (i < amount)
	{
		final[++elem_count] = ft_strsub(str, elem_pos[i], elem_pos[i + 1]);
		i += 2;
	}
	final[++elem_count] = 0;
	return (final);
}

/*
 * Takes the layout_file_content and makes the elements with their children.
 * This finds window and creates its elements.
*/
void	layout_make_family_trees(t_ui_layout *layout)
{
	int			i;
	char		**arr;
	t_ui_family	*family;

	arr = layout->layout_element_strings;
	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		family = make_family_from_string(arr[i]);
		if (family)
			add_to_list(&layout->families, family, sizeof(t_ui_family));
	}
}
