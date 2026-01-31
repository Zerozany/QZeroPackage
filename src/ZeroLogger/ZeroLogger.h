_Pragma("once");
#include <memory>
#include <spdlog/spdlog.h>

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

class ZERO_API ZeroLogger
{
public:
    explicit(true) ZeroLogger();
    ~ZeroLogger() noexcept;

public:
    static auto init(const std::string& _logPath, std::size_t _logNum = 3) noexcept -> void;

    static auto setLevel(const spdlog::level::level_enum& _level) noexcept -> void;

    template <typename... Args>
    static auto trace(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto debug(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto info(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto warn(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto error(const char* _fmt, const Args&... _args) noexcept -> void;

    template <typename... Args>
    static auto critical(const char* _fmt, const Args&... _args) noexcept -> void;

private:
    static auto shutdown() noexcept -> void;

private:
    inline static std::shared_ptr<spdlog::logger> m_LoggerInstance{nullptr};
};

template <typename... Args>
inline auto ZeroLogger::trace(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->trace(_fmt, _args...);
    }
}

template <typename... Args>
inline auto ZeroLogger::debug(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->debug(_fmt, _args...);
    }
}

template <typename... Args>
inline auto ZeroLogger::info(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->info(_fmt, _args...);
    }
}

template <typename... Args>
inline auto ZeroLogger::warn(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->warn(_fmt, _args...);
    }
}

template <typename... Args>
inline auto ZeroLogger::error(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->error(_fmt, _args...);
    }
}

template <typename... Args>
inline auto ZeroLogger::critical(const char* _fmt, const Args&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->critical(_fmt, _args...);
    }
}
