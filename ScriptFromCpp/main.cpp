
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    cout << "Calling some_script.sh" << endl;
    system("./some_script.sh");
    return 0;
}
