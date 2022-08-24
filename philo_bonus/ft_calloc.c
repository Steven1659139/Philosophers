#include "philo_bonus.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptrb;

	ptrb = b;
	while (len-- > 0)
		*ptrb++ = (unsigned char)c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtn;

	rtn = malloc(count * size);
	if (!rtn)
		return (NULL);
	ft_bzero(rtn, count * size);
	return (rtn);
}