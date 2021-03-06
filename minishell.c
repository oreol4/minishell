/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galetha <galetha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:46:09 by wjonatho          #+#    #+#             */
/*   Updated: 2022/03/03 18:23:39 by galetha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process4(char *str, t_envp **list_env)
{
	t_comm	*lst;
	char	**new_env;

	lst = NULL;
	new_env = ft_update_env(*list_env);
	lst = ft_parser4(lst, str, *list_env);
	if (lst == NULL)
	{
		if (new_env)
			clean_env(new_env);
		remove_all_list(lst);
		return (0);
	}
	if (executor(&lst, new_env) == -1)
		return (-1);
	if (new_env)
		clean_env(new_env);
	*list_env = lst->e;
	remove_all_list(lst);
	return (0);
}

void	ft_up_shlvl(t_envp *list_env)
{
	t_envp	*head;
	int		shlvl;
	char	*tmp;
	int		locate;

	locate = 0;
	head = list_env;
	locate = locate_env_key(head, "SHLVL");
	if (locate == -1)
		add_to_env(list_env, "SHLVL", "1");
	else
	{
		shlvl = ft_atoi(get_env_value(list_env, locate)) + 1;
		tmp = ft_itoa(shlvl);
		upd_env_value(list_env, tmp, locate);
		if (tmp)
			free(tmp);
	}
}

int	ft_support_circle(char *str, int *i, t_envp **list_env)
{
	if (ft_is_space(str, i) == -1)
	{
		free (str);
		return (-1);
	}
	if (ft_lexer(str) != -1)
	{
		if (ft_process4(str, list_env) == -1)
			exit(0);
	}
	else
		free (str);
	return (0);
}

int	ft_main_circle(char *str, t_envp **list_env)
{
	int	i;

	i = 0;
	str = readline("bash:");
	if (str && *str)
	{
		if (ft_support_circle(str, &i, list_env) == -1)
			return (0);
	}
	else if (str == NULL)
	{
		write(1, "exit\n", 5);
		remove_all_env_list(*list_env);
		exit(0);
	}else{
		free (str);
	}
	return (0);
}

int	main(void)
{
	char		*str;
	t_envp		*list_env;
	extern char	**environ;

	str = NULL;
	list_env = NULL;
	list_env = ft_node_env(list_env, environ);
	ft_up_shlvl(list_env);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		ft_main_circle(str, &list_env);
	}
	remove_all_env_list(list_env);
	return (0);
}
