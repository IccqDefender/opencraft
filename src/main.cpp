#include <iostream>
#include <memory>
#include "Core/Engine.h"

using namespace opencraft;

int main(){
    const auto _engine = new Engine(1280, 720, "opencraft");

    try {
        _engine->Run();
        //_engine->StartMainLoop();
        _engine->Stop();
        delete _engine;
    }catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}