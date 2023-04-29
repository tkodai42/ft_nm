#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
  char			*_dest = dst;
  const char	*_src = src;

  while (len-- > 0)
    *_dest++ = *_src++;
  return dst;
}
