/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedrohe3 <pedrohe3@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 11:03:04 by pedrohe3          #+#    #+#             */
/*   Updated: 2026/10/19 18:06:00 by pedrohe3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct	s_coder
{
	int	deadline;
	int	idx;
	char	name[6];
}	t_coder;

typedef struct	s_heap
{
	t_coder	*arr;
	int	size;
}	t_heap;

t_heap	new_heap()
{
	t_heap	new;

	new.arr = NULL;
	size = 0;
	return new;
}

int	left_node(t_coder parent)
{
	'''
		In a heap every node can have a left child node
		with index equal to the node index multiplied by
		two.
	'''
	int	parent_idx;

	parent_idx = parent.idx;
	return parent_idx * 2;
}

int	right_node(t_coder parent)
{
	'''
		In a heap every node can have a right child node
		with index equal to the node index multiplied by
		two plus one.
	'''
	int	parent_idx;

	parent_idx = parent.idx;
	return (parent_idx * 2) + 1;
}

int	parent_node(t_coder node)
{
	''' 
		In a heap every node has its parent index
		equal to the integer division of the node
		index by two.
	'''
	int	node_idx;

	node_idx = node.idx;
	return node / 2;
}

void	add_2_heap(t_heap heap, t_coder coder)
{
	t_heap	new;

	new = new_heap();
	new.arr = malloc(sizeof(t_coder) * (heap.size + 1));
	if (!heap.arr)

}

int	main(void)
{
	t_item	*queue;

	queue = NULL;
	print(queue);
	add_item(&queue, 'o', 4);
	print(queue);
	add_item(&queue, 'e', 2);
	print(queue);
	add_item(&queue, 'u', 5);
	print(queue);
	add_item(&queue, 'a', 1);
	print(queue);
	add_item(&queue, 'o', 4);
	print(queue);
	add_item(&queue, 'e', 2);
	print(queue);
	add_item(&queue, 'u', 5);
	print(queue);
	add_item(&queue, 'a', 1);
	print(queue);
	return (0);
}
