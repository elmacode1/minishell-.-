
export "test=pp"  (should not work)//but its working in bash
\\export VAR$=value 	(should not work)
\\export SPECIAL="!@#\$%^&*()"  (it shows only !@#\) (must handle the \)
\\export VAR1="hello world" VAR2='single quoted $HOME' VAR3="mix: \$USER and '$SHELL'" VAR4=unquoted123 VAR5="spaces   and            tabs"
\\	mkdir -p test_env/dir1/dir2/dir3
	minishell$ cd test_env
	minishell$ printf '#!/bin/bash\necho Hello from script\n' > myscript.sh
	minishell$ chmod +x myscript.sh
	minishell$ ./myscript.sh
	minishell: ./myscript.sh cmd not found (is should display "hello from script")
	(If a command contains a /, your shell must not search in the PATH — it must try to execute it as-is using execve().)
\\

minishell$ echo "hey"$="ok"
hey $= ok
minishell$ echo "jpo"ll'hello=p'
jpo ll hello=p