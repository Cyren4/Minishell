/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 18:20:22 by cramdani          #+#    #+#             */
/*   Updated: 2021/11/12 17:45:31 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*create_env(char *name, char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->content = ft_strdup(content);
	new->next = NULL;
	return (new);
}

void	maj_env(t_gen *data, char *name, char *content)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(content);
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		add_env(data, create_env(name, content));
}

void	maj_pwd(t_gen *data)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return ;
	maj_env(data, "OLDPWD", get_env_var(data, "PWD"));
	maj_env(data, "PWD", cwd);
}

int	cd_home(t_gen *data)
{
	char	*home;
	
	home = get_var_exist(data, "HOME");
	if (home == NULL)
		print_error("cd: HOME not set\n", NULL, NULL);
	else if (chdir(ft_strdup(home)) == -1)
		print_error("cd: ", home, ": No such file or directory\n");
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	cd_OLDPATH(t_gen *data)
{
	char	*oldPWD;
	
	oldPWD = get_var_exist(data, "OLDPWD");
	if (oldPWD == NULL)
		print_error("cd: OLDPWD not set\n", NULL, NULL);
	else if (chdir(ft_strdup(oldPWD)) == -1)
		print_error("cd: ", oldPWD, ": No such file or directory\n");
	else
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int	ft_cd(t_gen *data, t_lexer *dir)
{
	int		ret;

	ret = EXIT_SUCCESS;
	if (dir != NULL && dir->next != NULL)
	{
		print_error("cd: too many arguments\n", NULL, NULL);
		return (1);
	}
	else if (dir == NULL || ft_strcmp(dir->content, "~") == 0)
		ret = cd_home(data);
	else if (dir != NULL && ft_strcmp(dir->content, "-") == 0)
		ret = cd_OLDPATH(data);
	else
		if (chdir(dir->content) == -1)
			print_error("cd: ", dir->content, ": No such file or directory\n");
	if (ret == EXIT_SUCCESS)
		maj_pwd(data);
	return (ret);
}
