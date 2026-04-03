#include "../WindowManager/WindowManager.h"

class Engine(){
public:
    Engine();
    ~Engine();

    void Run();
    void StartMainLoop();
    void Stop();

private:
    WindowManager* _windowManager = nullptr;
};