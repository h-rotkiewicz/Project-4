#include "Actors.h"
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
    const uint window_width_ = 600; 
    const uint window_height_ = 700;
    const uint border_width_ = 0;
    std::unique_ptr<Display, decltype(WindowDeleter)> disp_  = {XOpenDisplay(nullptr), WindowDeleter};
    Window window_;
    XdbeBackBuffer back_buffer_;
    long unsigned *chosen_buffer_;
    XEvent event_;
    GC gc_;
    int screen_;
    int minor_;
    int major_;
    XdbeSwapInfo swap_info_;
    bool double_buffering_ = true;
    DisplayManager();
    public:
    static DisplayManager& GetInstance();
    int get_width() const;
    int get_height() const;
    ~DisplayManager();
    void swap_buffers();
    void render_objects(ObjectObserver const &obs)
    {
        for(auto& i : obs.get_drawable()){
            i->draw(disp_.get(),*chosen_buffer_,gc_);
        }

        for(auto& i : obs.get_moveable()){
            i->draw(disp_.get(),*chosen_buffer_,gc_);
            i->move();
        }

        if(XPending(disp_.get())){
            XNextEvent(disp_.get(), &event_);
            if (event_.type == Expose)
            {
                //write starting screen or something
            }

            //key press p
            if (event_.type == KeyPress && event_.xkey.keycode == 33)
            {
                obs.get_elevator()->set_target(1,1);
            }
        }
        swap_buffers();
    }

    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;
    DisplayManager& operator=(DisplayManager&&)=delete;
};
