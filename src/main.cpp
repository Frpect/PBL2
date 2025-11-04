#include "BaseObject.h"
#include "LoginState.h"

BaseObject BG;
bool InitData()
{
    bool success=true;
    int ret =SDL_Init(SDL_INIT_VIDEO);
    if(ret<0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << TTF_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("TEST",
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(window ==nullptr) success=false;
    else { 
        screen = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(screen==nullptr)  success=false;
        else
        {
            SDL_SetRenderDrawColor(screen,255,255,255,255);
            int imgFlags= IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags))
            {
                success=false;
            }
        }
    }
    return success;
}
bool loadBG()
{
    bool ret=BG.loadImg("assets/img/HomeTab.png",screen);
    if(ret==false)
    {
        std::cout<<"HONG BG";
        return false;
    }
    return true;
}
void close()
{
    BG.free();
    SDL_DestroyRenderer(screen);
    screen=nullptr;
    SDL_DestroyWindow(window);
    window=nullptr;
    IMG_Quit();
    SDL_Quit();
}

//Flags
bool needRender=true;
int main(int, char**) {
    if(InitData()==false) return -1;
    if(loadBG()==false) return -1;
    // Open font after TTF_Init
    font = TTF_OpenFont("assets/font/Montserrat.ttf", 28);
    if (!font) {
        std::cerr << "Failed to open font: " << TTF_GetError() << std::endl;
        // non-fatal for now; text won't render
    }

    LoginState state1;
    bool is_quit=false;
  
    while(!is_quit)
    {
        while(SDL_PollEvent(&event)!=0)
        {
            if(event.type==SDL_QUIT)
            {
                is_quit=true;
            }
            // forward all events to the state so buttons receive motion and clicks
            state1.handleEvent(event);
        }

        SDL_SetRenderDrawColor(screen,255,255,255,255);
        SDL_RenderClear(screen);

        // let the state render (background + buttons/texts)
        state1.render(screen);

        SDL_RenderPresent(screen);
    }
      
    close();
}
