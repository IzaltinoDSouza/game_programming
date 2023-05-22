#include <gtest/gtest.h>
#include "grid.h"

TEST(tic_tac_toe_grid, set_and_get_marks)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(0,2,TicTacToe::Marks::X);
	
	grid.set_mark(1,0,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(1,2,TicTacToe::Marks::X);
	
	grid.set_mark(2,0,TicTacToe::Marks::X);
	grid.set_mark(2,1,TicTacToe::Marks::X);
	grid.set_mark(2,2,TicTacToe::Marks::X);
	
	EXPECT_EQ(grid.get_mark(0,0),TicTacToe::Marks::X);
	EXPECT_EQ(grid.get_mark(0,1),TicTacToe::Marks::X);
	EXPECT_EQ(grid.get_mark(0,2),TicTacToe::Marks::X);
	
	EXPECT_EQ(grid.get_mark(1,0),TicTacToe::Marks::X);
	EXPECT_EQ(grid.get_mark(1,1),TicTacToe::Marks::X);
	EXPECT_EQ(grid.get_mark(1,2),TicTacToe::Marks::X);
	
	EXPECT_EQ(grid.get_mark(2,0),TicTacToe::Marks::X);
	EXPECT_EQ(grid.get_mark(2,1),TicTacToe::Marks::X);
	EXPECT_EQ(grid.get_mark(2,2),TicTacToe::Marks::X);
}
TEST(tic_tac_toe_grid, is_available_offset)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(0,2,TicTacToe::Marks::X);
	
	EXPECT_EQ(grid.is_available(1),false);
	EXPECT_EQ(grid.is_available(2),false);
	EXPECT_EQ(grid.is_available(3),false);
}
TEST(tic_tac_toe_grid, is_available_x_y)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(0,2,TicTacToe::Marks::X);
	
	EXPECT_EQ(grid.is_available(0,1),false);
	EXPECT_EQ(grid.is_available(0,1),false);
	EXPECT_EQ(grid.is_available(0,2),false);
}
TEST(tic_tac_toe_grid, no_more_available)
{
	TicTacToe::Grid grid;
		
	grid.set_mark(0,0,TicTacToe::Marks::X);
	grid.set_mark(0,1,TicTacToe::Marks::X);
	grid.set_mark(0,2,TicTacToe::Marks::X);
	
	grid.set_mark(1,0,TicTacToe::Marks::X);
	grid.set_mark(1,1,TicTacToe::Marks::X);
	grid.set_mark(1,2,TicTacToe::Marks::X);
	
	grid.set_mark(2,0,TicTacToe::Marks::X);
	grid.set_mark(2,1,TicTacToe::Marks::X);
	grid.set_mark(2,2,TicTacToe::Marks::X);
	
	EXPECT_EQ(grid.no_more_available(),true);
}


int main(int argc,char ** argv)
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
