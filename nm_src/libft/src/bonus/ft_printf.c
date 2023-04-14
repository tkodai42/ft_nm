#include "libft.h"

static char	g_ptf_buffer[1000 + 1];

void	ft_prf_init(t_ft_printf *data, const char *format)
{
	data->wrote_len = 0;
	data->format = format;
}

void	put_buffer(t_ft_printf *data)
{
	if (data->specifiier_type == 's')
		data->wrote_len += write(1, data->str, data->buf_word_size);
	else
		data->wrote_len += write(1, g_ptf_buffer, data->buf_word_size);
}

void	put_field(t_ft_printf *data, int c)
{
	while (data->field_size > 0)
	{
		data->wrote_len += write(1, &c, 1);
		data->field_size--;
	}
}

void	put_section(t_ft_printf *data)
{
	data->field_size -= data->buf_word_size;

	if (FT_PTR_FLAG_NEG(data->flag))
	{
		put_buffer(data);
		put_field(data, ' ');
	}
	else
	{
		if (FT_PTF_FLAG_ZERO(data->flag))
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

void	exec_specifier(t_ft_printf *data)
{
	set_flag(data);
	set_field(data);

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
	data->format++; //skip 'c' | 'd' etc.
}

void	main_loop(t_ft_printf *data)
{
	while (*data->format)
	{
		data->buf_word_size = 0;
		if (*data->format != '%')
		{
			data->wrote_len += write(1, data->format, 1);
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
	ft_prf_init(&data, format);
	va_start(data.ap, format);
	main_loop(&data);
	va_end(data.ap);
	return data.wrote_len;
}

/*
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
}*/
