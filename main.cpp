#include "Eng.h"
/* 
 *TODO 
 * 1. Add build instructions
 * 2. Add elevator and floor class that inherit from drawable
 * 3. Add Event class that handles events with an interface
 * 4. and more ...
 * 5. change auto in function parameters to actual types
 * */


int main() {
    try{
    DisplayManager& disp = DisplayManager::GetInstance();
    const int number_of_floors = 12;
    ObjectHandler handler; 
    Create_Floors(handler, disp.get_width(), disp.get_height(), number_of_floors);
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


