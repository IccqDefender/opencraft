#include <iostream>
#include <memory>
#include "Core/Engine.h"


int main(){
    const auto _engine = std::make_unique<Engine>();

    try {
        _engine->Run(1280, 720, "opencraft");
        _engine->StartMainLoop();
        _engine->Stop();
    }catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}