#ifndef BUTTON_H
#define BUTTON_H

#include"Common.h"
class Button {
protected:
    SDL_Rect rect_;            
    SDL_Color colorNormal_;    
    SDL_Color colorHover_;     
    bool hovered_;    
    
    std::string label_;        
    SDL_Color textColor_;      
    TTF_Font* font_;    

public:
    Button();
    virtual ~Button();

    Button(int x, int y, int w, int h,
           SDL_Color normal, SDL_Color hover,
           const std::string& label = "",
           SDL_Color textColor = {255, 255, 255, 255},
           TTF_Font* font = nullptr);

    virtual void handleEvent(SDL_Event& e);
    virtual bool isClicked(SDL_Event& e);
    virtual void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr);
        
};



class Button2 : public Button {
private:
    SDL_Texture* texNormal_ = nullptr;
    SDL_Texture* texHover_ = nullptr;

public:
    Button2();
    ~Button2() override;
    Button2(const std::string& normalPath,
            const std::string& hoverPath,
            SDL_Renderer* renderer,
            int x, int y,
            const std::string& label = "",
            SDL_Color textColor = {255, 255, 255, 255},
            TTF_Font* font = nullptr);

    bool loadImage(const std::string& normalPath,
                   const std::string& hoverPath,
                   SDL_Renderer* renderer);

    // Ghi đè 3 hàm chính
    void handleEvent(SDL_Event& e) override;
    bool isClicked(SDL_Event& e) override;
    void render(SDL_Renderer* renderer, const SDL_Rect* clip = nullptr) override;
    
    void free();
};


#endif
