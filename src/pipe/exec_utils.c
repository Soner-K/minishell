/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/16 14:52:00 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_child(t_exec **cmds_list, char **env_copy)
{
	if (getfile(cmds_list))
	{
		only_redirection(cmds_list);
		if (parse_path((*cmds_list)->cmd_array, (*cmds_list)->path))
			execve((*cmds_list)->path, (*cmds_list)->cmd_array, env_copy);
		else
			exit(127);
	}
}

void	exec_shell_builtin(t_exec **cmds_list, int builtin_check,
		t_env **env_list)
{
	// if (getfile(cmds_list))
	// {
	// 	only_redirection(cmds_list);
	exec_builtin(builtin_check, cmds_list, env_list);
	// }
}

void	exec_shell(t_exec **exec_list, t_env **env_list, char **env_copy,
		t_data *data)
{
	int		builtin_check;
	pid_t	fork_id;
	int		status;

	status = 0;
	// printf("exec_list %s\n", (*exec_list)->cmd_array[0]);
	builtin_check = which_builtin(*exec_list);
	if (builtin_check > 0)
	{
		(*exec_list)->old_stdin = dup(STDIN_FILENO);
		(*exec_list)->old_stdout = dup(STDOUT_FILENO);
		exec_shell_builtin(exec_list, builtin_check, env_list);
		dup2((*exec_list)->old_stdout, STDOUT_FILENO);
		dup2((*exec_list)->old_stdin, STDIN_FILENO);
		close((*exec_list)->old_stdout);
		close((*exec_list)->old_stdin);
	}
	else
	{
		fork_id = fork();
		if (fork_id == 0)
			init_child(exec_list, env_copy);
		wait(&status);
		if (WIFEXITED(status))
		{
			WEXITSTATUS(status);
			printf("status %d\n", status);
			data->exit_status = status;
		}
		// waitpid(fork_id, &status, 0);
		// data->exit_status = status;
	}
}
