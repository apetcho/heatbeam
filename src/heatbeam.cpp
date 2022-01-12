#include "heatbeam.hpp"

namespace heat1d{
// ***
Config::Config(){
    TLen = 100;
    tmax = 200;
    dx = 0.1;
    // ----
    Kt = 0.0;
    Ta = 0.0;
    Tb = 0.0;
    Te = 0.0;
}

// ***
void Config::read(){
    std::cout << "Enter Kt:\n>> ";
    std::cin >> Kt;
    std::cout << "Enter Ta:\n>> ";
    std::cin >> Ta;
    std::cout << "Enter Tb:\n>> ";
    std::cin >> Tb;
    std::cout << "Enter Te:\n>> ";
    std::cin >> Te;
    return;
}

//
Heat::Heat(){
    cfg.dx = 0.0;
    cfg.TLen = 0;
    cfg.Ta = 0.0;
    cfg.Tb = 0.0;
    cfg.Te = 0.0;
    cfg.tmax = 0;
    cfg.Kt = 0.0;
    T = nullptr;
    A = nullptr;
}

} // namespace heat1d
