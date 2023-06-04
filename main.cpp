#include "Eng.h"
constexpr int floor_width = 20;
constexpr int floor_lenght = 200;
/* 
 *TODO 
 * 1. Add build instructions
 * 2. Add elevator and floor class that inherit from drawable
 * 3. Add Event class that handles events with an interface
 * 4. and more ...
 * 5. change auto in function parameters to actual types
 * */

void Create_Floors(auto &cont, int window_width, int window_height, int number_of_floors){
    int floor_spaceing = window_height*2/(number_of_floors);

    //left
    int k = 1;
    for(int i = 0; i < number_of_floors;k++, i++){
        cont[i] = std::make_unique<Floor>(Floor(floor_lenght, floor_width, 0, k*floor_spaceing));
    }

    //right
    for(int i = number_of_floors/2, k=1; i < number_of_floors; k++,i++){
        cont[i] = std::make_unique<Floor>(Floor(floor_lenght,floor_width, window_width-floor_lenght, k*floor_spaceing));
    }
}

int main() {
    try{
    DisplayManager& disp = DisplayManager::GetInstance();
    const int number_of_floors = 12;
    std::vector<std::unique_ptr<IDrawable>> cont;
    cont.resize(number_of_floors);
    Create_Floors(cont, disp.get_width(), disp.get_height(),number_of_floors);
    disp.event_loop(cont);
    return 0;
    }
    catch(std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
 }


