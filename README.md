# MEV-Resistant BB

This document provides instructions for setting up and building the project using Conan and CMake.

## Prerequisites

- **Conan** (>= 1.29)
- **CMake** (>= 3.16)
- **Visual Studio** (>= 2019)

Ensure you have Conan and CMake installed, as well as Visual Studio with C++ development tools.

## Steps to Build the Project

1. **Clone the repository**:

   ```Power Shell
   git clone <repository_url>
   cd <cloned_repo_path>
   ```

2. **Detect the Conan profile**:

   ```Power Shell
   conan profile detect --force
   ```

3. **Install dependencies**:

   ```Power Shell
   conan install . --output-folder=out/build --build=missing
   ```

4. **Configure the project**:

   ```Power Shell
   cd out/build
   cmake ../.. -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE="build/generators/conan_toolchain.cmake" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW
   ```

5. **Build the project**:

   ```Power Shell
   cmake --build . --config Release
   ```

## Notes

- Replace `<repository_url>` with the actual repository link.
- This guide assumes you're using **Visual Studio 2019**. You can adjust the generator accordingly if you're using a different version or IDE.

Hoping to add more Linux functionality in the near future :)
