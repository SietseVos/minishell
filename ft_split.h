/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: svos <svos@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/16 09:59:07 by svos          #+#    #+#                 */
/*   Updated: 2022/05/20 11:16:26 by svos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPLIT_H
# define FT_SPLIT_H
# include <stdlib.h>

char	*putstr(char **s, char c);
char	**ft_split(char *s, char c);

#endif