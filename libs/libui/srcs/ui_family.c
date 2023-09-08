/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * Returns head family;
*/
t_ui_family	*create_family(char *name, char *type, char *children)
{
	t_ui_family	*family;
	t_ui_family	*child;
	int			k;

	family = ft_memalloc(sizeof(t_ui_family));
	family->id = ft_strdup(name);
	family->type = ui_element_type_from_string(type);
	family->children_strings = split_string_into_array(children);
	k = -1;
	while (family->children_strings[++k])
	{
		child = make_family_from_string(family->children_strings[k]);
		if (!child)
			break ;
		add_to_list(&family->children, child, sizeof(t_ui_family));
	}
	return (family);
}

t_ui_family	*make_family_from_string(char *str)
{
	t_ui_family	*family;
	char		**temp;
	char		**type_n_name;
	int			len;
	char		*children;

	temp = ft_strsplitfirstoccurence(str, '{');
	len = ft_strlen(temp[1]);
	family = NULL;
	if (len != 0)
	{
		children = ft_strndup(temp[1], len - 2);
		type_n_name = ft_strsplit(temp[0], ' ');
		family = create_family(type_n_name[1], type_n_name[0], children);
		ft_strdel(&children);
		ft_arraydel(type_n_name);
	}
	ft_arraydel(temp);
	return (family);
}

void	ui_family_free(void *family, size_t size)
{
	t_ui_family	*fam;

	fam = family;
	if (!fam)
		return ;
	free(fam->id);
	ft_arraydel(fam->children_strings);
	ft_lstdel(&fam->children, &ui_family_free);
	free(fam);
	(void)size;
}

void	make_family_from_children(
		t_list **list, void *parent, int parent_type, t_ui_family *family)
{
	t_list	*rruc;

	rruc = family->children;
	while (rruc)
	{
		make_elements_from_family(
			list, parent, parent_type, rruc->content);
		rruc = rruc->next;
	}
}

/*
 * NOTE:
 * 1. if the parent element is of type that has another element contained in it.
 * 	(button has label, dropdown has menu...)
 * 	make that child element the id of whatever you have decided it to be.
 * 	no need to make new element since we already have that.
 * 2. If the element type has a getter, we try to get the child,
 * 	but if the element doesn't have of that type of child,
 * 	we make a new elem.
*/
void	make_elements_from_family(
		t_list **list, void *parent, int parent_type, t_ui_family *family)
{
	t_ui_element	*elem;
	t_list			*rruc;

	elem = NULL;
	if (parent_type == UI_TYPE_ELEMENT
		&& g_acceptable[((t_ui_element *)parent)->element_type].getter)
	{
		elem = g_acceptable[((t_ui_element *)parent)->element_type].getter(
				parent, family->type);
		if (elem)
			ui_element_set_id(elem, family->id);
	}
	if (!elem)
	{
		elem = ft_memalloc(sizeof(t_ui_element));
		if (parent_type == UI_TYPE_WINDOW)
			g_acceptable[family->type].maker(parent, elem);
		else
			g_acceptable[family->type].maker(
				((t_ui_element *)parent)->win, elem);
		ui_element_set_parent(elem, parent, parent_type);
		ui_element_set_id(elem, family->id);
	}
	make_family_from_children(list, elem, UI_TYPE_ELEMENT, family);
	add_to_list(list, elem, UI_TYPE_ELEMENT);
}

/*
void	print_family(t_ui_family *family, int nth)
{
	t_list	*curr;
	int		tabs;

	tabs = -1;
	while (++tabs < nth)
		ft_putchar('\t');
	ft_printf("%s\n", family->id);
	tabs = -1;
	while (++tabs < nth)
		ft_putchar('\t');
	ft_putstr("{\n");
	curr = family->children;
	while (curr)
	{
		print_family(curr->content, nth + 1);
		curr = curr->next;
	}
	tabs = -1;
	while (++tabs < nth)
		ft_putchar('\t');
	ft_putstr("}\n");
}
*/
