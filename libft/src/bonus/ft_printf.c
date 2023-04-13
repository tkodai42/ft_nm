#include "libft.h"


void	ft_prf_init(t_ft_printf *data, const char *format)
{
	data->wrote_len = 0;
	data->format = format;
}

void	exec_c(t_ft_printf *data)
{
	if (data->specifiier_type == 'c')
		
}

void	exec_specifier(t_ft_printf *data)
{
	if (*data->format == '\0')
		return ;
	data->specifiier_type = *data->format;//set format type
	if (*data->format == 'c' || *data->format == '%')
		exec_c(data);
	
	format++;
}

void	main_loop(t_ft_printf *data)
{
	while (*data->format)
	{
		if (*data->format != '%')
		{
			data->wrote_len += write(1, data->format, 1);
			data->format++;
		}
		else // *formet == '%'
		{
			data->format++;//skip '%'
			data->exec_specifier(data);
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

int		main()
{
	ft_printf("asdf\n");
}
