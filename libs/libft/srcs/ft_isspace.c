/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/24 16:22:32 jsalmi
 * Updated: 2021/07/03 09:05:50 jsalmi
 */

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == '\n');
}
