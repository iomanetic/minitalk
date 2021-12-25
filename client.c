/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuuki <tyuuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:46:29 by tyuuki            #+#    #+#             */
/*   Updated: 2021/12/25 02:06:16 by tyuuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	valid_pid(char *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		if (pid[i] >= '0' && pid[i] <= '9')
			i++;
		else
		{
			ft_putstr_fd("NON VALID FORMAT FOR PID\n", 1);
			exit(0);
		}
	}
	return (1);
}

int	check_kill(int pid, int sig)
{
	if ((kill(pid, sig)))
	{
		ft_putstr_fd("PLEASE RECHECK PID\n", 1);
		exit(0);
	}
	return (0);
}

void	ft_action(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR2)
		ft_putstr_fd("Message send!\n", 1);
}

void	ft_send_bit(int pid, char *str)
{
	char	symb;
	int		i;

	while (*str)
	{
		symb = *str++;
		i = 8;
		while (i--)
		{
			if (symb >> i & 1)
				check_kill(pid, SIGUSR2);
			else
				check_kill(pid, SIGUSR1);
			usleep(50);
		}
	}
	i = 8;
	while (i--)
	{
		check_kill(pid, SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	signal;

	if (argc == 3 && valid_pid(argv[1]) && ft_strlen(argv[2]) > 0)
	{
		signal.sa_flags = SA_SIGINFO;
		signal.sa_sigaction = ft_action;
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
		ft_send_bit(ft_atoi(argv[1]), argv[2]);
	}
	else
		ft_putstr_fd("PLEASE RECHECK YOUR PARAMS\n", 1);
	return (0);
}
