#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(const char *str);
int		ft_putstr(const char *str);
char	*ft_itoa(int num);
void	ft_putnbr(int num);
char	*ft_strdup(const char *str);
void	ft_puthex(int num, int digit, int big);

/****************************/
/*********** BONUD **********/
/****************************/

void	ft_error_exit(int flag);

/*******************************/
/*********** FT_LIST ***********/
/*******************************/

typedef struct	s_list_node
{
	struct s_list_node	*next;
	struct s_list_node	*prev;
	void				*content;
}				t_list_node;

int		ft_list_size(t_list_node *lst);
void	ft_list_add_back(t_list_node **l, t_list_node *n);
void	ft_list_add_back_raw(t_list_node **l, void *c);
void	ft_list_clear(t_list_node **l, void (*del)(void*));
void	ft_list_show(t_list_node *l, void (*s)(void*));
void	ft_list_sort(t_list_node **l, int (*c)(void*, void*), int r);
//show func ptr
void	ft_list_show_func_ptr_int(void *c);
//comp func ptr
int		ft_list_comp_func_ptr_int(void *c1, void *c2);

/*******************************/
/*********** FT_QUEUE **********/
/*******************************/

typedef struct	s_q_node
{
	struct s_q_node	*next;
	struct s_q_node	*prev;
	void			*content;
}				t_q_node;

typedef struct	s_queue
{
	t_q_node	*head;
	t_q_node	*tail;
	int			size;
	uint8_t		pad[4];
}				t_queue;

t_q_node	*ft_q_node_new(void *content);
void	ft_q_node_add_last(t_q_node *tail, t_q_node *node);
void	queue_constructor(t_queue *q);
void	queue_destructor(t_queue *q);
int		queue_empty(t_queue *q);
int		queue_size(t_queue *q);
void	*queue_front(t_queue *q);
void	*queue_back(t_queue *q);
void	queue_push(t_queue *q, void *content);
void	queue_pop(t_queue *q);

#endif
