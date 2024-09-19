#! /bin/bash
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=ignore_readline.supp  ./minishell