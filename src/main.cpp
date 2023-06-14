#include "Eng.h"


constexpr static auto number_of_floors = 3;
const int Locations::spaceing_ = DisplayManager::window_height/number_of_floors;

int main() {
    try{
        DisplayManager& disp = DisplayManager::GetInstance();
        ObjectObserver handler; 
        handler.create_floors(disp.window_width, disp.window_height, number_of_floors);
        handler.create_elevator(disp.window_width, disp.window_height);
        handler.create_buttons(disp.window_width, disp.window_height, number_of_floors);
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
