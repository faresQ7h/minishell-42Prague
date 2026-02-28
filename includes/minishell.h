/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farmoham <farmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:19:38 by farmoham          #+#    #+#             */
/*   Updated: 2026/02/28 16:21:11 by farmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* ================== GLOBAL (ONLY ONE ALLOWED) ================== */
extern volatile sig_atomic_t	g_sig;

/* ================== ENV ================== */
typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

/* ================== SHELL STRUCT ================== */
typedef struct s_shell
{
	t_env						*env;
	int							exit_status;
	pid_t						last_pid;
	struct s_command			*cmds_head;
}								t_shell;

/* ================== TOKEN ================== */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}								t_token_type;

typedef struct s_token
{
	char						*value;
	t_token_type				type;
	struct s_token				*next;
}								t_token;

/* ================== COMMAND ================== */
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int				quoted;
	int				read_fd;
	struct s_redir	*next;
}								t_redir;

typedef struct s_command
{
	char						*cmd;
	char						**args;
	t_redir						*redirs;
	struct s_command			*next;
}								t_command;

/* ================== HELPER FOR EXPANDER ONLY ================== */
typedef struct s_expand
{
	char						*str;
	char						*result;
	t_env						*env;
	int							last_status;
	int							i;
	int							single;
	int							double_q;
}								t_expand;

/* ================== PROTOTYPES ================== */

/* core */
void							prompt_loop(t_shell *shell);

/* lexer*/
t_token							*lexer(char *line);

/*lexer_extract*/
char							*extract_word(char *line, int *i);
t_token_type					get_type(char *s);

/*lexer_token*/
int								add_token(t_token **head, char *value,
									t_token_type type);
int								is_operator(char c);
int								is_space(char c);
char							*handle_operator(char *line, int *i);

/*parser*/
int								parser(t_token *tokens, t_command **commands);

/*parser utils*/
int								is_quoted(char *s);
char							*strip_quotes(char *s);
int								handle_pipe(t_token **tok, t_command **current);
int								handle_redirection(t_token **tok,
									t_command *cmd);
int								final_validation(t_command *current);

/*command utils*/
t_command						*new_command(void);
int								add_argument(t_command *cmd, char *value);
int								add_redirection(t_command *cmd, int type,
									char *file, int quoted);
void							free_redirs(t_redir *redir);
void							free_commands(t_command *cmd);

/* expander */
void							expander(t_command *cmds, t_shell *s);
char							*expand_string(char *str, t_env *env,
									int last_status);

/* expand utils */
void							expand_variable(t_expand *e);

/* heredoc */
int								process_heredocs(t_command *cmds,
									t_shell *shell);

/* executor */
void							executor(t_command *cmds, t_shell *s);

/* executor_utils */
int								fork_process(t_command *cmd, t_shell *s,
									int prev_fd, int pipe_fd[2]);
void							parent_fds(int *prev_fd, int pipe_fd[2],
									int has_next);

/* wait */
void							wait_children(t_shell *s);

/* path_finder */
char							*get_path(char *cmd, t_env *env);

/* redirections */
int								apply_redirections(t_command *cmd);

/* builtins */
int								is_builtin(char *cmd);
int								builtin_echo(char **argv);
int								builtin_env(t_env *env);
int								exec_builtin(t_command *cmd, t_shell *s);
int								builtin_export(char **argv, t_env **env);

/* env */
t_env							*env_new(char *key, char *value);
int								env_size(t_env *env);
t_env							*env_init(char **envp);
void							env_add_from_envp(t_env **env, char *entry);
char							*env_get(t_env *env, char *key);
void							env_set(t_env **env, char *key, char *value);
void							env_unset(t_env **env, char *key);
char							**env_to_array(t_env *env);
int								valid_identifier(char *key);

/*Free functions*/
void							free_env(t_env *env);
void							free_tokens(t_token *head);
void							free_args(char **args);
void							free_str(char **s);

/* signals */
void							init_signals_interactive(void);
void							init_signals_child(void);
void							init_signals_exec(void);

/* utils */
int								is_empty(char *s);
char							*ft_strjoin_char(char *s, char c);
int								ft_strcmp(const char *s1, const char *s2);
char							*append_str(char *s1, char *s2);

#endif

// BUGE
// some export new variable error
