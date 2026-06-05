#include "UsbManager.h"
#include <print>

UsbManager::UsbManager()
{
    std::invoke(&UsbManager::init, this);
}

UsbManager::~UsbManager() noexcept
{
    if (m_devices)
    {
        libusb_free_device_list(m_devices, 1);
        m_devices = nullptr;
    }
    if (m_usbContext)
    {
        libusb_exit(m_usbContext);
        m_usbContext = nullptr;
    }
}

auto UsbManager::init() noexcept -> void
{
    if (int result{libusb_init(&m_usbContext)}; result != LIBUSB_SUCCESS)
    {
        std::println("UsbManager init Failed: {}", libusb_error_name(result));
        return;
    }
    std::println("UsbManager init Success");
}

auto UsbManager::devicesList() noexcept -> std::map<u_int, u_int>
{
    std::map<u_int, u_int> devicesViewMap{};
    ssize_t                count{libusb_get_device_list(m_usbContext, &m_devices)};
    if (count < 0)
    {
        std::println("UsbManager get devices list Failed: {}", libusb_error_name(count));
        return devicesViewMap;
    }
    for (int i{}; i < count; ++i)
    {
        libusb_device_descriptor descriptor{};
        if (int result{libusb_get_device_descriptor(m_devices[i], &descriptor)}; result != LIBUSB_SUCCESS)
        {
            continue;
        }
        devicesViewMap.emplace(descriptor.idVendor, descriptor.idProduct);
    }
    return devicesViewMap;
}
