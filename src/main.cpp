#include "Eng.h"
/* 
 *TODO 
 * 1. Add build instructions
 * 2. separete the declaration from the implementation
 * */


int main() {
    try{
        const auto number_of_floors = 3;
        DisplayManager& disp = DisplayManager::GetInstance();
        ObjectObserver handler; 
        handler.create_floors(disp.get_width(), disp.get_height(), number_of_floors);
        handler.create_elevator(disp.get_width(), disp.get_height());
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
