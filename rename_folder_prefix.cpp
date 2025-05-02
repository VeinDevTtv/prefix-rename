// file: rename_folder_prefix.cpp

#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm> // for std::transform

namespace fs = std::filesystem;

void rename_folder_prefix(const std::string& base_dir,
                          const std::string& old_prefix,
                          const std::string& new_prefix,
                          bool dry_run,
                          bool ignore_case) {
    int renamed_count = 0;
    int skipped_count = 0;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(base_dir)) {
            if (entry.is_directory()) {
                std::string folder_name = entry.path().filename().string();

                std::string old_prefix_cmp = old_prefix;
                std::string folder_name_cmp = folder_name;
                if (ignore_case) {
                    std::transform(old_prefix_cmp.begin(), old_prefix_cmp.end(), old_prefix_cmp.begin(), ::tolower);
                    std::transform(folder_name_cmp.begin(), folder_name_cmp.end(), folder_name_cmp.begin(), ::tolower);
                }

                if (folder_name_cmp.rfind(old_prefix_cmp, 0) == 0) { // starts with old_prefix
                    std::string suffix = folder_name.substr(old_prefix.size());
                    std::string new_name = new_prefix + suffix;

                    fs::path old_path = entry.path();
                    fs::path new_path = old_path.parent_path() / new_name;

                    if (fs::exists(new_path)) {
                        std::cerr << "⚠️  Warning: Target already exists, skipping: " << new_path << '\n';
                        ++skipped_count;
                        continue;
                    }

                    if (dry_run) {
                        std::cout << "[Dry-Run] Would rename: " << old_path << " -> " << new_path << '\n';
                    } else {
                        fs::rename(old_path, new_path);
                        std::cout << "✅ Renamed: " << old_path << " -> " << new_path << '\n';
                        ++renamed_count;
                    }
                }
            }
        }

        std::cout << "\n--- Summary ---\n";
        std::cout << "Total renamed folders: " << renamed_count << '\n';
        std::cout << "Total skipped (already exists): " << skipped_count << '\n';

    } catch (const fs::filesystem_error& e) {
        std::cerr << "❌ Filesystem error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0]
                  << " <directory> <old_prefix> <new_prefix> [--dry-run|-n] [--ignore-case|-i]\n";
        return 1;
    }

    std::string base_dir = argv[1];
    std::string old_prefix = argv[2];
    std::string new_prefix = argv[3];

    bool dry_run = false;
    bool ignore_case = false;

    for (int i = 4; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--dry-run" || arg == "-n") {
            dry_run = true;
        } else if (arg == "--ignore-case" || arg == "-i") {
            ignore_case = true;
        }
    }

    rename_folder_prefix(base_dir, old_prefix, new_prefix, dry_run, ignore_case);

    return 0;
}

// Example usage:
// rename_folder_prefix.exe "C:\path\to\base_dir" "old_prefix" "new_prefix" --dry-run
// rename_folder_prefix.exe "C:\path\to\base_dir" "old_prefix" "new_prefix" --ignore-case
// rename_folder_prefix.exe "C:\path\to\base_dir" "old_prefix" "new_prefix" --dry-run --ignore-case
