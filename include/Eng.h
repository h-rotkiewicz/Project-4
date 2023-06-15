#include "Actors.h"
#include <X11/extensions/sync.h>
#include <iostream>
#include <string>
#include <utility>
#include <array>
#include <vector>
//RAII wrapper for X11 Display
inline auto WindowDeleter = [](Display* disp) noexcept {
    if(disp)
        XCloseDisplay(disp);
};

//Singleton class for managing X11 display and window
class DisplayManager {
    std::unique_ptr<Display, decltype(WindowDeleter)> disp_  = {XOpenDisplay(nullptr), WindowDeleter};
    Window window_;
    XdbeBackBuffer back_buffer_;
    long unsigned *chosen_buffer_;
    XEvent event_;
    
    GC gc_;
    int screen_;
    XdbeSwapInfo swap_info_;
    bool double_buffering_ = true;
    DisplayManager();
    public:
    static constexpr uint window_width = 600; 
    static constexpr uint window_height = 700;
    static constexpr uint border_width = 0;
    static DisplayManager& GetInstance();

    ~DisplayManager();
    void handle_events(ObjectObserver const &obs)
    {
        if(XPending(disp_.get())){
            XNextEvent(disp_.get(), &event_);
            if (event_.type == Expose)
            {
                //write starting screen or something
            }
            else if(event_.type == ButtonPress)
            {
                obs.was_button_pressed(event_.xbutton.x, event_.xbutton.y);    
            }
        }
    }
    void swap_buffers();
    void render_objects(ObjectObserver const &obs)
    {
        for(auto const &i : obs.get_drawable()){
            i->draw(disp_.get(),*chosen_buffer_,gc_);
        }

        for(auto const &i : obs.get_moveable()){
            i->draw(disp_.get(),*chosen_buffer_,gc_);
            i->move();
        }

        for(auto const & i : obs.get_buttons()){
            i->draw(disp_.get(),*chosen_buffer_,gc_);
        }
        handle_events(obs);
        XSync(disp_.get(), false);
        swap_buffers();
    }
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;
    DisplayManager& operator=(DisplayManager&&)=delete;
};
