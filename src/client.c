/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:51:23 by asamuilk          #+#    #+#             */
/*   Updated: 2024/02/26 22:28:16 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_signal_received;

static void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		g_signal_received = 1;
	else
		exit(EXIT_SUCCESS);
}

static void	send_signal(int pid, int signal)
{
	g_signal_received = 0;
	if (kill(pid, signal) == -1)
	{
		ft_putendl_fd("kill error", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	while (!g_signal_received)
		pause();
}

static void	send_message(int pid, char *message)
{
	int	i;

	while (*message)
	{
		i = BITS_IN_BYTE;
		while (i--)
		{
			if (*message & (1 << i))
				send_signal(pid, SIGUSR1);
			else
				send_signal(pid, SIGUSR2);
		}
		message ++;
	}
	i = BITS_IN_BYTE;
	while (i--)
		send_signal(pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	int				pid;
	char			*message;

	if (ac != 3)
		ft_putendl_fd("Please, enter process id and the message.", STDERR_FILENO);
	else
	{
		pid = ft_atoi(av[1]);
		message = av[2];
		if (pid <= 1)
			ft_putendl_fd("Wrong process id!", STDERR_FILENO);
		else
		{
			signal(SIGUSR1, signal_handler);
			signal(SIGUSR2, signal_handler);
			while (1)
				send_message(pid, message);
		}
	}
}
