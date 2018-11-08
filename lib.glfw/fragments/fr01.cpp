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

// ======================== Варинат 1 ========================================

struct GLFWwindow {};
typedef void(* GLFWcharfun) (GLFWwindow *, unsigned int);

GLFWcharfun glfwSetCharCallback (   GLFWwindow *    window,
                                 GLFWcharfun    cbfun
                                 );

struct InputManager;

struct WindowToInputManager
{
    struct impl
    {
        void associate(GLFWwindow* window, InputManager* manager)
        {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            mapping_[window] = manager;
        }

        void disassociate(GLFWwindow* window, InputManager* manager)
        {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            mapping_.erase(window);
        }

        InputManager* find(GLFWwindow* window) const
        {
            auto lock = std::unique_lock<std::mutex>(mutex_);
            auto i = mapping_.find(window);
            if (i == mapping_.end())
                return nullptr;
            else
                return i->second;
        }

        mutable std::mutex mutex_;
        std::map<GLFWwindow*, InputManager*> mapping_;
    };

    static impl& get_impl() {
        static impl i {};
        return i;
    }

    void associate(GLFWwindow* window, InputManager* manager)
    {
        get_impl().associate(window, manager);
    }

    void disassociate(GLFWwindow* window, InputManager* manager)
    {
        get_impl().disassociate(window, manager);
    }

    InputManager* find(GLFWwindow* window)
    {
        return get_impl().find(window);
    }

};

struct InputManager
{
    void init()
    {
        // how to set up the callback?

        // first, associate the window with this input manager
        callback_mapper_.associate(window_, this);

        // now use a proxy as the callback
        glfwSetCharCallback(window_, &InputManager::handleCharCallback);

    }

    static void handleCharCallback(GLFWwindow *     window,
                           unsigned int ch)
    {
        // proxy locates the handler
        if(auto self = callback_mapper_.find(window))
        {
            self->charInputCallback(window, ch);
        }

    }

    void charInputCallback(GLFWwindow *     window,
                           int ch)
    {
        // do something here
    }


    GLFWwindow* window_;
    static WindowToInputManager callback_mapper_;    
};


