#include "TextInput.h"
#include "Common.h"

TextInput::TextInput(int x, int y, int w, int h,
                     const std::string& placeholder,
                     bool passwordMode)
{
    rect_.x = x;
    rect_.y = y;
    rect_.w = w;
    rect_.h = h;

    placeholder_ = placeholder;
    passwordMode_ = passwordMode;
    focused_ = false;
    maxLength_ = 64;
    padding_ = 10;

    textTexture_ = nullptr;
    textW_ = 0;
    textH_ = 0;

    textColor_ = SDL_Color{255, 255, 255, 255};
    placeholderColor_ = SDL_Color{160, 160, 160, 255};
}

TextInput::~TextInput()
{
    if (textTexture_)
    {
        SDL_DestroyTexture(textTexture_);
        textTexture_ = nullptr;
    }
}

void TextInput::setFocus(bool focused)
{
    if (focused_ == focused) return;
    focused_ = focused;
    if (focused_) SDL_StartTextInput();
    else SDL_StopTextInput();
}

void TextInput::setText(const std::string& text)
{
    text_ = text;
}

void TextInput::setPlaceholder(const std::string& text)
{
    placeholder_ = text;
}

void TextInput::setPasswordMode(bool enabled)
{
    passwordMode_ = enabled;
}

std::string TextInput::getDisplayText() const
{
    if (!text_.empty())
    {
        if (passwordMode_)
        {
            return std::string(text_.size(), '*');
        }
        return text_;
    }
    return placeholder_;
}

void TextInput::rebuildTexture(SDL_Renderer* des_)
{
    if (!font) return;

    if (textTexture_)
    {
        SDL_DestroyTexture(textTexture_);
        textTexture_ = nullptr;
    }

    std::string display = getDisplayText();
    SDL_Color color = text_.empty() ? placeholderColor_ : textColor_;

    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, display.c_str(), color);
    if (!surface)
    {
        return;
    }

    textTexture_ = SDL_CreateTextureFromSurface(des_, surface);
    textW_ = surface->w;
    textH_ = surface->h;
    SDL_FreeSurface(surface);
}

void TextInput::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point p{ e.button.x, e.button.y };
        bool inside = SDL_PointInRect(&p, &rect_);
        setFocus(inside);
    }

    if (!focused_) return;

    if (e.type == SDL_TEXTINPUT)
    {
        if (text_.size() < maxLength_)
        {
            text_ += e.text.text;
        }
    }
    else if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_BACKSPACE)
        {
            if (!text_.empty()) text_.pop_back();
        }
    }
}

void TextInput::render(SDL_Renderer* des_)
{
    rebuildTexture(des_);
    if (textTexture_)
    {
        SDL_Rect dst{ rect_.x + padding_, rect_.y + (rect_.h - textH_) / 2, textW_, textH_ };
        SDL_RenderCopy(des_, textTexture_, nullptr, &dst);
    }
}


