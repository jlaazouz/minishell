/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlaazouz < jlaazouz@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:18:07 by jlaazouz          #+#    #+#             */
/*   Updated: 2023/06/06 17:58:20 by jlaazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int	ft_random(void)
{
	static long int	rand;
	char			*p;
	unsigned int	i;

	p = malloc(sizeof(char) * 2);
	i = (unsigned int)p[0];
	rand += ((rand + i) * 1103515245 + 12345) & 0xFFFFFFFF;
	free(p);
	return ((unsigned int)rand);
}

char	*ft_generate_rand_str(int len)
{
	t_rand_str	data;

	ft_strlcpy(data.src,
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
		63);
	data.random_str = (char *)malloc(sizeof(char) * (len + 1));
	data.i = 0;
	data.src_len = sizeof(data.src) - 1;
	while (data.i < len)
	{
		data.random_i = ft_random() % data.src_len;
		data.random_str[data.i++] = data.src[data.random_i];
	}
	data.random_str[data.i] = 0;
	return (data.random_str);
}

void	ft_get_rand_str(t_rand_str *d, t_redir *data, t_input *list)
{
	char	*tmp;

	d->rand_nbr = ft_random() % 63;
	d->ruin_name = ft_generate_rand_str(data->herdoc_count + d->rand_nbr);
	tmp = ft_strjoin("/tmp/", d->ruin_name);
	ft_strlcpy(list->redirect->herdoc_file_name, tmp, 29);
	data->in_fd = open(list->redirect->herdoc_file_name,
			O_CREAT | O_TRUNC, 0644);
	close (data->in_fd);
	free (tmp);
	free(d->ruin_name);
}

void	ft_check_expand(t_input *list, t_redir *data, int *pos, int i)
{
	if (surounded_by(list->redirect->file_name[pos[i]], '\"')
		|| surounded_by(list->redirect->file_name[pos[i]], '\''))
	{
		no_surounded_anymore(&(list->redirect->file_name[pos[i]]));
		data->expand = 0;
	}
}

int	ft_leave_current_heredoc(t_redir *data, int i)
{
	free(data->input);
	data->input = NULL;
	if (i == data->herdoc_count - 1)
		close(data->in_fd);
	return (1);
}
