#include <SDL2/SDL.h>
#include <fmt/core.h>

#include "state.h"
#include "grid.h"
#include "ai.h"

class GridView
{
public:
	GridView(const TicTacToe::Grid & grid,int width,int height)
	: m_grid{grid},
	  m_width{width/3},
	  m_height{height/3}
	{
	
	}
	void draw(SDL_Renderer * renderer)
	{
		for(int y = 0;y < 3;++y)
		{
			for(int x = 0;x < 3;++x)
			{
				switch(m_grid.get_mark(x,y))
				{
					case TicTacToe::Marks::EMPTY:
						SDL_SetRenderDrawColor(renderer,255,255,255,255);
					break;
					case TicTacToe::Marks::X:
						SDL_SetRenderDrawColor(renderer,0,255,0,255);
					break;
					case TicTacToe::Marks::O:
						SDL_SetRenderDrawColor(renderer,255,0,0,255);
					break;
				}

				SDL_Rect rect = {(m_width*x)+k_spacing,
								 (m_height*y)+k_spacing,
								  m_width-(k_spacing*2),
								  m_height-(k_spacing*2)};

				SDL_RenderFillRect(renderer,&rect);
			}
		}
	}
	
	SDL_Rect grid_rect(int x,int y)
	{
		return SDL_Rect {(m_width*x)+k_spacing,(m_height*y)+k_spacing,
				          m_width-(k_spacing*2),m_height-(k_spacing*2)};
	}
private:
	const TicTacToe::Grid & m_grid;
	int m_width;
	int m_height;
	const int k_spacing{5};
};

struct MouseInput
{
	int x;
	int y;
	bool click;
};
class TicTacToeSDL
{
public:
	TicTacToeSDL(size_t width,size_t height,const char * title = "TicTacToe")
	 : m_quit{false},
	   m_grid_view{m_grid,static_cast<int>(width),static_cast<int>(height)}
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
		{
			fmt::print("SDL initialization fail : {} \n", SDL_GetError());
			exit(1);
		}
		m_window = SDL_CreateWindow(title,
		                            SDL_WINDOWPOS_CENTERED,
		                            SDL_WINDOWPOS_CENTERED,
		                            width,
		                            height,
		                            SDL_WINDOW_SHOWN);
		if(m_window == nullptr)
		{
			fmt::print("SDL create window fail : {} \n", SDL_GetError());
			exit(1);
		}
		
		m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
		if(m_renderer == nullptr)
		{
			fmt::print("SDL create renderer fail : {} \n", SDL_GetError());
			exit(1);
		}
	}
	~TicTacToeSDL()
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}
	void run()
	{		
		while(!m_quit)
		{
			uint32_t frame_start = SDL_GetTicks();			
					
			input();

			process_input();

			if(m_user_choose)
			{
				ai_input();
			}

			update();
			render();
			
			uint32_t frame_time = SDL_GetTicks() - frame_start;
			if(frame_time < m_target_fps_time)
				SDL_Delay(m_target_fps_time - frame_time);
		}
	}
private:
	SDL_Window   *  m_window;
	SDL_Renderer *  m_renderer; 
	SDL_Event       m_event;
	bool            m_quit;
	TicTacToe::Grid m_grid;
	GridView        m_grid_view;
	uint32_t        m_target_fps_time{static_cast<uint32_t>(1000.0/30.0)};
	MouseInput      m_mouse_input;
	bool            m_user_choose;
	
	void input()
	{
		while(SDL_PollEvent(&m_event))
		{
			if(m_event.type == SDL_QUIT) m_quit = true;
			if(m_event.type == SDL_KEYDOWN)
			{
				if(m_event.key.keysym.sym == SDLK_ESCAPE) m_quit  = true;
				
				//fmt::print("keydown {}\n",m_event.key.keysym.sym);
			}
			if(m_event.type == SDL_MOUSEMOTION)
			{
				//fmt::print("{} {}\n",m_event.motion.x,m_event.motion.y);
				m_mouse_input = {m_event.motion.x,m_event.motion.y,false};				
			}
			if(m_event.type == SDL_MOUSEBUTTONDOWN)
			{
				m_mouse_input = {m_event.motion.x,m_event.motion.y,true};
				//fmt::print("{} {}\n",m_event.button.x,m_event.button.y);
			}
		}
	}
	void render()
	{
		SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
		SDL_RenderClear(m_renderer);
		
		m_grid_view.draw(m_renderer);
		
		mouse_over(m_mouse_input.x,m_mouse_input.y);
		
		SDL_RenderPresent(m_renderer);
	}
	void process_input()
	{
		m_user_choose = false;

		for(int posy = 0;posy < 3;++posy)
		{
			for(int posx = 0;posx < 3;++posx)
			{
				const SDL_Rect rect = m_grid_view.grid_rect(posx,posy);
				
				 if(m_mouse_input.click)
				 {
					 if(m_mouse_input.x >= rect.x           &&
						m_mouse_input.x <= rect.x + rect.w  && 
						m_mouse_input.y >= rect.y           &&
						m_mouse_input.y <= rect.y + rect.h)
					 {
					 	switch(m_grid.get_mark(posx,posy))
						{
							case TicTacToe::Marks::EMPTY:
								m_grid.set_mark(posx,posy,TicTacToe::Marks::X);
								m_user_choose = true;
							break;
						}
					 }
				 }
			}
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
			{
				return;	//DO NOTHNG
			}
			break;
			case TicTacToe::State::X_WIN:
			{
				m_quit = true;
				SDL_Delay(1000);
			}
			break;
			case TicTacToe::State::O_WIN:
			{
				m_quit = true;
				SDL_Delay(1000);
			}
			break;
			case TicTacToe::State::DRAW:
			{
				m_quit = true;
				SDL_Delay(1000);
			}
			break;
		}
	}
	void mouse_over(int x,int y)
	{
		for(int posy = 0;posy < 3;++posy)
		{
			for(int posx = 0;posx < 3;++posx)
			{
				const SDL_Rect rect = m_grid_view.grid_rect(posx,posy);
				 
				 if(x >= rect.x && x <= rect.x + rect.w && 
				    y >= rect.y && y <= rect.y + rect.h)
				 {
				 	switch(m_grid.get_mark(posx,posy))
					{
						case TicTacToe::Marks::EMPTY:
							SDL_SetRenderDrawColor(m_renderer,0,255,0,255);
							SDL_RenderFillRect(m_renderer,&rect);
						break;
						case TicTacToe::Marks::X:
							SDL_SetRenderDrawColor(m_renderer,0,255,0,255);
							SDL_RenderFillRect(m_renderer,&rect);
						break;
					}
				 }
			}
		}
	}
	
};

int main()
{
	TicTacToeSDL tic_tac_toe(800,600);
	tic_tac_toe.run();
}
