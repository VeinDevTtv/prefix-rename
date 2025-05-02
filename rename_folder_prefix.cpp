// file: rename_folder_prefix.cpp

#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void rename_folder_prefix(const std::string& base_dir, const std::string& old_prefix, const std::string& new_prefix) {
    try {
        for (const auto& entry : fs::directory_iterator(base_dir)) {
            if (entry.is_directory()) {
                std::string folder_name = entry.path().filename().string();

                if (folder_name.rfind(old_prefix, 0) == 0) { // starts with old_prefix
                    std::string suffix = folder_name.substr(old_prefix.size());
                    std::string new_name = new_prefix + suffix;

                    fs::path old_path = entry.path();
                    fs::path new_path = old_path.parent_path() / new_name;

                    fs::rename(old_path, new_path);
                    std::cout << "Renamed: " << old_path << " -> " << new_path << '\n';
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

int main() {
    std::string base_dir = "resources";
    std::string old_prefix = "vein-";
    std::string new_prefix = "good-";

    rename_folder_prefix(base_dir, old_prefix, new_prefix);

    return 0;
}
