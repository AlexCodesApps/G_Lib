#include <filesystem>
#include <string>
#include <iostream>

using namespace std;

const string lib_path = "/usr/local/include/G_Lib_C/";

void Copy_To_G_Lib() {
    for (auto file : filesystem::directory_iterator(lib_path)) {
        if (file.path().extension() != ".h") continue;
        string file_to_copy = file.path().string();
        string operation = "cp " + file_to_copy + " .";
        cout << "Created Terminal Command : [" << operation << "]\n";
        system(operation.c_str());
    }
}

void Copy_To_G_Lib_C() {
    for (auto file : filesystem::directory_iterator(filesystem::current_path().c_str())) {
        if (file.path().extension() != ".h") continue;
        string file_to_copy = file.path().string();
        string operation = "cp " + file_to_copy + " " + lib_path;
        cout << "Created Terminal Command : [" << operation << "]\n";
        system(operation.c_str());
    }
}

int main(int argc, char ** argv) {
    if (argc > 1) {if (strncmp(argv[1], "to", 2) == 0) Copy_To_G_Lib_C();}
    else Copy_To_G_Lib();
}