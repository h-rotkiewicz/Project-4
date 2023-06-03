#include "Eng.h"
constexpr int floor_width = 20;
constexpr int floor_lenght = 300;
constexpr int floor_spaceing = 10;
/* 
 *TODO 
 * 1. Add build instructions
 * 2. Add elevator and floor class that inherit from drawable
 * 3. Add Event class that handles events with an interface
 * 4. and more ...
 * */
int main() {
    DisplayManager& disp = DisplayManager::GetInstance();
    std::array<IDrawable*,3> cont ;
    for(int i = 0; i < 3; i++){
        cont[i] = new Floor(floor_lenght, floor_width, 0, i*(floor_width + floor_spaceing));
    }
    disp.event_loop(cont);
    system("sleep 5");
    return 0;
}


