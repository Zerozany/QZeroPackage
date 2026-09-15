find_package(spdlog CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(httplib CONFIG REQUIRED)

find_library(LIBUSB_1_LIB NAMES usb-1.0)

if(NOT LIBUSB_1_LIB)
    message(FATAL_ERROR "libusb-1.0 library not found")
endif()

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    spdlog::spdlog
    ${LIBUSB_1_LIB}
    OpenSSL::SSL
    OpenSSL::Crypto
    httplib::httplib
)
