#include "libft.h"

int		ft_list_size(t_list_node *lst)
{
	t_list_node		*next_list;
	int				i;

	if (lst == NULL)
		return (0);
	i = 1;
	next_list = lst;
	while (next_list->next != NULL)
	{
		i++;
		next_list = next_list->next;
	}
	return (i);
}

t_list_node	*ft_list_new(void *content)
{
	t_list_node	*new_lst;

	if (!(new_lst = malloc(sizeof(t_list_node))))
	{
		ft_malloc_error();
		return NULL;
	}
	new_lst->content = content;
	new_lst->next = NULL;
	new_lst->prev = NULL;
	return (new_lst);
}

t_list_node	*ft_list_last(t_list_node *lst)
{
	t_list_node	*ret_list;

	if (!lst)
		return (NULL);
	ret_list = lst;
	while (ret_list->next != NULL)
	{
		ret_list = ret_list->next;
	}
	return (ret_list);
}

t_list_node	*ft_list_add_back(t_list_node **lst, t_list_node *new)
{
	t_list_node	*tmp;

	if (lst == NULL)
		return NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return new;
	}
	tmp = ft_list_last(*lst);
	tmp->next = new;
	new->prev = tmp;
	return new;
}

t_list_node	*ft_list_add_back_raw(t_list_node **lst, void *content)
{
	t_list_node	*tmp;
	t_list_node *new;

	if (lst == NULL)
		return NULL;
	new = ft_list_new(content);
	if (new == NULL)
		return NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return new;
	}
	tmp = ft_list_last(*lst);
	tmp->next = new;
	new->prev = tmp;
	return new;
}

void	ft_list_clear(t_list_node **lst, void (*del)(void*))
{
	t_list_node		*tmp_lst;

	while (*lst)
	{
		tmp_lst = *lst;
		if (del != NULL)
			del((*lst)->content);
		*lst = tmp_lst->next;
		free(tmp_lst);
	}
	*lst = NULL;
}

/* show function ptr */
void	ft_list_show_func_ptr_int(void *c)
{
	//printf("[%lld]", (long long)c);
	long long	n = (long long)c;
	int			num = (int)n;

	ft_printf("[%d]", num);
}

void	ft_list_show_func_ptr_str(void *c)
{
	ft_printf("[%s]", (char*)c);
}


void	ft_list_show(t_list_node *head, void (*show)(void*))
{
	while (head)
	{
		show(head->content);	
		head = head->next;
	}
}

/* comp function ptr */
int		ft_list_comp_func_ptr_int(void *c1, void *c2)
{
	return (long long)c1 - (long long)c2;
}

/*
void	ft_swap(int *x, int *y)
{
	int		tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}*/

void	ft_swap(t_list_node **tab, int left, int right)
{
	t_list_node	*tmp;

	tmp = tab[left];
	tab[left] = tab[right];
	tab[right] = tmp;
}

void	ft_quick_sort(t_list_node **tab, int (*comp)(void*, void*), int left, int right)
{
	t_list_node		*pivot;
    int 			l;
	int				r;

    if (left >= right)
        return;
    pivot = tab[left];
    l = left;
    r = right;

    while (1)
	{
        while (comp(tab[l]->content, pivot->content) < 0)
            l++;
        while (comp(tab[r]->content, pivot->content) > 0)
            r--;
        if (l >= r)
            break;
        ft_swap(tab, l, r);
        l++;
        r--;
    }
    ft_quick_sort(tab, comp, left, l - 1);
    ft_quick_sort(tab, comp, r + 1, right);
}

void	ft_quick_sort_rev(t_list_node **tab, int (*comp)(void*, void*), int left, int right)
{
	t_list_node		*pivot;
    int 			l;
	int				r;

    if (left >= right)
        return;
    pivot = tab[left];
    l = left;
    r = right;

    while (1)
	{
        while (comp(tab[l]->content, pivot->content) > 0)
            l++;
        while (comp(tab[r]->content, pivot->content) < 0)
            r--;
        if (l >= r)
            break;
        ft_swap(tab, l, r);
        l++;
        r--;
    }
    ft_quick_sort_rev(tab, comp, left, l - 1);
    ft_quick_sort_rev(tab, comp, r + 1, right);
}


void	ft_list_sort(t_list_node **lst, int (*comp)(void*, void*), int is_rev)
{
	int			size;
	int			index = 0;
	t_list_node	*tmp;
	t_list_node **ary;

	if (lst == NULL || *lst == NULL)
		return ;
	size = ft_list_size(*lst);
	ary = malloc(sizeof(t_list_node) * size);
	if (ary == NULL)
	{
		ft_malloc_error();
		return ;
	}

	//--- fill ---
	tmp = *lst;
	index = 0;
	while (tmp)
	{
		ary[index++] = tmp;
		tmp = tmp->next;
	}
	//--- sort ---
#if 1
	if (is_rev == 0)
		ft_quick_sort(ary, comp, 0, size - 1);
	else
		ft_quick_sort_rev(ary, comp, 0, size - 1);
#else 
	int			swap_flag = 0;
				index = 0;

	while (index + 1 < size)
	{
		swap_flag = 0;
		if (is_rev == 0)
		{
			if (comp(ary[index]->content, ary[index + 1]->content) > 0)
				swap_flag = 1;
		}
		else
		{
			if (comp(ary[index + 1]->content, ary[index]->content) > 0)
				swap_flag = 1;
		}
		if (swap_flag == 1)
		{
			tmp = ary[index];
			ary[index] = ary[index + 1];
			ary[index + 1] = tmp;
			index = 0;
			continue ;
		}
		index++;
	}
#endif

	//--- refill ---
	index = 0;
	ary[0]->prev = NULL;
	ary[size - 1]->next = NULL;
	while (index + 1 < size)
	{
		ary[index]->next = ary[index + 1];
		ary[index + 1]->prev = ary[index];
		index++;
	}
	*lst = ary[0];
	free(ary);
}

