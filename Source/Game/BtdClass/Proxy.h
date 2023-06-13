#pragma once
#include <type_traits>
namespace Btd
{
    template <typename T>
    class Proxy {
    private:
        T& object;
        bool enabled;

    public:
        Proxy(T& obj, bool enable) : object(obj), enabled(enable) {}
        void Init(T& obj, bool enable)
        {
            object = obj;
            enabled = enable;
        }
        void SetEnable(bool enable) {
            enabled = enable;
        }
        template <typename R, typename... Args>
        typename std::enable_if<!std::is_void<R>::value, R>::type
            Invoke(R(T::* fn)(Args...), Args&& ... args) {
            if (enabled) {
                return (object.*fn)(std::forward<Args>(args)...);
            }
            else {
                return R{};
            }
        }

        template <typename R, typename... Args>
        typename std::enable_if<std::is_void<R>::value, R>::type
            Invoke(R(T::* fn)(Args...), Args&& ... args) {
            if (enabled) {
                (object.*fn)(std::forward<Args>(args)...);
            }
        }

    };

}