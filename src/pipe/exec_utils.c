/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/09 12:22:02 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

int	parse_path(char **cmds, char *path)
{
	if (!path || access(path, X_OK | F_OK) != 0)
	{
		printf("%s: Command not found\n", cmds[0]);
		return (0);
	}
	else
	{
		return (1);
	}
}

int	init_child(t_parse **cmds_list, char **env_copy)
{
	if (getfile(cmds_list))
	{
		only_redirection(cmds_list);
		if (parse_path((*cmds_list)->cmd_array, (*cmds_list)->path))
		{
			execve((*cmds_list)->path, (*cmds_list)->cmd_array, env_copy);
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

void	exec_shell_builtin(t_parse **cmds_list, int builtin_check,
		t_env **env_list, t_data *data)
{
	if (getfile(cmds_list))
	{
		only_redirection(cmds_list);
		exec_builtin(builtin_check, cmds_list, env_list, data);
	}
}

void	exec_shell(t_parse **cmds_list, t_env **env_list, char **env_copy,
		t_data *data)
{
	int		builtin_check;
	pid_t	fork_id;
	int		status;
	int		result;

	status = 0;
	builtin_check = is_builtin(*cmds_list);
	if (builtin_check > 0)
	{
		(*cmds_list)->old_stdin = dup(STDIN_FILENO);
		(*cmds_list)->old_stdout = dup(STDOUT_FILENO);
		exec_shell_builtin(cmds_list, builtin_check, env_list, data);
		dup2((*cmds_list)->old_stdout, STDOUT_FILENO);
		dup2((*cmds_list)->old_stdin, STDIN_FILENO);
		close((*cmds_list)->old_stdout);
		close((*cmds_list)->old_stdin);
	}
	else
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			result = init_child(cmds_list, env_copy);
			free_parse_list(cmds_list);
			free_array(data->all_paths);
			free_env_list(env_list);
			free(data);
			if (result == 1)
				exit(127);
			else
				exit(0);
		}
		waitpid(fork_id, &status, 0);
		data->exit_status = WEXITSTATUS(status);
	}
}
