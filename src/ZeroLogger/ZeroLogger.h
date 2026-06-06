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
    static auto trace(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    static auto debug(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    static auto info(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    static auto warn(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    static auto error(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

    template <typename... Args>
    static auto critical(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void;

private:
    static auto shutdown() noexcept -> void;

private:
    inline static std::shared_ptr<spdlog::logger> m_LoggerInstance{nullptr};
};

template <typename... Args>
inline auto ZeroLogger::trace(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->trace(_fmt, std::forward<Args>(_args)...);
    }
}

template <typename... Args>
inline auto ZeroLogger::debug(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->debug(_fmt, std::forward<Args>(_args)...);
    }
}

template <typename... Args>
inline auto ZeroLogger::info(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->info(_fmt, std::forward<Args>(_args)...);
    }
}

template <typename... Args>
inline auto ZeroLogger::warn(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->warn(_fmt, std::forward<Args>(_args)...);
    }
}

template <typename... Args>
inline auto ZeroLogger::error(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->error(_fmt, std::forward<Args>(_args)...);
    }
}

template <typename... Args>
inline auto ZeroLogger::critical(fmt::format_string<Args...> _fmt, Args&&... _args) noexcept -> void
{
    if (m_LoggerInstance.get())
    {
        m_LoggerInstance.get()->critical(_fmt, std::forward<Args>(_args)...);
    }
}
