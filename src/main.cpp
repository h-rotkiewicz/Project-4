#include "Eng.h"


constexpr static auto number_of_floors = 3;
const int Locations::spaceing_ = number_of_floors/DisplayManager::window_height_;

int main() {
    try{
        DisplayManager& disp = DisplayManager::GetInstance();
        ObjectObserver handler; 
        handler.create_floors(disp.window_width_, disp.window_height_, number_of_floors);
        handler.create_elevator(disp.window_width_, disp.window_height_);
        while(true){
            disp.render_objects(handler);
        }
        return 0;
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
 }
