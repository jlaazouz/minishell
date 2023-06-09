/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:10 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/06 18:21:44 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// check if there is consecutive character in the string
int	consecutive(char *str, char c)
{
	int	i;
	int	len;

	len = ft_strlen(str) - 1;
	i = 0;
	while (str[i + 1])
	{
		if (str[i] == c && str[i + 1] == c && i + 1 != len)
			return (1);
		i++;
	}
	return (0);
}

// create a new str without the specified character in it
char	*clean_from(char *c, char l)
{
	int		i;
	int		j;
	char	*re;

	i = 0;
	j = 0;
	re = malloc(sizeof(char) * (ft_strlen(c) + 1));
	while (c && c[i])
	{
		if (c[i] != l)
			re[j++] = c[i++];
		else
			i++;
	}
	re[j] = '\0';
	return (re);
}

void	init_vars(t_redir *data)
{
	data->error = 0;
	data->in_fd = 0;
	data->out_fd = 0;
	g_vars.g_exit_status = 0;
}

int	ft_is_file_dir(t_input *list, t_redir *data, t_files *f_data)
{
	struct stat	f_stat;
	int			ret;

	ret = stat(list->redirect->file_name[f_data->i], &f_stat);
	if (!ret)
	{	
		if (S_ISDIR(f_stat.st_mode))
		{
			g_vars.g_exit_status = 1;
			ft_printf("bash: %s: Is a directory\n",
				list->redirect->file_name[f_data->i]);
			data->error = 1;
			return (0);
		}
	}
	return (1);
}

int	check_in_file_permissions(t_input *list, t_redir *data, int i)
{
	if (list->redirect->file_name[i] == NULL)
	{
		ft_error(data, AMBIGUOUS_ERR);
		return (0);
	}
	if (list->redirect->file_name[i][0] == '$')
	{
		ft_error(data, AMBIGUOUS_ERR);
		return (0);
	}
	data->error = 1;
	g_vars.g_exit_status = 1;
	ft_printf("bash: %s: %s\n", list->redirect->file_name[i], strerror(errno));
	return (0);
}
