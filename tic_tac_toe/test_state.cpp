#include <gtest/gtest.h>
#include "state.h"

TEST(tic_tac_toe_state, X_WINNER_HORIZONTAL)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(0,2,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
	
	grid.set_mark(1,0,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(1,2,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
	
	grid.set_mark(1,0,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(1,2,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
}
TEST(tic_tac_toe_state, X_WINNER_VERTICAL)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(1,0,TicTacToe::Marks::X);
	grid.set_mark(2,0,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
	
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(2,1,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
	
	grid.set_mark(0,2,TicTacToe::Marks::X);
	grid.set_mark(1,2,TicTacToe::Marks::X);
	grid.set_mark(2,2,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
}
TEST(tic_tac_toe_state, X_WINNER_DIAGONAL)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(2,2,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
	
	grid.set_mark(0,2,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(2,0,TicTacToe::Marks::X);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::X_WIN);
	grid.reset();
}

TEST(tic_tac_toe_state, O_WINNER_HORIZONTAL)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::O);
	grid.set_mark(0,1,TicTacToe::Marks::O);
	grid.set_mark(0,2,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
	
	grid.set_mark(1,0,TicTacToe::Marks::O);
	grid.set_mark(1,1,TicTacToe::Marks::O);
	grid.set_mark(1,2,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
	
	grid.set_mark(1,0,TicTacToe::Marks::O);
	grid.set_mark(1,1,TicTacToe::Marks::O);
	grid.set_mark(1,2,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
}
TEST(tic_tac_toe_state, O_WINNER_VERTICAL)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::O);
	grid.set_mark(1,0,TicTacToe::Marks::O);
	grid.set_mark(2,0,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
	
	grid.set_mark(0,1,TicTacToe::Marks::O);
	grid.set_mark(1,1,TicTacToe::Marks::O);
	grid.set_mark(2,1,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
	
	grid.set_mark(0,2,TicTacToe::Marks::O);
	grid.set_mark(1,2,TicTacToe::Marks::O);
	grid.set_mark(2,2,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
}
TEST(tic_tac_toe_state, O_WINNER_DIAGONAL)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::O);
	grid.set_mark(1,1,TicTacToe::Marks::O);
	grid.set_mark(2,2,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
	
	grid.set_mark(0,2,TicTacToe::Marks::O);
	grid.set_mark(1,1,TicTacToe::Marks::O);
	grid.set_mark(2,0,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::O_WIN);
	grid.reset();
}

TEST(tic_tac_toe_state, DRAW)
{
	
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::O);
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(0,2,TicTacToe::Marks::O);
	
	grid.set_mark(1,0,TicTacToe::Marks::O);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(1,2,TicTacToe::Marks::X);
	
	grid.set_mark(2,0,TicTacToe::Marks::X);
	grid.set_mark(2,1,TicTacToe::Marks::O);
	grid.set_mark(2,2,TicTacToe::Marks::O);
	EXPECT_EQ(check_state_winner_or_draw(grid),TicTacToe::State::DRAW);
}

int main(int argc,char ** argv)
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
