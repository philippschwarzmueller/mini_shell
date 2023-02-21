#include <stdio.h>
#include <readline/readline.h>

int	main(void)
{
	while (1)
	{
		readline("\033[0;31msigmashell \033[0;32m> \033[0;37m");
	}
}
