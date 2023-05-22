#pragma once
#include <cstddef>

namespace TicTacToe
{
	enum class Marks
	{
		EMPTY,
		X,
		O
	};
	class Grid
	{
	public:
		Grid()
		{
			reset();
		}
		void reset()
		{
			for(size_t y = 0;y < 3;++y)
			{
				for(size_t x = 0;x < 3;++x)
				{
					m_grid[y][x] = Marks::EMPTY;
				}
			}
		}
		void set_mark(size_t offset,Marks mark)
		{
			m_grid[(offset-1) % 3][(offset-1) / 3] = mark;
		}
		void set_mark(size_t x,size_t y,Marks mark)
		{
			m_grid[y][x] = mark;
		}
		Marks get_mark(size_t x,size_t y) const
		{
			return m_grid[y][x];
		}
		bool is_available(size_t offset) const
		{
			return m_grid[(offset-1) % 3][(offset-1) / 3] == Marks::EMPTY;
		}
		bool is_available(size_t x,size_t y)
		{
			return m_grid[y][x] == Marks::EMPTY;
		}
		bool no_more_available() const
		{
			size_t total = 0;
			for(size_t y = 0;y < 3;++y)
			{
				for(size_t x = 0;x < 3;++x)
				{
					if(m_grid[y][x] != Marks::EMPTY)
						++total;
				}
			}
			return total == 3*3;
		}
	private:
		Marks m_grid[3][3];
	};
}
