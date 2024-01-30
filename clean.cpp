#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

void cleanAllFilesExceptCPP(const fs::path& directory) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        auto ext = entry.path().extension();
            if (ext == ".exe" || ext == ".ilk" || ext == ".pdb" || ext == ".obj") {
                fs::remove(entry.path());
            }
    }
}

void cleanStaffFilesExceptCPPandEXE(const fs::path& directory) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (!fs::is_directory(entry)) {
            auto ext = entry.path().extension();
            if (ext == ".ilk" || ext == ".pdb" || ext == ".obj") {
                fs::remove(entry.path());
            }
        }
    }
}

int main(int argc, char* argv[]) {
    fs::path directory = fs::current_path();
    if(argc > 1){
        std::string arg = argv[1];

        if (argc > 2) {
            directory = argv[2];
        }

        if (arg == "-all" || arg == "-a" || arg == "-ALL" || arg == "-A") {
            cleanAllFilesExceptCPP(directory);
        }
        else if (arg == "-staff" || arg == "-S" || arg == "-STAFF" || arg == "-s") {
            cleanStaffFilesExceptCPPandEXE(directory);
        }
        else if (arg == "help"){
            std::cout << "Delete all staffs came from MSVC compiler. (Authored by Bestar)" << std::endl << std::endl;
            std::cout << "CLEAN -A/-ALL [drive:path]" << std::endl;
            std::cout << "CLEAN [-S]/[-STAFF] [drive:path]" << std::endl << std::endl;
            std::cout << "Note: [*] means that * can be omitted." << std::endl << std::endl;
            std::cout << "\t-A : Remove all files exclude *.cpp source files." << std::endl;
            std::cout << "\t     These files can be *.exe, *.ilk, *.pdb and *.obj."<< std::endl;
            std::cout << "\t[-S] : Remove all files exclude *.cpp files and *.exe files." << std::endl;
            std::cout << "\t     These files can be *.ilk, *.pdb and *.obj."<< std::endl << std::endl;
        }
        else {
            std::cout << "Invalid argument" << std::endl;
            return 1;
        }
    } else {
        cleanStaffFilesExceptCPPandEXE(directory);
    }

    return 0;
}
