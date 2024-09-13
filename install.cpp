#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <fstream>

namespace fs = std::filesystem;

// Function to copy a file from source to destination
void copyFile(const std::string &source, const std::string &destination) {
  try {
    fs::copy(source, destination, fs::copy_options::overwrite_existing);
    std::cout << "Copied " << source << " to " << destination << "\n";
  } catch (fs::filesystem_error &e) {
    std::cerr << "Error copying file: " << e.what() << '\n';
  }
}

// Function to set permissions to a file (e.g., make it executable)
void setPermissions(const std::string &file, fs::perms permissions) {
  try {
    fs::permissions(file, permissions);
    std::cout << "Set permissions for " << file << "\n";
  } catch (fs::filesystem_error &e) {
    std::cerr << "Error setting permissions: " << e.what() << '\n';
  }
}

int main() {
  std::cout << "Installing...\n";

  std::string appName = "tunacalc";
  std::string appBinaryPath = "./bin/" + appName;
  std::string targetPath = "/usr/local/bin";
  std::string targetBinaryPath = targetPath + "/" + appName;

  // 1. Copy the application binary to /usr/local/bin
  copyFile(appBinaryPath, targetPath);

  // 2. Set executable permissions (for everyone)
  setPermissions(targetBinaryPath, fs::perms::others_exec | fs::perms::others_read | fs::perms::others_write);

  // 3. Print success message
  std::cout << "Installation completed successfully!\n";

  return 0;
}
