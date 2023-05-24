#pragma once

#include "grid.h"

#include <cstddef>
#include <functional>
#include <limits>
#include <fmt/core.h>

namespace TicTacToe
{
	int minimax(Grid & grid,
				int depth,
		        bool is_maximimize,
		        std::function<int(const Grid & grid)> evaluate)
	{
	
		int score = evaluate(grid);
		if(score == +1 || score == 0 || score == -1)
		{
		    return score;
		}
		
		if(is_maximimize)
		{
			int best_score = std::numeric_limits<int>().min();
			
			for(size_t y = 0;y < 3;++y)
			{
				for(size_t x = 0;x < 3;++x)
				{
					if(grid.get_mark(x,y) == Marks::EMPTY)
					{
						grid.set_mark(x,y,Marks::X);
						
						int current_score = minimax(grid,depth+1,false,evaluate);
						
						grid.set_mark(x,y,Marks::EMPTY);
						
						best_score = std::max(best_score,current_score);
					}
				}
			}
			return best_score;
		}else
		{
			int best_score = std::numeric_limits<int>().max();
			for(size_t y = 0;y < 3;++y)
			{
				for(size_t x = 0;x < 3;++x)
				{
					if(grid.get_mark(x,y) == Marks::EMPTY)
					{
						grid.set_mark(x,y,Marks::O);
						
						int current_score = minimax(grid,depth+1,true,evaluate);
						
						grid.set_mark(x,y,Marks::EMPTY);
						
						best_score = std::min(best_score,current_score);
					}
				}
			}
			return best_score;
		}
	}
}
