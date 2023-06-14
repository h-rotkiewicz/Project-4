#pragma once
#include <X11/Xlib.h>
#include <X11/extensions/Xdbe.h> // for double buffering
#include <X11/Xutil.h>
#include <vector>
#include <memory>
#include <iostream>
#include <type_traits>


class ObjectObserver;

static consteval double get_dt() {
    return 0.001;
} 

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
        uint get_length() const { return length_;}   
        uint get_width() const{ return width_;}
        virtual ~IDrawable() = default;
};

class IMoveable : public IDrawable{
    protected:
        friend class DisplayManager; // only draw objects from DisplayManager 
        int x_target_ =-1;
        int y_target_ =-1;
        double speed_ = 1;
        int max_speed_ = 10;
        double acceleration_ = speed_ * get_dt();
    public:
        virtual void move() = 0;
        virtual void set_target(int x, int y) {
            std::cout << "set target" << std::endl;
            x_target_ = x;
            y_target_ = y;
        }
        virtual ~IMoveable() = default;
        virtual double get_speed() const = 0;
        virtual void set_pos(int x, int y);
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
        double get_speed() const override;
        Elevator(uint length, uint width,  int x, int y): IMoveable(length, width, x, y) {}
};

class Human : public IMoveable{
    private:
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const override;
        void move() override;
    public:
        double get_speed() const override;
        Human(uint length, uint width,  int x, int y): IMoveable(length, width, x, y) {}
};

struct Locations{
    enum Level {
        NONE = -1,
        GROUND,
        FIRST,
        SECOND,
        THIRD,
        FOURTH,
        FIFTH,
    };
    static int convert_to_y(Level level) {
        return (int)level * spaceing_; 
    }
    private:
    static const int spaceing_ ;
};

class Button : public IDrawable {
    private:
        Locations::Level level_;
        void draw(Display *disp, long unsigned back_buff, GC const &gc) const;
        friend class DisplayManager; // only draw objects from DisplayManager 
    public:
        Button(uint length, uint width,  int x, int y, Locations::Level level): IDrawable(length, width, x, y), level_(level) {}
        void press(ObjectObserver const &);
        Locations::Level get_level() const;
};


//since 2 objects have nearly the same constructor, we can use a template to avoid code duplication
//in case elevator or person object has different constructors, we will have to rewrite this
template <typename T>
concept is_IDrawable = std::is_base_of_v<IDrawable, T>;

//Return type deduction based on inheritance
template <is_IDrawable T >
inline auto ObjectFactory(int width, int height,int x,int y, Locations::Level level =Locations::Level::NONE);

class ObjectObserver{
    private:
        using index = int;
        std::vector<std::unique_ptr<IDrawable>> container_;
        std::vector<std::unique_ptr<IMoveable>> moveable_container_;
        std::vector<std::unique_ptr<Button>> button_container_;
        const int floor_width = 20;
        const int floor_length = 200;
        const int elevator_width = 200;
        const int elevator_height = 120;
        int floor_spacing_ = 0;
        index elevator_ = -1;
    public:
        template <is_IDrawable OBJECT>
            void add_object(int width, int height,int x,int y,
                    Locations::Level level =Locations::Level::NONE);

        auto& get_moveable() const {
            return moveable_container_;
        }

        auto& get_drawable() const {
            return container_;
        }
        
        void was_button_pressed(int x, int y) const {
            for(auto const &button : button_container_){
                if(true){
                    button->press(*this);
                }
            }
        }
    
        auto & get_buttons()const {
            return button_container_;
        }

        auto& get_elevator() const {
            if (elevator_ == -1){
                throw std::runtime_error("Elevator not found");
            }
            return moveable_container_[elevator_]; 
        }

        void create_floors(int window_width, int window_height, int number_of_floors);
        void create_elevator(int window_width, int window_height);
        void create_buttons(int window_width, int window_height, int number_of_floors);
};

class ButtonHandler {
    
};

