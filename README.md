# ⭐ MINIHSELL by Sumseo and Sokaraku ⭐
The goal of this project is to recreate a basic shell, with few functionnalities, such as pipes, redirections, here_doc...

The shell that we are aiming is based on "BASH". 

# How to start the program
1. make : Compile all the files by using the command
2. ./minishell : Launch the program without any arguments. 
3. When you are inside the shell, try some linux commands such as cat, ls, etc.
4. Do not forget to enjoy our minishell :) This is our goal ! 

## Prompt
Prompt is waiting for the uses's touch ⌨️. It waits until user put some commandes and save it to history. And then it sends it to the parsing part. We could make beautiful prompt, but there are errors occuring if we want to change the color.

## Execution
When parsing is done, our minishell program sends the user's "input" to execution part. Then execution part will filter two cases.
1. Built-In commandes : cd, echo, env, exit, export, pwd, unset
2. Normal commandes : all other commandes

The program will execute all above functions in the shell.

## Pipeline
When there are multiple commands by using pipe | (🐱 cat | cat | cat | cat 🐱), the program will handle these cases, too.

Minishell will create multiple processes to execute many commandes. To understand this, you need to to have good understanding regarding process, etc.

## Redirection
If there are infiles or outfiles to read, write or what so more, minishell program will read, or write. Also to have good understand this part, you need to have good understanding of linux file system. Because everytime you use the file, you need to open and close to not have memory leaks in C.

## Exit Status
All commandes return "exit-status". When commande is successfully executed, it returns 0, but if not, it returns non-zero code(1-~255) which could be considered "error code".

| Exit status | Meaning    | Error message    |
| :---:       | :---:      | :---:            |
| 0     | Successfully exectued|              |
| 1     | General errors       | “Operation not permitted” , "not a valid identifier", "too many arguments", etc      |
| 2     | Builtin errors       | “No such file or directory”, etc        |
| 126   | Permission problems  | "Permission denied", "Is a directory", etc          |
| 127   | Path problems        | “Command not found”, “No such file or directory”, etc         |
| 130   | Fatal error(ctrl+c)  | "Script terminated by Ctrl+C”,etc       |
| 255   | exit with out of range(0~255)  | "numeric argument required"|
</br>

So whenever we execute the commande in the minishell, we would like to know this execution is succesfully done in our program. Or maybe, it was not correctly executed because of several reasons such as not finding path, etc. So to know this "status", there are ways to find out it. 

But in reality, we can not control all error status code and even error messages in our minishell. To do so, we are going to use "strerror" functin which is allowed in the minishell project.

## Signal
What is signal, by the way ? 🤔
<br/> Signal is a literally sending "signal" to processes when there are certain events in the terminal(ctrl+c, ctrl+d, etc) Meaning, it is a way to communicate between process.

So when process gets signals, there are three scenarios.
1. Terminate process
2. Ignore process
3. Call signal-handler

In our minishell, we decided to interprept some of signal handlers(ctrl+c, ctrl+d, ctrl+\\). So whenever this event happens on the minishell, you will see the difference and the similarities compared to original shell or bash. 