#include <iostream>
#include "LoginServer.h"
int main()
{
    LoginServer loginServer;
    loginServer.Run();
    while (loginServer._bShutdown == false)
    {
        loginServer.ServerControl();
        loginServer.Monitor();
        Sleep(1000);
    }
}
