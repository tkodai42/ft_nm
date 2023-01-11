/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkodai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:11:52 by tkodai            #+#    #+#             */
/*   Updated: 2023/01/10 12:24:51 by tkodai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_q_node	*ft_q_node_new(void *content)
{
	t_q_node	*ret;

	ret = malloc(sizeof(t_q_node));
	if (ret != NULL)
	{
		ret->next = NULL;
		ret->prev = NULL;
		ret->content = content;
	}
	return ret;
}

void	ft_q_node_add_last(t_q_node *tail, t_q_node *node)
{
	while (tail->next)
	{
		tail = tail->next;
	}
	tail->next = node;
	node->prev = tail;
}

void	queue_constructor(t_queue *q)
{
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

void	queue_destructor(t_queue *q)
{
	t_q_node *tmp;
	t_q_node *del;

	tmp = q->head;
	while (tmp)
	{
		del = tmp;
		tmp = tmp->next;
		free(del);
	}
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

int		queue_empty(t_queue *q)
{
	if (q->size == 0)
		return 1;
	return 0;
}

int		queue_size(t_queue *q)
{
	return (q->size);
}

void	*queue_front(t_queue *q)
{
	return (q->head->content);
}

void	*queue_back(t_queue *q)
{
	return (q->tail->content);
}

void	queue_push(t_queue *q, void *content)
{
	t_q_node	*tmp;

	if (q->head == NULL)
	{
		q->head = ft_q_node_new(content);
		if (q->head == NULL)
			ft_error_exit(1 /*MALLOC_ERR*/);
		q->tail = q->head;
		if (q->tail != NULL)
			q->size++;
		return ;
	}
	tmp = ft_q_node_new(content);
	if (tmp == NULL)
		ft_error_exit(1 /*MALLOC_ERR*/);
	ft_q_node_add_last(q->tail, tmp);
	q->tail = tmp;
	q->size++;
}

void	queue_pop(t_queue *q)
{
	t_q_node	*tmp;

	if (q->head == NULL)
		return ;
	tmp = q->head;	
	q->head = tmp->next;
	q->size--;
	if (q->size == 0)
		q->tail = NULL;
	free(tmp);
}


/*
#include <stdio.h>

void	main2()
{
	t_queue q_tmp;
	t_queue *q = &q_tmp;

	queue_constructor(q);
	queue_push(q, (void *)3);
	queue_push(q, (void *)4);
	queue_push(q, (void *)5);
	queue_push(q, (void *)6);
	printf("size %d\n", queue_size(q));

	while (queue_size(q) != 0)
	{
		int num = (int)queue_front(q);
		queue_pop(q);
		printf("front %d\n", num);

	}

	//queue_destructor(q);
}

int		main()
{
	main2();
	system("leaks a.out");
}
*/


