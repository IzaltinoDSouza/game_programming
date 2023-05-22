#pragma once

#include <cstddef>
#include "grid.h"

namespace TicTacToe
{
	enum class State
	{
		NONE,
		X_WIN,
		O_WIN,
		DRAW
	};

	State check_state_winner_or_draw(const Grid & grid)
	{
		//grid is full with X and O
		if(grid.no_more_available()) return State::DRAW;
		
		//horizontal
		for(size_t y = 0;y < 3;++y)
		{
			if(grid.get_mark(y,0) == grid.get_mark(y,1) &&
			   grid.get_mark(y,0) == grid.get_mark(y,2))
			{
				if(grid.get_mark(y,0) == Marks::X)      return State::X_WIN;
				else if(grid.get_mark(y,0) == Marks::O) return State::O_WIN;
				
			}
		}

		//vertical
		for(size_t x = 0;x < 3;++x)
		{
			if(grid.get_mark(0,x) == grid.get_mark(1,x) &&
			   grid.get_mark(0,x) == grid.get_mark(2,x))
			{
				if(grid.get_mark(0,x) == Marks::X)      return State::X_WIN;
				else if(grid.get_mark(0,x) == Marks::O) return State::O_WIN;
			}
		}

		//diagonal 1
		if(grid.get_mark(0,0) == grid.get_mark(1,1) &&
		   grid.get_mark(0,0) == grid.get_mark(2,2))
		{
			if(grid.get_mark(0,0) == Marks::X)      return State::X_WIN;
			else if(grid.get_mark(0,0) == Marks::O) return State::O_WIN;
			
		}
		//diagonal 2
		if(grid.get_mark(0,2) == grid.get_mark(1,1) &&
		   grid.get_mark(0,2) == grid.get_mark(2,0))
		{
			if(grid.get_mark(0,2) == Marks::X)       return State::X_WIN;
			else if(grid.get_mark(0,2) == Marks::O)  return State::O_WIN;
		}
		
		return State::NONE;
	}
}
