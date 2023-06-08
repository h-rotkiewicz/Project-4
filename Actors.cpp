
#include "Actors.h"
#include <iostream>

int IDrawable::get_x() const {
    return x_;
}

int IDrawable::get_y() const {
    return y_;
}

void Floor::draw(Display *disp, long unsigned back_buff, GC const &gc) const override{
    XSetForeground(disp, gc, 0x0000FF);
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_);
}

void Elevator::draw(Display *disp, long unsigned back_buff, GC const &gc) const override{
    XSetForeground(disp, gc, 0xDCDCDC);
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_); //back wall   
    XSetForeground(disp, gc, 0x00FFFF); 
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, wall_thickness); //celling 
    XFillRectangle(disp, back_buff, gc, x_, y_+width_, length_, wall_thickness); //floor
    XFillRectangle(disp, back_buff, gc, x_, y_+wall_thickness, wall_thickness, width_-wall_thickness); // left wall
    XFillRectangle(disp, back_buff, gc, x_+length_-wall_thickness, y_+wall_thickness, wall_thickness, width_-wall_thickness); //right wall
}

void Elevator::move() override{}

void Human::draw(Display *disp, long unsigned back_buff, GC const &gc) const override{
}

void Human::move() override{}

template <typename T>
concept is_IDrawable = std::is_base_of_v<IDrawable, T>;

template <is_IDrawable T >
inline auto ObjectFactory(int width, int height,int x,int y) {
    using ReturnType = std::conditional_t<std::is_base_of_v<IMoveable, T>,
          std::unique_ptr<IMoveable>,
          std::unique_ptr<IDrawable>>;
        return ReturnType(std::make_unique<T>(width, height, x, y));
}

void ObjectObserver::create_floors(int window_width, int window_height, int number_of_floors){
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

void ObjectObserver::create_elevator(int window_width, int window_height){
        add_object<Elevator>(elevator_width, elevator_height,floor_length, window_height-elevator_height-floor_width);

}

template <is_IDrawable OBJECT>
void ObjectObserver::add_object(int width, int height,int x, int y){
            if constexpr (std::is_base_of_v<IMoveable, OBJECT>)
            {
                moveable_container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
            else{
                container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
}

auto& ObjectObserver::get_moveable() const {
    return moveable_container_;
}

auto& ObjectObserver::get_drawable() const {
        return container_;
    }
    