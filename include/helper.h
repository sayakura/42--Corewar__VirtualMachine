/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 08:27:46 by qpeng             #+#    #+#             */
/*   Updated: 2019/07/22 08:47:12 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  HELPER_H
#define HELPER_H

#include <unistd.h>
// #include "corewar/process.h"

void	ft_putchar(char c);
void    h_rev_bytes(void *ptr, size_t n);
// void    h_print_register(t_process *cp);
void	h_puthex(unsigned char c);

#endif // ! HELPER_H
