# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFSIZE 4096

// In case of I've made the encryption function as well
//
// static void	encode(unsigned char *str)
// {
// 	unsigned char i = 0;

// 	if (!str && !*str)
// 		return ;
// 	dprintf(STDOUT_FILENO, "Before: |%s|\n", str);
// 	while (str[i])
// 	{
// 		str[i] = str[i] + i;
// 		i++;
// 	}
// 	dprintf(STDOUT_FILENO, "After:  |%s|\n", str);
// 	return ;
// }

static void	decode(unsigned char *str)
{
	unsigned char i = 0;

	if (!str && !*str)
		return ;
	dprintf(STDOUT_FILENO, "Before: |%s|\n", str);
	while (str[i])
	{
		str[i] = str[i] - i;
		i++;
	}
	dprintf(STDOUT_FILENO, "After:  |%s|\n", str);
	return ;
}

static int readAllFromSTDIN(char **str)
{
	ssize_t	readed	= 1;
	char	*tmp	= NULL;
	unsigned int	offset	= 0;

	if ((tmp = malloc(sizeof(char) * BUFSIZE + 1)) == NULL)
	{
		*str = NULL;
		dprintf(STDERR_FILENO, "Error when allocating memory dynamicaly.\n");
		return EXIT_FAILURE; 
	}
	while (readed > 0 && (BUFSIZE - offset != 0) )
	{
		readed = read(STDIN_FILENO, tmp + offset, BUFSIZE - offset);
		dprintf(STDERR_FILENO, "RETURN = %zd\n", readed);
		if (readed < 0)
		{
			dprintf(STDERR_FILENO, "Something went wrong when reading from standard input.\n");
			free(tmp);
			return EXIT_FAILURE;
		}
		offset += readed;
	}
	*str = tmp;
	if (readed != 0)
	{
		dprintf(STDERR_FILENO, "Message too long, the input will be truncated\n");
		*str[readed] = '\0';
	}
	return EXIT_SUCCESS;
}


/*
** Usage: ./reverse [string]\n
** If no arguments is given then the program will read from STDIN.
*/
int main(int ac, char **av)
{
	char	*str	= NULL;
	int		ret		= 0;

	if (ac > 2)
	{
		dprintf(STDOUT_FILENO, "Usage:\n\t./reverse [string]\n\n");
		return 1;
	}
	else if (ac == 1)
	{
		ret = readAllFromSTDIN(&str);
		if (ret == EXIT_FAILURE)
			return EXIT_FAILURE;
		
	}
	else
		str = av[1];

	decode((unsigned char*) str);
	if (ac == 1 && str != NULL)
		free(str);
	return 0;
}