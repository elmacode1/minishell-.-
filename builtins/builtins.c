#include "../minishell.h"


void init_builtin(t_shell *shell)
{
    shell->builtinds[0] = (t_builtin){"echo", &ft_echo};
    shell->builtinds[1] = (t_builtin){"cd", &ft_cd};
    shell->builtinds[2] = (t_builtin){"pwd", &ft_pwd};
    shell->builtinds[3] = (t_builtin){"export", &ft_export};
    shell->builtinds[4] = (t_builtin){"unset", &ft_unset};
    shell->builtinds[5] = (t_builtin){"env", &ft_env};
    shell->builtinds[6] = (t_builtin){"exit", &ft_exit};
    shell->builtinds[7] = (t_builtin){NULL, NULL};
}