#include <X11/Xlib.h>
#include <X11/extensions/Xdbe.h> // for double buffering
#include <X11/Xutil.h>
#include <vector>
#include <memory>
#include <iostream>
#include <type_traits>

class IDrawable{
    protected:
        uint length_;
        uint width_;
        int x_;
        int y_;
        virtual void draw(Display *disp, XdbeBackBuffer, GC const &gc) const = 0;
        friend class DisplayManager; // only draw objects from DisplayManager 
    public:
        IDrawable(uint length, uint width,  int x, int y): length_(length), width_(width),  x_(x), y_(y) {}
        int get_x() const {
            return x_;
        }
        int get_y() const {
            return y_;
        }
        virtual ~IDrawable() = default;
};

class IMoveable : public IDrawable{
    protected:
        virtual void move() = 0;
        friend class DisplayManager; // only draw objects from DisplayManager 
    public:
        virtual ~IMoveable() = default;
        IMoveable(uint length, uint width,  int x, int y): IDrawable(length, width, x, y) {}
};

class Floor : public IDrawable{
    private:
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override  {
            XSetForeground(disp, gc, 0x0000FF);
            XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_);
        }

    public:
        Floor(uint length, uint width,  int x, int y): IDrawable(length, width, x, y) {}
};

class Elevator : public IMoveable{
    private:
    const int wall_thickness=10;
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override {
            XSetForeground(disp, gc, 0xDCDCDC);
            XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_); //back wall   
            XSetForeground(disp, gc, 0x00FFFF);
            XFillRectangle(disp, back_buff, gc, x_, y_, length_, wall_thickness); //celling 
            XFillRectangle(disp, back_buff, gc, x_, y_+width_, length_, wall_thickness); //floor
            XFillRectangle(disp, back_buff, gc, x_, y_+wall_thickness, wall_thickness, width_-wall_thickness); // left wall
            XFillRectangle(disp, back_buff, gc, x_+length_-wall_thickness, y_+wall_thickness, wall_thickness, width_-wall_thickness); //right wall
        }
        void move() override {}
    public:
        Elevator(uint length, uint width,  int x, int y): IMoveable(length, width, x, y) {}
};

class Human : public IMoveable{
    private:
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override {
            
        }
        void move() override {}
    public:
        Human(uint length, uint width,  int x, int y): IMoveable(length, width, x, y) {}
};

//since 2 objects have nearly the same constructor, we can use a template to avoid code duplication
//in case elevator or person object has different constructors, we will have to rewrite this
template <typename T>
concept is_IDrawable = std::is_base_of_v<IDrawable, T>;

//Return type deduction based on inheritance
template <is_IDrawable T >
inline auto ObjectFactory(int width, int height,int x,int y) {
    using ReturnType = std::conditional_t<std::is_base_of_v<IMoveable, T>,
          std::unique_ptr<IMoveable>,
          std::unique_ptr<IDrawable>>;
        return ReturnType(std::make_unique<T>(width, height, x, y));
}

class ObjectObserver{
    std::vector<std::unique_ptr<IDrawable>> container_;
    std::vector<std::unique_ptr<IMoveable>> moveable_container_;
    const int floor_width = 20;
    const int floor_length = 200;
    const int elevator_width = 200;
    const int elevator_height = 120;

    public:
    template <is_IDrawable OBJECT>
        void add_object(int width, int height,int x, int y){
            if constexpr (std::is_base_of_v<IMoveable, OBJECT>)
            {
                moveable_container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
            else{
                container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
        }

    // So we can use range based for loop in DisplayManager
    auto& get_moveable() const {
        return moveable_container_;
    }
    auto& get_drawable() const {
        return container_;
    }

    void create_floors(int window_width, int window_height, int number_of_floors){
        int floor_spacing = window_height/(number_of_floors);

        //left
        int k = 1;
        for(int i = 0; i < number_of_floors;k++, i++){
            add_object<Floor>(floor_length,floor_width,0, k*floor_spacing-floor_width);
        }

        //right
        for(int i = number_of_floors/2, k=1; i < number_of_floors; k++,i++){
            add_object<Floor>(floor_length, floor_width,window_width-floor_length, k*floor_spacing+floor_spacing/2-floor_width);
        }
    }

    void create_elevator(int window_width, int window_height){
        add_object<Elevator>(elevator_width, elevator_height,floor_length, window_height-elevator_height-floor_width);
    }
};
