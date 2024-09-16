/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:47:58 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/16 15:51:59 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# define MKO "Allocation issue\n"
# define ALLOCATION_FAILURE -1
# define UNCLOSED_QUOTES -2
# define SYNTAX_ERROR -3

# define SUCCESS 1
# define FAILURE 0

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

# define NO_FILE_FOUND -1
# define NO_RIGHT 0
# define EXECUTE_ONLY 1
# define WRITE_ONLY 2
# define WRITE_EXECUTE 3
# define READ_ONLY 4
# define READ_EXECUTE 5
# define READ_WRITE 6
# define READ_WRITE_EXECUTE 7

# define CLOSED_QUOTES_CHECK 1
# define QUOTES_MARKING_MODE 2
# define QUOTES_REMOVING_MODE 3

#endif