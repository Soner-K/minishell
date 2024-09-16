/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:24:41 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/16 14:05:58 by sokaraku         ###   ########.fr       */
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
 * @param env A pointer to an array of environment strings.
 * @returns The splitted path, with the separator being ':'. Returns NULL
 * if the allocation failed or if the PATH variable isn't found.
 */
static char	**split_path(char **env)
{
	short int	i;
	char		**all_paths;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	// necessary if split returns "" instead of NULL if command not found? COME BACK
	all_paths = ft_split(env[i], ':');
	if (!all_paths)
		return (NULL);
	return (all_paths);
}

/**
 * @brief Finds the path of a given command, if it exists.
 * @param cmd The command for which to look for a path.
 * @param env The environment variable.
 * @param alloc_fail A pointer to a boolean taking the value 1 if
 * an allocation error occured, and 0 otherwise.
 * @returns The path of a given command if it exists, and NULL otherwise.
 */
char	*find_path(char *cmd, char **env, bool *alloc_fail)
{
	char		**all_paths;
	char		*cmd_path;
	short int	i;

	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	all_paths = split_path(env);
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
bool	check_if_builtin(t_tokens **node)
{
	t_tokens	*prev;

	prev = (*node)->prev;
	if (is_builtin((*node)->word))
	{
		if (!prev)
		{	
			(*node)->type = BUILTIN;
			*node = (*node)->next;
			return (true);
		}
		else if (prev->type != CMD && prev->type != BUILTIN)
		{	
			(*node)->type = BUILTIN;
			*node = (*node)->next;
			return (true);
		}
	}
	return (false);
}
/**
 * @brief Checks for all the tokens in the tokens list if there are
 * commands or builtins. If a command is found, the path to the executable
 * is found.
 * @param head The head of the tokens list.
 * @param env The environment variable.
 * @returns -1 if an allocation failure occured, 0 if head is NULL and 1
 * if the list was successfully iterated through.
 */
__int8_t	find_cmd_type(t_tokens *head, char **env)
{
	char	*str;
	bool	allocation_fail;

	if (!head)
		return (0);
	allocation_fail = 1;
	while (head)
	{
		if (check_if_builtin(&head))
			continue ;
		str = find_path(head->word, env, &allocation_fail);
		if (!str && allocation_fail)
			return (-1); // proteger pour malloc
		if (str && !access(str, F_OK && X_OK) && head->type == WORD)
		{
			head->path = str;
			head->type = CMD;
		}
		else if (str)
			free(str);
		head = head->next;
	}
	return (1);
}