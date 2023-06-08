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
    static constexpr uint window_width_ = 600; 
    static constexpr uint window_height_ = 700;
    static constexpr uint border_width_ = 0;
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
    //should probably simplify this
    //to a non template function with defined argument types
    //but for now it works at least for the current use case
    template <typename ...Containers>
        void render_objects(Containers&... conts);
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;
    DisplayManager& operator=(DisplayManager&&)=delete;
};

