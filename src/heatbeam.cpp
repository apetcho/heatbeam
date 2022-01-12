#include "heatbeam.hpp"
#include<iostream>
#include<cstring>


namespace heat1d{
// ***
void XPlot::close(){
    XUnloadFont(display, font_info->fid);
    XFreeGC(display, gc);
    XCloseDisplay(display);
}

// ***
void XPlot::wait_for_click(bool flag){
    char message[] = "Click to continue...";
    char values[256];
    XEvent event;

    if(flag){
        XDrawString(display, win, gc,
            5, 20, message, strlen(message));

        do{
            XNextEvent(display, &event);
        }while(event.type != ButtonPress && event.type != KeyPress);
        XCheckMaskEvent(display, ButtonPressMask, &event);
        if(event.type == ButtonPress){
            XFlush(display);
        }
    }
}

// ***
void XPlot::setup(){
    XEvent event;
    display = XOpenDisplay(NULL);
    font_info = XLoadQueryFont(display, "7x13");
    
    // XSetErrorHandler((XErrorHandler)xerror);
    // XSetIOErrorHandler((XIOErrorHandler)xerror);

    screen = DefaultScreen(display);
    width = DisplayWidth(display, screen) - 100;
    height = DisplayHeight(display, screen) - 160;
    win = XCreateSimpleWindow(
        display, RootWindow(display, screen),
        50, 80, width, height, 4,
        BlackPixel(display, screen), WhitePixel(display, screen));

    size_hints.flags = PPosition | PSize;
    size_hints.x = 0;
    size_hints.y = 0;
    size_hints.width = width;
    size_hints.height = height;

    XSetStandardProperties(display, win, "xplot",
        NULL, 0, NULL, 0, &size_hints);
    XSelectInput(display, win, ExposureMask | ButtonPressMask);
    gc = XCreateGC(display, win, 0, NULL);
    XSetFont(display, gc, font_info->fid);
    XSetForeground(display, gc, BlackPixel(display, screen));
    XMapWindow(display, win);
    do{
        XNextEvent(display, &event);
    }while(event.type != Expose);
}

// ***
void XPlot::movexy(int x, int y){
    currx = x;
    curry = y;
}

// ***
void XPlot::linexy(int x, int y){
    int xnew = x;
    int ynew = y;
    XDrawLine(display, win, gc, currx, curry, xnew, ynew);
    currx = xnew;
    curry = ynew;
}

// ***
void XPlot::clear(){
    XClearWindow(display, win);
}

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
    T = {};
    A = {};
}

// ***
void Heat::configure(const Config& conf){
    cfg = Config(conf);
    T = {};
    A = {};
}
// ***
Heat::Heat(const Config& conf){
    cfg = Config(conf);
    T = {};
    A = {};
}

// ***
Heat::~Heat(){
    T.clear();
    A.clear();
}

// ***
void Heat::init(){
    auto N = cfg.TLen;
    auto M = static_cast<double>(N);
    auto Ta = cfg.Ta;
    auto Tb = cfg.Tb;
    for(int i=0; i < N; i++){
        auto j = static_cast<double>(i);
        auto aval = (j*j) /(M-1.0)/(M-1.0);
        auto tval = Ta*(M - j)/M + Tb * j/M;
        A.push_back(aval);
        T.push_back(tval);
    }
}


// ***
void Heat::run(int tmax){
    this->cfg.tmax = tmax;
    for(int i=0; i < cfg.tmax; i++){
        step();
    }
}

void Heat::step(){
    auto N = cfg.TLen;
    auto Kt = cfg.Kt;
    auto dx = cfg.dx;
    auto Te = cfg.Te;
    const double kdx2 = Kt / dx / dx;
    for(int i=1; i < N-1; i++){
        T[i] = (kdx2 * (T[i+1] + T[i-1]) + A[i]*Te)/(A[i] + 2.0*kdx2);
    }
}

// ***
void Heat::displayResult(ResultMode mode){
    if(mode == ResultMode::XPLOT){
        XPlot plot;
        plot.setup();
        plot.movexy(0, (int)T[0]);
        for(int i=1; i < cfg.TLen; i++){
            plot.linexy(i, (int)T[i]);
        }
        plot.wait_for_click(true);
        plot.close();
    }else if(mode == ResultMode::TEXT){
        for(int i=0; i < cfg.TLen; i++){
            std::cout << T[i] << std::endl;
        }
    }

    return;
}


} // namespace heat1d
