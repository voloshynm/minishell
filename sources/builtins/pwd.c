#include "../../includes/minishell.h"

int pwd()
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
		return(p_error2("pwd: ", NULL));
	return (0);
}
