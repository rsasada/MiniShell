# PowerUpShell by Risasada && jongykim
We rewrite a simple shell


We've named it PowerUpShell, but it's powering down.

# Available options
PowerUpShell runs executables from an absolute, relative or environment PATH (/bin/ls or ls), including arguments or options. ' and " work the same as bash, except for multiline commands.

You can separate commands with ;, as well as use redirections > >> < and pipes |.

Environment variables are handled, like $HOME, including the return code $?.

Finally, you can use Ctrl-C to interrupt and Ctrl-\ to quit a program, as well as Ctrl-D to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for echo, pwd, cd, env, export, unset and exit.


We based the basic design on Bash.

<img width="785" alt="スクリーンショット 2024-05-05 16 31 27" src="https://github.com/rsasada/MiniShell/assets/81406794/00e38f02-fcc6-4450-a266-57e4690aad28">

