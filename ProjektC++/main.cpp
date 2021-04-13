#include "Application.h"
#include "Display.h"
#include <conio.h>
#include <iostream>
#include "World/Attacks/Attack.h"
int main()try{
    Application app;
    app.runMainLoop();

    _getch();
    return 0;
}
catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
}
catch (...) {
    std::cerr << "Cos zlapano" << std::endl;
}
