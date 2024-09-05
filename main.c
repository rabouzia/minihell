int	main(int ac, char **av, char **envp)
{
	static int	exit_status;
	t_env		*env;
	char		*input;

	(void)ac;
	(void)av;
	env = NULL;
	exit_status = 0;
	init_minishell(envp, &env);
	set_signal_handler();
	while (1)
	{
		input = readline("kashell$> ");
		if (!input)
		{
			exit_shell();
			break ;
		}
		if (!*input)
			continue ;
		else
			add_history(input);
		process_input(input, env, &exit_status);
	}
	return (clear_env(env), 0);
}