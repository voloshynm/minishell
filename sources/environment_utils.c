#include "../includes/minishell.h"

// Custom function to swap two strings
void	ft_str_swap(char **a, char **b)
{
	char *temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

// Bubble sort function to sort array of strings
void	ft_str_bubble_sort(char **arr, int n)
{
	int i;
	int j;
	
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
				ft_str_swap(&arr[j], &arr[j + 1]);
			j++;
		}
		i++;
	}
}

int sizeof_2d_array(char **arr)
{
	int	n;

	n = 0;
	while (arr[n] != NULL)
		n++;
	return (n);
}

void	free_ft_split_fixed(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
