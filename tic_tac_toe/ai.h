#pragma once

#include "grid.h"
#include "state.h"
#include "minimax.h"
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
	void ai_minimax(TicTacToe::Grid & grid)
	{
		auto evaluate = [](const Grid & grid)
		{
			switch(check_state_winner_or_draw(grid))
			{
				case TicTacToe::State::DRAW:
					return 0;
				break;
				case TicTacToe::State::X_WIN:
					return 1;
				break;
				case TicTacToe::State::O_WIN:
					return -1;
				break;
			}
			return 2;
		};
		
		int best_score = std::numeric_limits<int>().min();
		size_t best_x{};
		size_t best_y{};
		
		for(size_t y = 0;y < 3;++y)
		{
			for(size_t x = 0;x < 3;++x)
			{
				if(grid.get_mark(x,y) == Marks::EMPTY)
				{
					grid.set_mark(x,y,Marks::O);

					int move_score = minimax(grid,0,false,evaluate);

					grid.set_mark(x,y,Marks::EMPTY);

					if(move_score > best_score)
					{
						best_score = move_score;

						best_x = x;
						best_y = y;
					}
				}
			}
		}
		grid.set_mark(best_x,best_y,Marks::O);
	}
}
