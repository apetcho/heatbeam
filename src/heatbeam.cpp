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
Config::Config(const Config& cfg){
    this->dx = cfg.dx;
    this->Kt = cfg.Kt;
    this->Ta = cfg.Ta;
    this->Tb = cfg.Tb;
    this->Te = cfg.Te;
    this->TLen = cfg.TLen;
    this->tmax = cfg.tmax;
}

// ***
Config& Config::operator=(const Config& cfg){
    if(this != &cfg){
        this->dx = cfg.dx;
        this->Kt = cfg.Kt;
        this->Ta = cfg.Ta;
        this->Tb = cfg.Tb;
        this->Te = cfg.Te;
        this->TLen = cfg.TLen;
        this->tmax = cfg.tmax;
    }

    return *this;
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

// ***
Heat::Heat(const Config& config){
    cfg = config;
    T = new double[cfg.TLen];
    A = new double[cfg.TLen];
}

// ***
Heat::~Heat(){
    if(T){ delete [] T; }
    if(A){ delete [] A; }
}

// ***
void Heat::init(){
    auto N = cfg.TLen;
    auto M = static_cast<double>(N);
    for(int i=0; i < N; i++){
        auto j = static_cast<double>(i);
        A[i] = (j*j) /(M-1.0)/(M-1.0);
    }
    auto Ta = cfg.Ta;
    auto Tb = cfg.Tb;
    for(int i=0; i < N; i++){
        auto j = static_cast<double>(i);
        T[i] = Ta*(M - j)/M + Tb * j/M;
    }
}


// ***
void Heat::run(){
    auto N = cfg.TLen;
    auto Kt = cfg.Kt;
    auto dx = cfg.dx;
    auto Te = cfg.Te;
    const double kdx2 = Kt / dx / dx;
    for(int i=1; i < N-1; i++){
        T[i] = (kdx * (T[i+1] + T[i-1]) + A[i]*Te)/(A[i] + 2.0*kdx2);
    }
}

} // namespace heat1d
