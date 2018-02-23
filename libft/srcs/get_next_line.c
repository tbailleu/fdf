/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 14:43:39 by tbailleu          #+#    #+#             */
/*   Updated: 2017/12/29 11:58:32 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		get_first_line(const int fd, char ***savedlines, char **line)
{
	char	*nl_pos;

	if ((nl_pos = ft_strchr((*savedlines)[fd], (int)'\n')))
	{
		*line = ft_strsub((*savedlines)[fd], 0, nl_pos - (*savedlines)[fd]);
		ft_memmove((*savedlines)[fd], nl_pos + 1, ft_strlen(nl_pos));
		nl_pos = NULL;
		return (1);
	}
	return (0);
}

int		read_fd_save_lines(const int fd, char ***savedlines, char **line)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;

	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (savedlines && *savedlines && (*savedlines)[fd])
			(*savedlines)[fd] = ft_strjoinfree((*savedlines)[fd], buff);
		else
			(*savedlines)[fd] = ft_strdup(buff);
		if (get_first_line(fd, savedlines, line))
			return (1);
	}
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	static char	**savedlines = NULL;

	if (!savedlines)
		if (!(savedlines = (char **)ft_memalloc(FD_MAX)))
			return (-1);
	if (fd < 0 || read(fd, 0, 0) == -1 || !line || BUFF_SIZE < 1 || fd > FD_MAX)
		return (-1);
	if (savedlines && savedlines[fd] && get_first_line(fd, &savedlines, line))
		return (1);
	if ((ret = read_fd_save_lines(fd, &savedlines, line)) != 0)
		return (ret);
	if (savedlines[fd] == NULL || savedlines[fd][0] == '\0')
		return (0);
	*line = savedlines[fd];
	savedlines[fd] = NULL;
	return (1);
}
