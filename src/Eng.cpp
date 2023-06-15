#include "Eng.h"

DisplayManager::DisplayManager() { 
    int minor_;
    int major_;
    if(!disp_) {
        throw std::runtime_error("Failed to open X11 display");
    }
    int event_base, error_base;
    if (!XSyncQueryExtension(disp_.get(), &event_base, &error_base)) {
        std::cerr << "XSync extension not supported\n" 
                  << "Some animations may stutter\n";
    }
    screen_ = DefaultScreen(disp_.get());
    window_ = XCreateSimpleWindow(disp_.get(), RootWindow(disp_.get(), screen_), 0,0 ,window_width ,window_height , 
            border_width, BlackPixel(disp_.get(), screen_), WhitePixel(disp_.get(), screen_));

    XSelectInput(disp_.get(), window_,  ButtonPressMask | KeyPressMask);
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
        swap_info_.swap_action = XdbeBackground; 
        back_buffer_ = XdbeAllocateBackBufferName(disp_.get(), swap_info_.swap_window, swap_info_.swap_action);
    }
}

DisplayManager& DisplayManager::GetInstance(){
    static DisplayManager instance;
    return instance;
}

void DisplayManager::swap_buffers(){
    if(double_buffering_) {
        XdbeSwapBuffers(disp_.get(), &swap_info_, 1);
    }
    else {
        XFlush(disp_.get());
    }
}

DisplayManager::~DisplayManager(){
    XDestroyWindow(disp_.get(), window_);
}


