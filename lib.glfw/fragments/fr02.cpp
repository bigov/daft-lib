/* Filename: fr01.cpp
 *
 * фрагмент примера, приведенный на https://stackoverflow.com/questions/39447862/registering-a-class-member-function-as-a-callback-to-a-function-using-stdbind/39448312#39448312
 *
 * Проблема в том, что нет возможности передать объект «контекст», который
 * автоматически отобразит обратный вызов обратно в экземпляр InputManager.
 * Поэтому нужно выполнить сопоставление вручную, используя только тот ключ,
 * который у вас есть - указатель окна.
 *
 *
 */

#include <map>
#include <mutex>

// ======================== Варинат 2 ========================================
// оr if you prefer closures:

struct GLFWwindow {};
typedef void(* GLFWcharfun) (GLFWwindow *, unsigned int);

GLFWcharfun glfwSetCharCallback (   GLFWwindow *    window,
                                 GLFWcharfun    cbfun
                                 );

struct InputManager;

struct WindowToInputManager
{
    using sig_type = void (GLFWwindow *, unsigned int);
    using func_type = std::function<sig_type>;

    struct impl
    {
        void associate(GLFWwindow* window, func_type func)
        {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            mapping_[window] = std::move(func);
        }

        void disassociate(GLFWwindow* window)
        {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            mapping_.erase(window);
        }

        const func_type* find(GLFWwindow* window) const
        {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            auto i = mapping_.find(window);
            if (i == mapping_.end())
                return nullptr;
            else
                return std::addressof(i->second);
        }

        mutable std::mutex mutex_;
        std::map<GLFWwindow*, func_type> mapping_;
    };

    static impl& get_impl() {
        static impl i {};
        return i;
    }

    template<class F>
    void associate(GLFWwindow* window, F&& f)
    {
        get_impl().associate(window, std::forward<F>(f));
        glfwSetCharCallback(window, &WindowToInputManager::handleCharCallback);
    }

    void disassociate(GLFWwindow* window)
    {
        // call whatever is the reverse of glfwSetCharCallback here
        //

        // then remove from the map
        get_impl().disassociate(window);
    }

    const func_type* find(GLFWwindow* window)
    {
        return get_impl().find(window);
    }

    static void handleCharCallback(GLFWwindow* w, unsigned int ch)
    {
        auto f = get_impl().find(w);
        // note - possible race here if handler calls disasociate. better to return a copy of the function?
        if (f) {
            (*f)(w, ch);
        }
    }

};

struct InputManager
{
    void init()
    {
        callback_mapper_.associate(window_, [this](auto* window, int ch) { this->charInputCallback(window, ch); });

    }

    void charInputCallback(GLFWwindow * window,
                           int ch)
    {
        // do something here
    }


    GLFWwindow* window_;
    WindowToInputManager callback_mapper_;

};
