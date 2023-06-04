#include <X11/Xlib.h>
#include <X11/extensions/Xdbe.h> // for double buffering
#include <X11/Xutil.h>
#include <vector>
#include <memory>

constexpr int floor_width = 20;
constexpr int floor_lenght = 200;
constexpr int elevator_width = 20;
constexpr int elevator_height = 50;

class IDrawable{
    protected:
        virtual void draw(Display *disp, XdbeBackBuffer, GC const &gc) const = 0;
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

        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override  {
            XSetForeground(disp, gc, 0x0000FF);
            XFillRectangle(disp, back_buff, gc, x_, y_, lenght_, width_);
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

        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override {
            
        }

    public:
        Elevator( int width, int height, int x, int y):  width_(width), height_(height), x_(x), y_(y) {}
};

//since 2 objects have nearly the same constructor, we can use a template to avoid code duplication
//in case elevator or person object has different constructors, we will have to rewrite this
template <typename T>
concept is_IDrawable = std::is_base_of_v<IDrawable, T>;

template <is_IDrawable T>
inline std::unique_ptr<IDrawable> ObjectFactory(int width, int height,int x,int y) {
    return std::make_unique<T>(width, height, x, y);
}

class ObjectHandler{
    std::vector<std::unique_ptr<IDrawable>> container_;
    public:
    template <is_IDrawable OBJECT>
    void add_object(int width, int height,int x, int y){
        container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
    }
    void remove_object(int index){
        container_.erase(container_.begin() + index);
    }
    // So we can use range based for loop in DisplayManager
    auto begin(){
        return container_.begin();
    }
    auto end(){
        return container_.end();
    }
};

inline void Create_Floors(ObjectHandler &Handler, int window_width, int window_height, int number_of_floors){
    int floor_spaceing = window_height*2/(number_of_floors);

    //left
    int k = 1;
    for(int i = 0; i < number_of_floors;k++, i++){
        Handler.add_object<Floor>(floor_lenght,floor_width,0, k*floor_spaceing);
    }

    //right
    for(int i = number_of_floors/2, k=1; i < number_of_floors; k++,i++){
        Handler.add_object<Floor>(floor_lenght, floor_width,window_width-floor_lenght, k*floor_spaceing);
    }
}


