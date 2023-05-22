#pragma once

#include "grid.h"
#include <cstddef>

namespace TicTacToe
{
	void ai_brute_force(TicTacToe::Grid & grid)
	{
		ai_try_again:
			
		srand(time(NULL));
		size_t x = rand() % 3;
		srand(time(NULL));
		size_t y = rand() % 3;
		
		if(grid.is_available(x,y))
		{
			grid.set_mark(x,y,TicTacToe::Marks::O);
		}else
		{
			if(grid.no_more_available()) return;
			goto ai_try_again;
		}
	}
}
