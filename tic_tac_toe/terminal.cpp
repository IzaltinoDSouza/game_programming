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

#include "state.h"
#include "grid.h"
#include "ai.h"

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
				m_grid.set_mark(offset,TicTacToe::Marks::X);
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
				goto user_try_again;
			break;
			default:
				terminal_clear();
				goto user_try_again;
			break;
		}
	}
	void ai_input()
	{		
		TicTacToe::ai_minimax(m_grid);
	}
	void update()
	{
		switch(TicTacToe::check_state_winner_or_draw(m_grid))
		{
			case TicTacToe::State::NONE:
				return;	//DO NOTHNG
			break;
			case TicTacToe::State::X_WIN:
				m_score1 += 1;
				m_grid.reset();
			break;
			case TicTacToe::State::O_WIN:
				m_score2 += 2;
				m_grid.reset();
			break;
			case TicTacToe::State::DRAW:
				m_grid.reset();
			break;
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
					case TicTacToe::Marks::EMPTY:
						fmt::print("[ ]");
					break;
					case TicTacToe::Marks::X:
						fmt::print("[X]");
					break;
					case TicTacToe::Marks::O:
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
	TicTacToe::Grid  m_grid;
	bool             m_quit;
	int              m_score1;
	int              m_score2;
};
int main()
{	
	TicTacToeTerminal tic_tac_toe;
	tic_tac_toe.run();
}

