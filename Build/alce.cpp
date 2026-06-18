#include <cstdlib>
#include <string>

int main(int argc, char* argv[])
{
    std::string command = "python3 cli.py ";

    for(int i = 1; i < argc; i++)
    {
        command += argv[i];
        command += " ";
    }

    system(command.c_str());
}
