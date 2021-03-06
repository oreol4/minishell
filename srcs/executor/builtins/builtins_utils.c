/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galetha <galetha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:08:07 by wjonatho          #+#    #+#             */
/*   Updated: 2022/03/03 17:29:05 by galetha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** @param origin: \c 1 for search key_origin, \c 0 for 'fake' key
 * @return \c NULL if can't find location
**/
char	*get_env_value(t_envp *envp, int location)
{
	int		i;
	t_envp	*tmp;

	if (!envp)
		return (NULL);
	i = 0;
	tmp = envp;
	while (tmp)
	{
		if (i == location)
			return (tmp->value);
		i++;
		tmp = tmp->next;
	}
	return (NULL);
}

/** @param origin: \c 1 for search key_origin, \c 0 for 'fake' key
**/
void	upd_env_value(t_envp *envp, char *new_value, int location)
{
	int		i;
	t_envp	*tmp;
	char	*clean;

	if (!envp)
		return ;
	i = 0;
	tmp = envp;
	while (tmp)
	{
		if (i == location)
			break ;
		i++;
		tmp = tmp->next;
	}
	if (tmp)
	{
		clean = tmp->value;
		tmp->value = ft_strdup(new_value);
		if (clean)
			free(clean);
	}
}

/** @param origin: \c 1 for search key_origin, \c 0 for 'fake' key
**/
void	add_to_env(t_envp *envp, char *new_key, char *new_value)
{
	t_envp	*node;
	t_envp	*tmp;

	if (!envp)
		return ;
	node = malloc(sizeof(t_envp));
	if (node == NULL)
		exit(0);
	node->key = ft_strdup(new_key);
	if (new_value)
		node->value = ft_strdup(new_value);
	else
		node->value = NULL;
	node->next = NULL;
	tmp = envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/** @param origin: \c 1 for search key_origin, \c 0 for 'fake' key
 * @return key \c position in list \n
 * \c-1 if fails */
int	locate_env_key(t_envp *envp, char *key)
{
	int		i;
	size_t	key_len;
	t_envp	*tmp;

	i = 0;
	if (!envp)
		return (-2);
	if (!key)
		return (-1);
	key_len = ft_strlen(key);
	tmp = envp;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, key_len + 1) == 0)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (-1);
}

int	ft_count_strings(t_comm *lst)
{
	int	count;

	count = 0;
	while (lst->cmd[count])
		count++;
	return (count);
}
