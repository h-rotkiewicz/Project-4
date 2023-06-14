#include "Actors.h"
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

void Elevator::move(){
    static double buffer = 0; // since gc_.x is int, we need to accumulate the speed
    if(x_target_ < 0 || y_target_ < 0) 
        return;
    buffer += acceleration_;
    if(buffer <= 1)
        return;
    else {
        if(speed_ < max_speed_)
            speed_ += buffer;
 // I don't know why it's 9, but it works                                                              
 // have to figure out why I don't know                                                                
 // no variable is equal to 9                                                                          
 // this is needed so the elevator doesn't                                                             
 // wobble when it stops                                                                               
 // use the set target function to set the target                                                      
 // elevator will only consider the y coordinate                                                       
 // and human will consider both x and y                 {
        if(y_ == y_target_ + 9|| y_ == y_target_ - 9) 
        {
            speed_ = 0;
        }       
        y_ <= y_target_ ? y_=+speed_ : y_-=speed_;
        buffer = 0;
    }

}

void Button::draw(Display *disp, long unsigned back_buff, GC const &gc) const{
    XSetForeground(disp, gc, 0x000000);
    XFillRectangle(disp, back_buff, gc, x_, y_, length_, width_);
}

void Button::press(){
    pressed_ = true;
}

void Button::release(){
    pressed_ = false;
}

bool Button::is_pressed() const{
    return pressed_;
}

Locations::Level Button::get_level() const{
    return level_;
}   

void Human::draw(Display *disp, long unsigned back_buff, GC const &gc) const{}

void Human::move(){
    x_ < x_target_ ? x_=+speed_ : x_-=speed_;
    y_ < y_target_ ? y_=+speed_ : y_-=speed_;
}



template <is_IDrawable T >
inline auto ObjectFactory(int width, int height,int x,int y, Locations::Level level) {
    using ReturnType = std::conditional_t<std::is_base_of_v<IMoveable, T>,
          std::unique_ptr<IMoveable>,
          std::unique_ptr<IDrawable>>;
    if constexpr (std::is_same_v<Button, T>)
        return ReturnType(std::make_unique<T>(width, height, x, y, level));
    else
    return ReturnType(std::make_unique<T>(width, height, x, y));
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
            add_object<Button>(100, 100,1, 1, (Locations::Level)k);
        }
}

template <is_IDrawable OBJECT>
void ObjectObserver::add_object(int width, int height,int x, int y, Locations::Level level){
            if constexpr (std::is_base_of_v<IMoveable, OBJECT>)
            {
                if constexpr (std::is_same_v<OBJECT, Elevator>)
                {
                    elevator_index_ = moveable_container_.size();
                }
                moveable_container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
            else{
                container_.push_back(ObjectFactory<OBJECT>(width,height,x,y));
            }
}
