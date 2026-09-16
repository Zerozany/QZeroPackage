_Pragma("once");
#include <string>

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

class ZERO_API HttpsManager
{
private:
#if defined(__ANDROID__)
    std::string m_cacertPath{};
#endif
};
