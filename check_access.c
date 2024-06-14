#include "execute.h"

char	*get_path(char **env)
{
	int		i;

	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

