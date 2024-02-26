/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:51:17 by asamuilk          #+#    #+#             */
/*   Updated: 2024/02/26 22:32:52 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_signal(int pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		ft_putendl_fd("kill error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

static void	signal_handler(int signal, siginfo_t *info, void *ucontext)
{
	static sig_atomic_t	i = 0;
	static sig_atomic_t	letter = 0;

	(void)ucontext;
	if (i ++ < BITS_IN_BYTE)
	{
		if (signal == SIGUSR1)
			letter = letter * 2 + 1;
		else
			letter *= 2;
	}
	if (i == BITS_IN_BYTE)
	{
		if (letter)
			ft_putchar_fd(letter, STDOUT_FILENO);
		else
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			send_signal(info->si_pid, SIGUSR2);
		}
		i = 0;
		letter = 0;
	}
	send_signal(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	ft_printf("I am the server. My process ID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
