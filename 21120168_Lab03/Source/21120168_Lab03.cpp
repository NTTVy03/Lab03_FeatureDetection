#include "../Header/AppController.h"

int main(int argc, char** argv)
{
    AppController* myApp = new AppController();
    myApp->run(argc, argv);
    delete myApp;
    return 0;
}
