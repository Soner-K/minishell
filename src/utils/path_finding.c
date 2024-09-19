/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:24:41 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/19 13:14:07 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Joins a directory's path with a command.
 * @param dir A path to a directory.
 * @param cmd The command to look for.
 * @returns <dir>/<cmd>. NULL if there is no dir or no cmd,
 * or if the allocation failed.
 */
static char	*full_path(char *dir, char *cmd)
{
	char	*path;
	size_t	size;

	if (!dir || !cmd)
		return (NULL);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (NULL);
		return (path);
	}
	size = ft_strlen(dir) + ft_strlen(cmd) + 1;
	path = (char *)ft_calloc(size + 2, sizeof(char));
	if (!path)
		return (NULL);
	ft_memcpy(path, dir, ft_strlen(dir));
	path[ft_strlen(dir)] = '/';
	ft_memcpy(path + ft_strlen(dir) + 1, cmd, ft_strlen(cmd));
	path[size] = '\0';
	return (path);
}

/**
 * @brief Finds the PATH variable inside the environment variable,
	and splits it.
 * @param env_list A pointer to an array of environment strings.
 * @returns The splitted path, with the separator being ':'. Returns NULL
 * if the allocation failed or if the PATH variable isn't found.
 */
static char	**split_path(t_env *env_list)
{
	short int	i;
	char		**all_paths;

	i = 0;
	while (env_list)
	{
		if (!ft_strncmp(env_list->variable, "PATH=", 5))
			break ;
		env_list = env_list->next;
	}
	if (!env_list)
		return (NULL);
	// necessary if split returns "" instead of NULL if command not found? COME BACK
	all_paths = ft_split(env_list->variable, ':');
	if (!all_paths)
		return (NULL);
	return (all_paths);
}

/**
 * @brief Finds the path of a given command, if it exists.
 * @param cmd The command for which to look for a path.
 * @param env_list Minishell's environment variable.
 * @param alloc_fail A pointer to a boolean taking the value 1 if
 * an allocation error occured, and 0 otherwise.
 * @returns The path of a given command if it exists, and NULL otherwise.
 */
static char	*find_path(char *cmd, t_env *env_list, bool *alloc_fail)
{
	char		**all_paths;
	char		*cmd_path;
	short int	i;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	all_paths = split_path(env_list);
	if (!all_paths)
		return (*alloc_fail = 1, NULL);
	i = 0;
	while (all_paths[i])
	{
		cmd_path = full_path(all_paths[i], cmd);
		if (!cmd_path)
			return (free_arrs((void **)all_paths), *alloc_fail = 1, NULL);
		if (!access(cmd_path, F_OK | X_OK))
			return (free_arrs((void **)all_paths), *alloc_fail = 0, cmd_path);
		i++;
		free(cmd_path);
	}
	free_arrs((void **)all_paths);
	*alloc_fail = 0;
	return (NULL);
}

/**
 * @brief Checks if a command is a builtin or not.
 * @param cmd The string to check.
 * @returns True (1) if the command is a builtin and false (0) otherwise.
 */
bool	check_if_builtin(t_exec *node)
{
	if (!node)
		return (false);
	if (is_builtin(node->cmd_array[0]))
		return (true);
	return (false);
}

/**
 * @brief Checks for all the nodes in the exec list if there are
 * commands. If a command is found, the path to the executable
 * is found.
 * @param head The head of the tokens list.
 * @param env_list Minishell's environment variable.
 * @returns -1 if an allocation failure occured, 0 if head is NULL and 1
 * if the list was successfully iterated through.
 */
__int8_t	find_cmd_type(t_exec *head, t_env *env_list)
{
	char	*str;
	bool	allocation_fail;

	if (!head)
		return (0);
	allocation_fail = 1;
	while (head)
	{
		if (check_if_builtin(head))
		{
			head = head->next;
			continue ;
		}
		str = find_path(head->cmd_array[0], env_list, &allocation_fail);
		if (!str && allocation_fail)
			return (free_exec(head, false), ALLOCATION_FAILURE); // proteger pour malloc
		if (str && !access(str, F_OK && X_OK))
			head->path = str;
		else if (str)
			free(str);
		head = head->next;
	}
	return (1);
}
