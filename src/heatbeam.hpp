#ifndef _HEATBEAM_H
#define _HEATBEAM_H

#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<X11/Xlib.h>
#include<X11/Xutil.h>


namespace heat1d{
// ---
int xerror(const std::string msg){
    std::cerr << msg << std::endl;
    return 1;
}

// ---
struct XPlot{
    Display *display;
    Window win;
    XSizeHints size;
    XSizeHints size_hints;
    GC gc;
    XFontStruct *font_info;
    int screen;
    int width;
    int height;
    int currx;
    int curry;
    // ---
    // initgraphique() => setup()
    void setup();

    // ---
    // closegraphique() => close()
    void close();

    // rattent(int waitm) => wait() ??
    void wait_for_click(bool flag);

    // move2(int x, int y) => movexy(x, y)
    void movexy(int x, int y);

    // line2(int x, int y) => line(x, y)
    void linexy(int x, int y);

    // reffecran() => reffscreen()
    void clear();
};

// ---
enum class ResultMode{ TEXT=0, XPLOT=1 };


// k =
// Te = 
// T0 =
// Tm = 
// a[i] = [...]
// HeatConfig?? float k, T0, Tm, Te, a[M]
struct Config{
    int TLen;   // 100
    double dx;  // 0.1
    int tmax;   // 200

    double Kt; // Diffusion coefficient
    // beam boundary temperature
    double Ta; // T0
    double Tb; // TM
    // Ambient (exterior) temperature
    double Te;

    Config();
    Config(const Config& cfg);
    Config& operator=(const Config& cfg);

    ~Config(){}

    // 
    // void init(double *t, HeatData& data);
    // void relax(double *t, HeatData& data);
    // void showResult(VuMode mode, double *t);

    void read();
};

// ---
class Heat{
public:
    // M = 100
    // dx = 0.1
    // JMAX = 200
    Heat(); // = delete;
    Heat(const Config& config);
    ~Heat();
    
    // init(float *t, Data&)
    // relax(float *t, Data&)
    void run(int tmax = 200);

    // result(float *t, Data&)
    void displayResult(ResultMode mode);
    void configure(const Config& config);

    // tempvar[]
private:
    Config cfg;
    double *T;
    double *A;
    void step();

public:
    void init(); // initialize A and T
};

} // namespace

#endif
