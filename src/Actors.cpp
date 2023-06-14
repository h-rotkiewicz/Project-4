#include "Actors.h"
#include <algorithm>
#include <iostream>
int IDrawable::get_x() const {
    return x_;
}

int IDrawable::get_y() const {
    return y_;
}

void Floor::draw(Display *disp, long unsigned back_buff, GC const &gc) const{
    XSetForeground(disp, gc, 0x0000FF);
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_);
}

void Elevator::draw(Display *disp, long unsigned back_buff, GC const &gc) const{
    XSetForeground(disp, gc, 0xDCDCDC);
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_); //back wall   
    XSetForeground(disp, gc, 0x00FFFF); 
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, wall_thickness); //celling 
    XFillRectangle(disp, back_buff, gc, x_, y_+width_, length_, wall_thickness); //floor
    XFillRectangle(disp, back_buff, gc, x_, y_+wall_thickness, wall_thickness, width_-wall_thickness); // left wall
    XFillRectangle(disp, back_buff, gc, x_+length_-wall_thickness, y_+wall_thickness, wall_thickness, width_-wall_thickness); //right wall
}

double Elevator::get_speed() const{
    return speed_;
}

double Human::get_speed() const{
    return speed_;
}

void IMoveable::set_pos(int x, int y){
    x_ = x;
    y_ = y;
}
void Elevator::move() {
    static double buffer = 0;
    if(x_target_ < 0 || y_target_ < 0) 
        return;
    buffer += acceleration_;
    if(buffer <= 1)
        return;
    else {

        if(speed_ < max_speed_)
            speed_ = std::min(speed_ + buffer, static_cast<double>(max_speed_));
        
        double distance_to_target = std::abs(y_ - y_target_);
        double threshold_distance = 10.0; 
        if (distance_to_target <= threshold_distance) {
            double deceleration_factor = distance_to_target / threshold_distance;
            speed_ *= deceleration_factor;
        }
        y_ <= y_target_ ? y_+=speed_ : y_-=speed_;
        buffer = 0;
    }
}

void Button::draw(Display *disp, long unsigned back_buff, GC const &gc) const{
    XSetForeground(disp, gc, 0x000000);
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_);
}

void Button::press(ObjectObserver const& obs){
    std::cout << "Button pressed" << Locations::convert_to_y(level_) <<std::endl;
    obs.get_elevator()->set_target(0,Locations::convert_to_y(level_));
}

Locations::Level Button::get_level() const{
    return level_;
}

template <is_IDrawable T >
inline auto ObjectFactory(int width, int height,int x,int y, Locations::Level level) {
    if constexpr (std::is_same_v<Button, T>)
        return std::make_unique<T>(width, height, x,level); // Button is not of an abstract type and can't have an interface
    else
        return std::make_unique<T>(width, height, x, y);
}

void ObjectObserver::create_floors(int window_width, int window_height, int number_of_floors){
        floor_spacing_ = window_height/(number_of_floors);

        //left
        int k = 1;
        for(int i = 0; i < number_of_floors;k++, i++){
            add_object<Floor>(floor_length,floor_width,0, k*floor_spacing_-floor_width);
        }

        //right
        for(int i = number_of_floors/2, k=1; i < number_of_floors; k++,i++){
            add_object<Floor>(floor_length, floor_width,window_width-floor_length, k*floor_spacing_+floor_spacing_/2-floor_width);
        }
}

void ObjectObserver::create_elevator(int window_width, int window_height){
        add_object<Elevator>(elevator_width, elevator_height,floor_length, window_height-elevator_height-floor_width);

}

void ObjectObserver::create_buttons(int window_width, int window_height, int number_of_floors){
        int k = 1;
        for(int i = 0; i < number_of_floors; k++, i++){
            add_object<Button>(50, 50, floor_length/2, k*floor_spacing_-floor_width,(Locations::Level)k);
            std::cout << "Button created" << Locations::convert_to_y((Locations::Level)k) <<std::endl;
        }
}

template <is_IDrawable OBJECT>
void ObjectObserver::add_object(int width, int height,int x, int y, Locations::Level level){
            if constexpr (std::is_base_of_v<IMoveable, OBJECT>)
            {
                if constexpr (std::is_same_v<OBJECT, Elevator>)
                {
                    elevator_ = moveable_container_.size();
                }
                moveable_container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
            else if constexpr (std::is_same_v<OBJECT, Button>)
            {
                button_container_.push_back(ObjectFactory<OBJECT>(width,height,x,y, level));
                return;
            }
            else{
                container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
}
