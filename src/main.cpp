#include "core/Core.h"

#include <memory>

int main() {

    std::unique_ptr<Core> m_core = std::make_unique<Core>();

    m_core->run();

    m_core->stop();

    return 0;
}