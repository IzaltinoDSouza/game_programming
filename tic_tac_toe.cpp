/*
	This is very simple terminal version of tic tac toe
	[1][2][3]
	[4][5][6]
	[7][8][9]
	
	* Single player
	* AI is force brute
*/

#include <cstddef>
#include <fmt/core.h>
#include <iostream>
#include <chrono>
#include <thread>

#ifdef __linux__
#define terminal_clear() system("clear")
#elif __WIN32__
#define terminal_clear() system("cls")
#endif

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
	bool is_available(size_t offset)
	{
		return m_grid[(offset-1) % 3][(offset-1) / 3] == Marks::EMPTY;
	}
	bool is_available(size_t x,size_t y)
	{
		return m_grid[y][x] == Marks::EMPTY;
	}
	bool no_more_available()
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

class TicTacToeTerminal
{
public:
	TicTacToeTerminal()
	 : m_quit{false},
	   m_score1{},
	   m_score2{}
	{
	
	}
	void user_input()
	{
		user_try_again:
		
		char key;
		std::cout << "select a number 1 - 9\n";
		std::cin >> key;
		if(key >= '1' && key <= '9')
		{
			size_t offset = key-'0';
			if(m_grid.is_available(offset))
			{
				m_grid.set_mark(offset,Marks::X);
			}else
			{
				goto user_try_again;
			}
			return;
		}
		
		switch(key)
		{
			case 'q':
				m_quit = true;
			break;
			case 'r':
				m_grid.reset();
				m_score1 = 0;
				m_score2 = 0;
			break;
			case 'h':
				help_menu();
			break;
			default:
				terminal_clear();
			break;
		}
	}
	void ai_input()
	{
		size_t prev_x = 0;
		size_t prev_y = 0;
		
		bool try_again = false;
		
		ai_try_again:
		
		srand(time(NULL));
		size_t x = rand() % 3;
		srand(time(NULL));
		size_t y = rand() % 3;
		
		if(try_again && x == prev_x && y == prev_y)
		{
			x = rand() % 3;
			if(x == prev_x) goto ai_try_again;
			try_again = false;
		}
		
		if(m_grid.is_available(x,y))
		{
			m_grid.set_mark(x,y,Marks::O);
		}else
		{
			try_again = true;
			goto ai_try_again;
		}
	}
	void update()
	{
		if(m_grid.no_more_available())
		{
			m_grid.reset();
		}
	
		//horizontal
		for(size_t y = 0;y < 3;++y)
		{
			if(m_grid.get_mark(y,0) == m_grid.get_mark(y,1) &&
			   m_grid.get_mark(y,0) == m_grid.get_mark(y,2))
			{
				if(m_grid.get_mark(y,0) == Marks::X)
				{
					m_score1 += 1;
					m_grid.reset();
				}else if(m_grid.get_mark(y,0) == Marks::O)
				{
					m_score2 += 1;
					m_grid.reset();
				}
			}
		}
		
		//vertical
		for(size_t x = 0;x < 3;++x)
		{
			if(m_grid.get_mark(0,x) == m_grid.get_mark(1,x) &&
			   m_grid.get_mark(0,x) == m_grid.get_mark(2,x))
			{
				if(m_grid.get_mark(0,x) == Marks::X)
				{
					m_score1 += 1;
					m_grid.reset();
				}else if(m_grid.get_mark(0,x) == Marks::O)
				{
					m_score2 += 1;
					m_grid.reset();
				}
			}
		}
		
		//diagonal 1
		if(m_grid.get_mark(0,0) == m_grid.get_mark(1,1) &&
		   m_grid.get_mark(0,0) == m_grid.get_mark(2,2))
		{
			if(m_grid.get_mark(0,0) == Marks::X)
			{
				m_score1 += 1;
				m_grid.reset();
			}
			else if(m_grid.get_mark(0,0) == Marks::O)
			{
				m_score2 += 1;
				m_grid.reset();
			}
		}
		//diagonal 2
		if(m_grid.get_mark(0,2) == m_grid.get_mark(1,1) &&
		   m_grid.get_mark(0,2) == m_grid.get_mark(2,0))
		{
			if(m_grid.get_mark(0,2) == Marks::X)
			{
				m_score2 += 1;
				m_grid.reset();
			}
			else if(m_grid.get_mark(0,2) == Marks::O)
			{
				m_score2 += 1;
				m_grid.reset();
			}
		}
	}
	void render()
	{
		terminal_clear();
		fmt::print("score : {} | {}\n",m_score1,m_score2);
		for(size_t y = 0;y < 3;++y)
		{
			for(size_t x = 0;x < 3;++x)
			{
				switch(m_grid.get_mark(y,x))
				{
					case Marks::EMPTY:
						fmt::print("[ ]");
					break;
					case Marks::X:
						fmt::print("[X]");
					break;
					case Marks::O:
						fmt::print("[O]");
					break;
				}
				fmt::print(" ");
			}
			fmt::print("\n");
		}
	}
	void help_menu()
	{
		terminal_clear();
		fmt::print("Options:\n"
				   "      [q] to quit\n"
		           "      [r] to reset\n"
		           "      [h] to help\n"
		           "\nTip : don't forget press enter after\n\n\n");
		           
		for(size_t y = 0;y < 3;++y)
		{
			for(size_t x = 0;x < 3;++x)
			{
				fmt::print("[{}]", (y * 3 + x)+1);
				fmt::print(" ");
			}
			fmt::print("\n");
		}
		fmt::print("\n");
		for(size_t i = 0;i < 10;++i)
		{
			//fmt::print("\r\r");
			fmt::print("countdown {} to help menu disappear\r\r",i+1);
			std::cout.flush();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		terminal_clear();
	}
	void run()
	{
		help_menu();
		while(!m_quit)
		{
			user_input();
			update();
			ai_input();
			update();
			render();
		}
	}
private:
	Grid m_grid;
	bool m_quit;
	int  m_score1;
	int  m_score2;
};
int main()
{	
	TicTacToeTerminal tic_tac_toe;
	tic_tac_toe.run();
}

