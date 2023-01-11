#ifndef LIBFT_H
#define LIBFT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_strlen(const char *str);

/****************************/
/*********** BONUD **********/
/****************************/

void	ft_error_exit(int flag);

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
