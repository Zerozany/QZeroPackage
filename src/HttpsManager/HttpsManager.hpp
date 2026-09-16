_Pragma("once");
#include <string>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <print>

#if defined(_WIN32) && defined(_MSC_VER)
    #ifdef QZeroPackage
        #define ZERO_API __declspec(dllexport)
    #else
        #define ZERO_API __declspec(dllimport)
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define ZERO_API __attribute__((visibility("default")))
#else
    #define ZERO_API
#endif

template <typename... Args>
class HttpsManager
{
public:
    explicit(true) HttpsManager(Args&&... args);

    virtual ~HttpsManager() noexcept;

protected:
    virtual auto init(Args&&... args) noexcept -> void;

protected:
    httplib::SSLClient* m_sslClient{nullptr};
};

template <typename... Args>
inline HttpsManager<Args...>::HttpsManager(Args&&... args)
{
    std::invoke(&HttpsManager::init, this, std::forward<Args>(args)...);
}

template <typename... Args>
inline HttpsManager<Args...>::~HttpsManager() noexcept
{
    delete m_sslClient;
    m_sslClient = nullptr;
}

template <typename... Args>
inline auto HttpsManager<Args...>::init(Args&&... args) noexcept -> void
{
    m_sslClient = new httplib::SSLClient{std::forward<Args>(args)...};
    m_sslClient->set_connection_timeout(10, 0);
    m_sslClient->set_read_timeout(10, 0);
    m_sslClient->set_error_logger([](const httplib::Error& err, const httplib::Request*) {
        std::println("httplib error:{}", httplib::to_string(err).c_str());
    });
}
