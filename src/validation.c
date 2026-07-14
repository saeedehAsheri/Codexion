#include "../includes/codexion.h"

int	get_scheduler(const char *str, t_scheduler *scheduler)
{
	if (!str || !scheduler)
		return (0);
	if (strcmp(str, "fifo") == 0)
	{
		*scheduler = FIFO;
		return (1);
	}
	if (strcmp(str, "edf") == 0)
	{
		*scheduler = EDF;
		return (1);
	}
	return (0);
}

int	parse_integer(const char *str, int *result, int allow_zero)
{
	int	number;
	int	digit;
	int	i;

	if (!str || str[0] == '\0' || !result)
		return (0);
	number = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = str[i] - '0';
		if (number > (INT_MAX - digit) / 10)
			return (0);
		number = number * 10 + digit;
		i++;
	}
	if (!allow_zero && number == 0)
		return (0);
	*result = number;
	return (1);
}
