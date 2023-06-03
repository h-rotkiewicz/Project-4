#include <X11/Xlib.h>
#include <memory>
#include <iostream>
#include <string>
#include <utility>
#include <array>

class IDrawable{
    protected:
        virtual void draw(Display *disp, Window const & win, GC const &gc) const = 0;
        friend class DisplayManager; // only draw objects from DisplayManager 
    public:
        virtual ~IDrawable() = default;
};

class Floor : public IDrawable{
    private:
        int lenght_;
        int width_;
        int x_;
        int y_;

        void draw(Display *disp, Window const &win, GC const &gc) const override  {
            XFillRectangle(disp, win, gc, x_, y_, lenght_, width_);
            XFlush(disp);
        }

    public:
        Floor(int lenght, int width,  int x, int y): lenght_(lenght), width_(width),  x_(x), y_(y) {}
};

class Elevator : public IDrawable{
    private:
        int width_;
        int height_;
        int x_;
        int y_;

        void draw(Display *disp, Window const &win, GC const &gc) const override {
            //TODO:change to actual draw function
            XFillRectangle(disp, win, gc, x_, y_, width_, height_);
            XFlush(disp);
        }

    public:
        Elevator( int width, int height, int x, int y):  width_(width), height_(height), x_(x), y_(y) {}
};

//RAII wrapper for X11 Display
inline auto WindowDeleter = [](Display* disp) noexcept {
    if(disp)
        XCloseDisplay(disp);
};

//Singleton class for managing X11 display and window
class DisplayManager {
    static constexpr auto window_width_ = 800; 
    static constexpr auto window_height_ = 600;
    static constexpr auto border_width_ = 0;

    const char *window_title_ = "Project 4";
    std::unique_ptr<Display, decltype(WindowDeleter)> disp_ = {XOpenDisplay(NULL), WindowDeleter};
    Window window_;
    XEvent event_;
    GC gc_;
    int screen_;

    DisplayManager(){ 
        if(!disp_) {
            throw std::runtime_error("Failed to open X11 display");
        }
        screen_ = DefaultScreen(disp_.get());
        window_ = XCreateSimpleWindow(disp_.get(), RootWindow(disp_.get(), screen_), 0,0 ,window_width_ ,window_height_ , border_width_, BlackPixel(disp_.get(), screen_), WhitePixel(disp_.get(), screen_));
        XSelectInput(disp_.get(), window_, ExposureMask | KeyPressMask);
        XMapWindow(disp_.get(), window_);
        gc_ = XCreateGC(disp_.get(), window_, 0, 0);
    }

    public:
    static DisplayManager& GetInstance() {
        static DisplayManager instance;
        return instance;
    }

    Display& get_display() const {
        return *disp_;
    };

    int& get_screen() {
        return screen_;
    };

    GC& get_gc() {
        return gc_;
    };

    Window& get_window() {
        return window_;
    };

    ~DisplayManager(){
        XDestroyWindow(disp_.get(), window_);
    }
    
// `cont` should be a container of IDrawable objects (e.g., std::vector<std::shared_ptr<IDrawable>>)
    void event_loop(auto &cont){
        while(1) {
            XNextEvent(disp_.get(), &event_);
            if(event_.type == Expose) {
                // TODO: implement a double buffer solution
                for(auto i : cont) {
                    i->draw(disp_.get(), window_, gc_);
                }
            }
            if(event_.type == KeyPress) {
                break;
            }
        }
    }
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;
    DisplayManager& operator=(DisplayManager&&)=delete;
};

