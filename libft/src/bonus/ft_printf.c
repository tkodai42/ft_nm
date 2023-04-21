#include "libft.h"

static char	g_ptf_buffer[1000 + 1];

void	ft_prf_init(t_ft_printf *data, const char *format, int fd)
{
	data->wrote_len = 0;
	data->format = format;
	data->fd = fd;
}

void	put_buffer(t_ft_printf *data)
{
	if (data->specifiier_type == 's')
		data->wrote_len += write(data->fd, data->str, data->buf_word_size);
	else
		data->wrote_len += write(data->fd, g_ptf_buffer, data->buf_word_size);
}

void	put_field(t_ft_printf *data, int c)
{
	while (data->field_size > 0)
	{
		data->wrote_len += write(data->fd, &c, 1);
		data->field_size--;
	}
}

void	resize_precision(t_ft_printf *data)
{
	if (data->specifiier_type == 'x' || data->specifiier_type == 'X')
	{
		int		len = data->precision_size - data->buf_word_size;
		char	*head = g_ptf_buffer;

		ft_memmove(g_ptf_buffer + len, g_ptf_buffer, data->buf_word_size);
		while (head != g_ptf_buffer + len)
			*head++ = '0';
		data->buf_word_size += len;
	}
	if (data->specifiier_type == 'p')
	{
		int		len = data->precision_size - data->buf_word_size;
		char	*head = g_ptf_buffer;
		//2 == "0x"
		ft_memmove(g_ptf_buffer + len + 2, g_ptf_buffer + 2, data->buf_word_size - 2);
		while (head + 2 != g_ptf_buffer + len + 2)
			*head++ = '0';
		data->buf_word_size += len;
	}
}

void	put_section(t_ft_printf *data)
{
	if (FT_PTR_PRECISION(data->flag))
	{
		if (data->buf_word_size > data->precision_size)
			data->buf_word_size = data->precision_size;
		else if (data->buf_word_size < data->precision_size)
			resize_precision(data);
	}
	data->field_size -= data->buf_word_size;

	if (FT_PTR_FLAG_NEG(data->flag))
	{
		put_buffer(data);
		put_field(data, ' ');
	}
	else
	{
		if (FT_PTR_FLAG_ZERO(data->flag))
			put_field(data, '0');
		else
			put_field(data, ' ');
		put_buffer(data);
	}
}

void	exec_d(t_ft_printf *data)
{
	int		num;

	num = va_arg(data->ap, int);
	data->buf_word_size = ft_setnbr(num, g_ptf_buffer);	
	put_section(data);
}

void	exec_s(t_ft_printf *data)
{
	data->str = va_arg(data->ap, char*);
	if (data->str == NULL)
		data->str = "(null)";
	data->buf_word_size = ft_strlen(data->str);	
	put_section(data);
}

void	exec_c(t_ft_printf *data)
{
	if (data->specifiier_type == 'c')
		g_ptf_buffer[0] = va_arg(data->ap, int);	
	else // '%'
		g_ptf_buffer[0] = '%';
	data->buf_word_size = 1;
	put_section(data);
}

void	exec_x(t_ft_printf *data)
{
	int		num;

	num = va_arg(data->ap, int);
	if (*data->format == 'x')
		data->buf_word_size = ft_sethex(num, 0, g_ptf_buffer);
	else //'X'
		data->buf_word_size = ft_sethex(num, 1, g_ptf_buffer);
	data->str = g_ptf_buffer;
	put_section(data);
}

void	exec_p(t_ft_printf *data)
{
	long long	num;

	num = va_arg(data->ap, long long);
	data->buf_word_size = ft_sethex(num, 0, g_ptf_buffer);
	data->str = g_ptf_buffer;
	ft_memmove(g_ptf_buffer + 2, g_ptf_buffer, data->buf_word_size);
	ft_memmove(g_ptf_buffer, "0x", 2);
	data->buf_word_size += 2;
	put_section(data);
}


void	set_flag(t_ft_printf *data)
{
	data->flag = 0;
	int		flag = 1;

	while (*data->format && flag)
	{
		flag = 0;
		if (*data->format == '0')
		{
			data->flag |= FT_PTR_FLAG_ZERO_BIT;
			data->format++;
			flag = 1;
		}
		if (*data->format == '-')
		{
			data->flag |= FT_PTR_FLAG_NEG_BIT;
			data->format++;
			flag = 1;
		}
	}
}

void	set_field(t_ft_printf *data)
{
	data->field_size = 0;
	if (ft_isdigit(*data->format) == 0)
		return ;	
	while (ft_isdigit(*data->format))
	{
		data->field_size = data->field_size * 10 + *data->format - '0';
		data->format++;
	}
}

void	set_precision(t_ft_printf *data)
{
	data->precision_size = 0;
	if (*data->format != '.')//exist precision
		return ;
	data->flag |= FT_PTR_FLAG_PRECISION_BIT;
	data->format++;	
	while (ft_isdigit(*data->format))
	{
		data->precision_size = data->precision_size * 10 + *data->format - '0';
		data->format++;
	}
}


void	exec_specifier(t_ft_printf *data)
{
	set_flag(data);
	set_field(data);
	set_precision(data);

	//specifiier
	if (*data->format == '\0')
		return ;
	data->specifiier_type = *data->format;//set format type
	if (*data->format == 'c' || *data->format == '%')
		exec_c(data);
	if (*data->format == 's')
		exec_s(data);
	if (*data->format == 'd' || *data->format == 'i')
		exec_d(data);
	if (*data->format == 'x' || *data->format == 'X')
		exec_x(data);
	if (*data->format == 'p')
		exec_p(data);
	if (*data->format != '\0')
		data->format++; //skip 'c' | 'd' | ... | specifiier
}

void	main_loop(t_ft_printf *data)
{
	while (*data->format)
	{
		data->buf_word_size = 0;
		if (*data->format != '%')
		{
			data->wrote_len += write(data->fd, data->format, 1);
			data->format++;
		}
		else // *format == '%'
		{
			data->format++;//skip '%'
			if (*data->format == '\0')
				break ;
			exec_specifier(data);
		}
	}
}

int		ft_printf(const char *format, ...)
{
	t_ft_printf	data;

	if (format == NULL || *format == '\0')
		return 0;
	ft_prf_init(&data, format, 1);
	va_start(data.ap, format);
	main_loop(&data);
	va_end(data.ap);
	return data.wrote_len;
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_ft_printf	data;

	if (format == NULL || *format == '\0')
		return 0;
	ft_prf_init(&data, format, fd);
	va_start(data.ap, format);
	main_loop(&data);
	va_end(data.ap);
	return data.wrote_len;
}


#if 0
int		main()
{
	int ret1 = 0;
	int ret2 = 0;
	
	//ret1 = ft_printf("asdf\n");
	//ret2 = printf("asdf\n");

	printf("--- %d %d ---\n", ret1, ret2);

	//ret1 = ft_printf("[%c] [%c] [%c] asdf\n", 0, 'a', 'z');
   	//ret2 = printf("[%c] [%c] [%c] asdf\n", 0, 'a', 'z');

	printf("--- %d %d ---\n", ret1, ret2);

	ret1 = ft_printf("[%05d] [%-10d] [%d] asdf\n", 3, -123, INT_MAX);
   	ret2 = printf("[%05d] [%-10d] [%d] asdf\n", 3, -123, INT_MAX);

	printf("--- %d %d ---\n", ret1, ret2);

	ret1 = ft_printf("[%5s] [%-10s] [%s] asdf\n", "123", "", NULL);
   	ret2 = printf("[%5s] [%-10s] [%s] asdf\n", "123", "", NULL);

	printf("--- %d %d ---\n", ret1, ret2);

	
	ret1 = ft_printf("[%5.s] [%-10.3s] [%s] [%2.5s]asdf\n", "123", "12345", NULL, "123");
   	ret2 =    printf("[%5.s] [%-10.3s] [%s] [%2.5s]asdf\n", "123", "12345", NULL, "123");

	printf("--- %d %d ---\n", ret1, ret2);

	ret1 = ft_printf("[%016x] [%-10x] [%x] [%.4x] [%-10.4x]asdf\n", 3, 123, INT_MAX, 12, 12);
   	ret2 =    printf("[%016x] [%-10x] [%x] [%.4x] [%-10.4x]asdf\n", 3, 123, INT_MAX, 12, 12);

	printf("--- %d %d ---\n", ret1, ret2);

	char	*p1 = "123";

	ret1 = ft_printf("[%18p] [%-10p] [%20p] [%p] [%-10p]asdf\n", p1, &p1, p1, p1, p1);
   	ret2 =    printf("[%18p] [%-10p] [%20p] [%p] [%-10p]asdf\n", p1, &p1, p1, p1, p1);

	printf("--- %d %d ---\n", ret1, ret2);

}
#endif
