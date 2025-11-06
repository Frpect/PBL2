#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include "BaseObject.h"
#include <string>

class TextInput : public BaseObject
{
public:
    TextInput(int x, int y, int w, int h,
              const std::string& placeholder = "",
              bool passwordMode = false);
    ~TextInput();

    void handleEvent(SDL_Event& e);
    void render(SDL_Renderer* des_);

    void setFocus(bool focused);
    bool isFocused() const { return focused_; }

    void setText(const std::string& text);
    const std::string& getText() const { return text_; }

    void setPlaceholder(const std::string& text);
    void setPasswordMode(bool enabled);
    void setMaxLength(size_t len) { maxLength_ = len; }

private:
    void rebuildTexture(SDL_Renderer* des_);
    std::string getDisplayText() const;

private:
    std::string text_;
    std::string placeholder_;
    bool focused_;
    bool passwordMode_;
    size_t maxLength_;
    int padding_;

    SDL_Texture* textTexture_;
    int textW_;
    int textH_;

    SDL_Color textColor_;
    SDL_Color placeholderColor_;
};

#endif

