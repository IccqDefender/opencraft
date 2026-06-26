#include "core/engine.h"
#include <memory>


int main(){
  std::unique_ptr<Engine> m_engine = std::make_unique<Engine>();

  m_engine->Start();

  m_engine->Stop();

  return 0;
}