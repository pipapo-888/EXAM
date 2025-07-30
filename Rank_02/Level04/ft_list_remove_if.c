#include <stdio.h>

typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *temp;

	temp = begin_list;
	while (temp)
	{
		int answer = cmp(temp -> data, data_ref);
		if (answer == 0)
			free(temp -> data);
		temp = temp -> next;

	}
	return ;
}
