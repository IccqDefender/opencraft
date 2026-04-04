#include <iostream>
#include <memory>
#include "Core/Engine.h"


int main(){
    std::unique_ptr<Engine> _engine = std::make_unique<Engine>();
    _engine->Run();
    _engine->StartMainLoop();
    _engine->Stop();
    
    return 0;
}