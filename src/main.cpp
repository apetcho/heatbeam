#include "heatbeam.hpp"


int main(){
    heat1d::Config config;
    heat1d::Heat heat;
    heat1d::ResultMode mode;

    config.read();
    // heat = heat1d::Heat(config);
    heat.configure(config);
    heat.init();
    heat.run();

    mode = heat1d::ResultMode::XPLOT;
    heat.displayResult(mode);

    return 0;
}
