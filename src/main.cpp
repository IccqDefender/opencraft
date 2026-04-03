#include <iostream>
#include "./Core/Engine.h"


int main(){
    Engine* engine = new Engine();

    engine->Run();
    engine->Stop();

    delete engine;
    
    return 0;
}