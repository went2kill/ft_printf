/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_for_xx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrobotko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 18:48:53 by yrobotko          #+#    #+#             */
/*   Updated: 2017/08/08 18:48:57 by yrobotko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int app_flags_xx(int size,char *strn, t_print* ls)
{
    int size1;
    int size2;
    char *fl;
    
    fl = ls->flags;
    size1 = (int)ft_strlen(strn);
    if (fl[3] == '1'){
        if ((size < ls->width || size < ls->precision)){
            size2 = 0;
            while (!ft_isdigit(strn[size2]))
                size2++;
            if (ls->convers == 'x')
                strn[--size2 - 1] = 'x';
            else
                strn[--size - 1] = 'X';
            strn[size2 - 2] = '0';
            size += 2;
        }
        else if (ls->convers == 'x')
            strn = ft_strjoin("0x", strn);
        else
            strn = ft_strjoin("0X", strn);
    }
    if (fl[0] == '1') {
        if (size < size1)
            strn = ft_strjoin(&strn[size1 - size], newstr(size1 - size, ' '));
    }
    if (fl[2] == '1' && fl[0] != '1'){
        size1 = 0;
        if (ls->prec_fl == 0)
            while (!ft_isdigit(strn[size1]))
                strn[size1++] = '0';
    }
    ft_putstr(strn);
    return (int)ft_strlen(strn);
}

int apply_w_p_xx(t_print *lst, char *strnum)
{
    int size_n;
    char *str;
    
    size_n = (int)ft_strlen(strnum);
    if (lst->precision > size_n)
        str = ft_strjoin(newstr(lst->precision - size_n, '0'), strnum);
    else
        str = strnum;
    size_n = (int)ft_strlen(str);
    if (lst->width > size_n)
        str = ft_strjoin(newstr(lst->width - size_n, ' '), str);
    return app_flags_xx(size_n, str, lst);
}

int next_step_for_X(t_print *list, va_list ptr)
{
    char *str;
    char c;
    
    c = list->convers;
    if (c == 'X' && list->size == 1)
        str = ft_itoa_base(va_arg(ptr, unsigned long long int), 16, 1);
    else if (c == 'X' && list->size == 2)
        str = ft_itoa_base(va_arg(ptr, unsigned long int), 16, 1);
    else if (c == 'X' && list->size == 3)
        str = ft_itoa_base((unsigned short int)va_arg(ptr, unsigned int), 16, 1);
    else if (c == 'X' && list->size == 4)
        str = ft_itoa_base((unsigned char)va_arg(ptr, unsigned int), 16, 1);
    else if (c == 'X' && list->size == 5)
        str = ft_itoa_base(va_arg(ptr, uintmax_t), 16, 1);
    else if (c == 'X' && list->size == 6)
        str = ft_itoa_base(va_arg(ptr, size_t), 16, 1);
    else
        str = ft_itoa_base(va_arg(ptr, unsigned int), 16, 1);
    return apply_w_p_xx(list, str);
}

int next_step_for_xx(t_print *list, va_list ptr)
{
    char *str;
    char c;
    
    c = list->convers;
    if (c == 'X')
        return next_step_for_X(list, ptr);
    else {
        if (c == 'x' && list->size == 1)
            str = ft_itoa_base(va_arg(ptr, unsigned long long int), 16, 0);
        else if (c == 'x' && list->size == 2)
            str = ft_itoa_base(va_arg(ptr, unsigned long int), 16, 0);
        else if (c == 'x' && list->size == 3)
            str = ft_itoa_base((unsigned short int) va_arg(ptr, unsigned int), 16, 0);
        else if (c == 'x' && list->size == 4)
            str = ft_itoa_base((unsigned char) va_arg(ptr, unsigned int), 16, 0);
        else if (c == 'x' && list->size == 5)
            str = ft_itoa_base(va_arg(ptr, uintmax_t), 16, 0);
        else if (c == 'x' && list->size == 6)
            str = ft_itoa_base(va_arg(ptr, size_t), 16, 0);
        else
            str = ft_itoa_base(va_arg(ptr, unsigned int), 16, 0);
    }
    return apply_w_p_xx(list, str);
}