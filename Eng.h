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
    static constexpr auto window_width_ = 600; 
    static constexpr auto window_height_ = 700;
    static constexpr auto border_width_ = 0;

    const char *window_title_ = "Project 4";
    std::unique_ptr<Display, decltype(WindowDeleter)> disp_ = {XOpenDisplay(NULL), WindowDeleter};
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
    
    DisplayManager(){ 
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

    public:
    static DisplayManager& GetInstance() {
        static DisplayManager instance;
        return instance;
    }

    int get_width() const {
        return window_width_;
    };

    int get_height() const {
        return window_height_;
    };

    ~DisplayManager(){
        XDestroyWindow(disp_.get(), window_);
    }

    // `cont` should be a container of IDrawable objects (e.g std::vector<std::shared_ptr<IDrawable>>)
    //  the objects will be drawn in the order they are stored in the container
    //  auto is used to allow flexibility in the type of container used
    void render_objects(auto &cont){
            XNextEvent(disp_.get(), &event_);
            if(event_.type == Expose) {
                // TODO: implement a double buffer solution
                for(auto &i : cont) {
                    i->draw(disp_.get(), *chosen_buffer_, gc_);
                }
                if(double_buffering_) {
                    XdbeSwapBuffers(disp_.get(), &swap_info_, 1);
                }
            }
            if(event_.type == KeyPress) {
            }
    }
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;
    DisplayManager& operator=(DisplayManager&&)=delete;
};

