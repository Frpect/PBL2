#include"State.h"

class LoginState : public State {
public:
    LoginState();
    virtual ~LoginState();
    virtual void handleEvent(SDL_Event& e) override;
    virtual void update() override;
    virtual void render(SDL_Renderer* des_, const SDL_Rect* clip = nullptr) override;    
protected:    
    Role identity_;
    int currentTab_;
    std::vector<std::unique_ptr<Tab>> tabs_; 
};