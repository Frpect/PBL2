#include "LoginTabs.h"
#include "TextInput.h"
//HomeTab
HomeTab::HomeTab()//load cac image, bg vao truoc
{
    bG_.loadImg("assets/img/HomeTab.png",screen);    
    
    buttons_.push_back(std::make_unique<Button>(
        282,537,210,73,
        SDL_Color{183, 28, 28,255},
        SDL_Color{154, 21, 21,255},
        "Đăng Nhập",
        SDL_Color{(255), (255), (255), (255)},
        font));
}
HomeTab::~HomeTab()=default;
void HomeTab::update()
{

}
void HomeTab::handleEvent(SDL_Event& e) 
{
    for(int i=0;i<buttons_.size();i++)
    {
        buttons_[i]->handleEvent(e);
        if(buttons_[i]->isClicked(e))
        {
            status_=DONE;
        }
    }
}
void HomeTab::render(SDL_Renderer* des_, const SDL_Rect* clip) {
    bG_.render(des_);
    for (auto& btn : buttons_) btn->render(des_);
}

//ROLETAB
RoleTab::RoleTab()
{
        bG_.loadImg("assets/img/RoleTab.png", screen);

    buttons_.push_back(std::make_unique<Button>(
        450, 450, 160, 110,
        SDL_Color{249, 168, 37, 255},
        SDL_Color{255, 183, 5, 255},
        "Guest",
        SDL_Color{255, 255, 255, 255},
        font));

    buttons_.push_back(std::make_unique<Button>(
        727, 451, 160, 110,
        SDL_Color{249, 168, 37, 255},
        SDL_Color{255, 183, 5, 255},
        "Staff",
        SDL_Color{255, 255, 255, 255},
        font));
 
    auto btn = std::make_unique<Button2>(
    "assets/img/ExitButton.png",
    "assets/img/HExitButton.png",
    screen,
    1170, 625,
    "",
    SDL_Color{255, 255, 255, 255},
    font);

    buttons_.push_back(std::move(btn));     
}//load cac image, bg vao s
RoleTab::~RoleTab()=default;
void RoleTab::render(SDL_Renderer* des_, const SDL_Rect* clip) {
    bG_.render(des_);
    for (auto& btn : buttons_) btn->render(des_);
}
void RoleTab::update()
{

}
void RoleTab::handleEvent(SDL_Event& e) 
{
    for(int i=0;i<buttons_.size();i++)
    {
        buttons_[i]->handleEvent(e);
        if(buttons_[i]->isClicked(e))
        {            
            auto* exitBtn = dynamic_cast<Button2*>(buttons_[i].get());
            if (exitBtn) {
                status_ = BACK;  
            } else {
                status_ = DONE;  
            }                 
        }
    }
}
//LoginTab

LoginTab::LoginTab()
{
    bG_.loadImg("assets/img/LoginTab.png",screen);
    // Inputs
    usernameInput_ = std::make_unique<TextInput>(460, 365, 380, 48, "Tên đăng nhập", false);
    passwordInput_ = std::make_unique<TextInput>(460, 490, 380, 48, "Mật khẩu", false);
    auto btn = std::make_unique<Button2>(
    "assets/img/ExitButton.png",
    "assets/img/HExitButton.png",
    screen,
    1170, 625,
    "",
    SDL_Color{0,0,0,255},
    font);  
    buttons_.push_back(std::move(btn)); 
    buttons_.push_back(std::make_unique<Button>(
        430, 550, 470, 70,
        SDL_Color{249, 168, 37, 255},
        SDL_Color{255, 183, 5, 255},
        "LOGIN",
        SDL_Color{255, 255, 255, 255},
        font)); 

}//load cac image, bg vao truoc
LoginTab::~LoginTab()=default;
void LoginTab::render(SDL_Renderer* des_, const SDL_Rect* clip) {
    bG_.render(des_);
    if (usernameInput_) usernameInput_->render(des_);
    if (passwordInput_) passwordInput_->render(des_);
    for (auto& btn : buttons_) btn->render(des_);
}
void LoginTab::update()
{

}
void LoginTab::handleEvent(SDL_Event& e) 
{
    if (usernameInput_) usernameInput_->handleEvent(e);
    if (passwordInput_) passwordInput_->handleEvent(e);

    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_RETURN)
        {
            status_ = DONE;
        }
        else if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            status_ = BACK;
        }
    }
    for(int i=0;i<buttons_.size();i++)
    {
        buttons_[i]->handleEvent(e);
        if(buttons_[i]->isClicked(e))
        {            
            auto* exitBtn = dynamic_cast<Button2*>(buttons_[i].get());
            if (exitBtn) {
                status_ = BACK;  
            } else {
                status_ = DONE;  
            }                 
        }
    }
    
}

