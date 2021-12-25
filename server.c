/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuuki <tyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:46:38 by tyuuki            #+#    #+#             */
/*   Updated: 2021/12/25 02:10:47 by tyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_accept_bits(int sig, siginfo_t *info, void *context)
{
	static char	symb = 0;
	static char	i = 0;

	(void)context;
	symb |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!symb)
		{
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		ft_putchar_fd(symb, 1);
		symb = 0;
		kill(info->si_pid, SIGUSR1);
	}
	else
		symb <<= 1;
}

int	main(void)
{
	struct sigaction	signal;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	signal.sa_flags = SA_SIGINFO;
	signal.sa_sigaction = ft_accept_bits;
	if ((sigaction(SIGUSR1, &signal, 0)))
	{
		ft_putstr_fd("ERROR SIGNAL\n", 1);
		exit(0);
	}
	if ((sigaction(SIGUSR2, &signal, 0)))
	{
		ft_putstr_fd("ERROR SIGNAL\n", 1);
		exit(0);
	}
	while (1)
		pause();
	return (0);
}
