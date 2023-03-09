#include "shell.h"

void	default_in_out(int *in, int *out, struct s_state *state)
{
	if (!state->in_set)
		*in = 0;
	if (!state->out_set)
		*out = 1;
}
