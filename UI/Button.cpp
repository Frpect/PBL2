#include"Button.h"
// Provide missing destructor definition
Button::~Button() = default;
Button::Button():hovered_(false)
{
    rect_.x=0;
    rect_.y=0;
    colorNormal_={255,255,255,255};
    colorHover_={0,0,0,255};    
}
Button::Button(int x, int y, int w, int h,
               SDL_Color normal, SDL_Color hover,
               const std::string& label,
               SDL_Color textColor,
               TTF_Font* font)
    : hovered_(false), label_(label), textColor_(textColor), font_(font)
{
    rect_ = { x, y, w, h };
    colorNormal_ = normal;
    colorHover_ = hover;
}

void Button::handleEvent(SDL_Event& e) {//Giup chinh on hovered - Re chuot toi vi tri thi hovered
        if (e.type == SDL_MOUSEMOTION) {
            int mx = e.motion.x, my = e.motion.y;
            SDL_Point point = { mx, my };
            hovered_ = SDL_PointInRect(&point, &rect_);
        }
    }

bool Button::isClicked(SDL_Event& e) { //Nhan click chuot
        if (e.type == SDL_MOUSEBUTTONDOWN && hovered_) {
            return true;
        }
        return false;
    }

void Button::render(SDL_Renderer* renderer, const SDL_Rect* clip) {
    // Màu nút
    SDL_Color c = hovered_ ? colorHover_ : colorNormal_;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
    SDL_RenderFillRect(renderer, &rect_);

    // Viền nút (tùy chọn)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    SDL_RenderDrawRect(renderer, &rect_);

    // Nếu có text
    if (font_ && !label_.empty()) {
        SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font_, label_.c_str(), textColor_);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Căn giữa text trong rect
        int textW, textH;
        SDL_QueryTexture(textTexture, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = {
            rect_.x + (rect_.w - textW) / 2,
            rect_.y + (rect_.h - textH) / 2,
            textW,
            textH
        };

        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
}
//////////////////////////////////////////


Button2::Button2() = default;

Button2::~Button2() {
    free();
}
Button2::Button2(const std::string& normalPath,
                 const std::string& hoverPath,
                 SDL_Renderer* renderer,
                 int x, int y,
                 const std::string& label,
                 SDL_Color textColor,
                 TTF_Font* font)
{
    // Gán thuộc tính text
    label_ = label;
    textColor_ = textColor;
    font_ = font;

    // Load ảnh
    if (!loadImage(normalPath, hoverPath, renderer)) {
        std::cerr << "[Button2] Failed to load images: " << normalPath << std::endl;
    }

    // Đặt vị trí (kích thước đã lấy từ ảnh)
    rect_.x = x;
    rect_.y = y;

    // Mặc định không hover
    hovered_ = false;
}

bool Button2::loadImage(const std::string& normalPath,
                        const std::string& hoverPath,
                        SDL_Renderer* renderer)
{
    free();

    SDL_Surface* surfNormal = IMG_Load(normalPath.c_str());
    if (!surfNormal) {
        std::cerr << "IMG_Load failed (normal): " << IMG_GetError() << std::endl;
        return false;
    }

    texNormal_ = SDL_CreateTextureFromSurface(renderer, surfNormal);
    rect_.w = surfNormal->w;
    rect_.h = surfNormal->h;
    SDL_FreeSurface(surfNormal);

    if (!hoverPath.empty()) {
        SDL_Surface* surfHover = IMG_Load(hoverPath.c_str());
        if (surfHover) {
            texHover_ = SDL_CreateTextureFromSurface(renderer, surfHover);
            SDL_FreeSurface(surfHover);
        }
    }

    return texNormal_ != nullptr;
}

void Button2::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_MOUSEMOTION) {
        SDL_Point p = { e.motion.x, e.motion.y };
        hovered_ = SDL_PointInRect(&p, &rect_);
    }
}

bool Button2::isClicked(SDL_Event& e)
{
    return (e.type == SDL_MOUSEBUTTONDOWN && hovered_);
}

void Button2::render(SDL_Renderer* renderer, const SDL_Rect* clip)
{
    if (!renderer || !texNormal_) return;

    SDL_Texture* tex = hovered_ && texHover_ ? texHover_ : texNormal_;
    SDL_RenderCopy(renderer, tex, clip, &rect_);

    // Nếu muốn thêm text chồng lên ảnh
    if (font_ && !label_.empty()) {
        SDL_Surface* surf = TTF_RenderUTF8_Blended(font_, label_.c_str(), textColor_);
        SDL_Texture* texText = SDL_CreateTextureFromSurface(renderer, surf);

        int textW, textH;
        SDL_QueryTexture(texText, nullptr, nullptr, &textW, &textH);
        SDL_Rect textRect = {
            rect_.x + (rect_.w - textW) / 2,
            rect_.y + (rect_.h - textH) / 2,
            textW, textH
        };

        SDL_RenderCopy(renderer, texText, nullptr, &textRect);
        SDL_DestroyTexture(texText);
        SDL_FreeSurface(surf);
    }
}

void Button2::free()
{
    if (texNormal_) {
        SDL_DestroyTexture(texNormal_);
        texNormal_ = nullptr;
    }
    if (texHover_) {
        SDL_DestroyTexture(texHover_);
        texHover_ = nullptr;
    }
}