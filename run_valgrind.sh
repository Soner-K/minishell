#! /bin/bash
valgrind --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline.supp  ./minishell