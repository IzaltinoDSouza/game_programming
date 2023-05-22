#include <SDL2/SDL.h>
#include <fmt/core.h>

#include "state.h"
#include "grid.h"

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
	 : m_quit{false}
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
		
		draw_grid();
		
		mouse_over(m_mouse_input.x,m_mouse_input.y);
		
		SDL_RenderPresent(m_renderer);
	}
	void process_input()
	{
		m_user_choose = false;
		
		int width,height;
		SDL_GetWindowSize(m_window,&width,&height);

		int spacing = 5;
		width  /= 3;
		height /= 3;

		for(int posy = 0;posy < 3;++posy)
		{
			for(int posx = 0;posx < 3;++posx)
			{
				SDL_Rect rect = {(width*posx)+spacing,
						         (height*posy)+spacing,
						          width-(spacing*2),
						          height-(spacing*2)};
				
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
		ai_try_again:
		
		srand(time(NULL));
		size_t x = rand() % 3;
		srand(time(NULL));
		size_t y = rand() % 3;
		
		if(m_grid.is_available(x,y))
		{
			m_grid.set_mark(x,y,TicTacToe::Marks::O);
		}else
		{
			if(m_grid.no_more_available()) return;
			goto ai_try_again;
		}
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
	uint32_t        m_target_fps_time{static_cast<uint32_t>(1000.0/30.0)};
	MouseInput      m_mouse_input;
	bool            m_user_choose;
	
	void mouse_over(int x,int y)
	{	
		int width,height;
		SDL_GetWindowSize(m_window,&width,&height);
		
		int spacing = 5;
		width  /= 3;
		height /= 3;
		
		for(int posy = 0;posy < 3;++posy)
		{
			for(int posx = 0;posx < 3;++posx)
			{
				SDL_Rect rect = {(width*posx)+spacing,
				                 (height*posy)+spacing,
				                  width-(spacing*2),
				                  height-(spacing*2)};
				 
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
	void draw_grid()
	{
		int width,height;
		SDL_GetWindowSize(m_window,&width,&height);
		
		int spacing = 5;
		width  /= 3;
		height /= 3;
		
		for(int y = 0;y < 3;++y)
		{
			for(int x = 0;x < 3;++x)
			{
				switch(m_grid.get_mark(x,y))
				{
					case TicTacToe::Marks::EMPTY:
						SDL_SetRenderDrawColor(m_renderer,255,255,255,255);
					break;
					case TicTacToe::Marks::X:
						SDL_SetRenderDrawColor(m_renderer,0,255,0,255);
					break;
					case TicTacToe::Marks::O:
						SDL_SetRenderDrawColor(m_renderer,255,0,0,255);
					break;
				}
			
				SDL_Rect rect = {(width*x)+spacing,
				                 (height*y)+spacing,
				                  width-(spacing*2),
				                  height-(spacing*2)};

				SDL_RenderFillRect(m_renderer,&rect);
			}
		}
	}
};

int main()
{
	TicTacToeSDL tic_tac_toe(800,600);
	tic_tac_toe.run();
}
