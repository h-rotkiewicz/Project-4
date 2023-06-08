#include "include/Eng.h"

DisplayManager::DisplayManager() { 
        
        if(!disp_) {
            throw std::runtime_error("Failed to open X11 display");
        }
        screen_ = DefaultScreen(disp_.get());
        window_ = XCreateSimpleWindow(disp_.get(), RootWindow(disp_.get(), screen_), 0,0 ,window_width_ ,window_height_ , 
                border_width_, BlackPixel(disp_.get(), screen_), WhitePixel(disp_.get(), screen_));
        XSelectInput(disp_.get(), window_, ExposureMask | KeyPressMask);
        XMapWindow(disp_.get(), window_);
        gc_ = XCreateGC(disp_.get(), window_, 0, 0);

        if(!XdbeQueryExtension(disp_.get() ,&major_, &minor_)) {
            std::cerr << "Double buffering not supported\n";
            std::cerr << "Proceeding with single buffer\n";
            std::cerr << "Program may be slow and flicker\n";
            double_buffering_ = false;
            chosen_buffer_ = &window_;
        }
        else {
            chosen_buffer_ = &back_buffer_;
            swap_info_.swap_window = window_;
            //For ref see https://manpages.ubuntu.com/manpages/trusty/man3/XdbeSwapBuffers.3.html
            swap_info_.swap_action = XdbeUndefined; 
            back_buffer_ = XdbeAllocateBackBufferName(disp_.get(), swap_info_.swap_window, swap_info_.swap_action);
        }
    }

DisplayManager& DisplayManager::GetInstance(){
    static DisplayManager instance;
    return instance;
}

int DisplayManager::get_height() const {
    return window_height_;
}

int DisplayManager::get_width() const {
    return window_width_;
}

DisplayManager::~DisplayManager(){
    XDestroyWindow(disp_.get(), window_);
}

template <typename... Containers>
void DisplayManager::render_objects(Containers &...conts)
{
    auto Render = [&](auto &cont)
    {
        for (auto &obj : cont)
            obj->draw(disp_.get(), *chosen_buffer_, gc_);
    };

    XNextEvent(disp_.get(), &event_);
    if (event_.type == Expose)
    {
            (Render(conts), ...);
            if (double_buffering_)
            {
                XdbeSwapBuffers(disp_.get(), &swap_info_, 1);
            }
    }
    if (event_.type == KeyPress)
    {
    }
}
