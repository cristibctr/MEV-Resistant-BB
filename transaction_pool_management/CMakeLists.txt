# CMakeList.txt : CMake project for transaction_pool_management, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (transaction_pool_management "transaction_pool_manager.cpp" "transaction_pool_manager.h" "transaction.h" "transaction.cpp" "encrypted_transaction.h" "encrypted_transaction.cpp" "encryption_utils.h" "encryption_utils.cpp" "config.h" "config.cpp" "key_management.h" "key_management.cpp" "network_interface.h" "network_interface.cpp" "transaction_queue.h" "transaction_queue.cpp")

find_package(jsoncpp REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(transaction_pool_management JsonCpp::JsonCpp openssl::openssl)

# TODO: Add tests and install targets if needed.
