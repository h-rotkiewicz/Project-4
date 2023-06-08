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
        int get_x() const;
        int get_y() const;
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
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override;
    public:
        Floor(uint length, uint width,  int x, int y): IDrawable(length, width, x, y) {}
};

class Elevator : public IMoveable{
    private:
    const int wall_thickness=10;
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override;
        void move() override;
    public:
        Elevator(uint length, uint width,  int x, int y): IMoveable(length, width, x, y) {}
};

class Human : public IMoveable{
    private:
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override;
        void move() override;
    public:
        Human(uint length, uint width,  int x, int y): IMoveable(length, width, x, y) {}
};

//since 2 objects have nearly the same constructor, we can use a template to avoid code duplication
//in case elevator or person object has different constructors, we will have to rewrite this
template <typename T>
concept is_IDrawable = std::is_base_of_v<IDrawable, T>;

//Return type deduction based on inheritance
template <is_IDrawable T >
inline auto ObjectFactory(int width, int height,int x,int y);

class ObjectObserver{
    private:
    std::vector<std::unique_ptr<IDrawable>> container_;
    std::vector<std::unique_ptr<IMoveable>> moveable_container_;
    const int floor_width = 20;
    const int floor_length = 200;
    const int elevator_width = 200;
    const int elevator_height = 120;
    public:
    template <is_IDrawable OBJECT>
        void add_object(int width, int height,int x, int y);
    // So we can use range based for loop in DisplayManager
    auto& get_moveable() const {
    return moveable_container_;
    }
    auto& get_drawable() const {
        return container_;
    }
    void create_floors(int window_width, int window_height, int number_of_floors);
    void create_elevator(int window_width, int window_height);
};
