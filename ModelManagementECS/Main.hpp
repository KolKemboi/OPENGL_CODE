#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Entity.hpp"
#include <memory>

typedef unsigned int u_int;
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
Ref<T> Reffed (Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

class Engine
{
public:
	Engine()
	{

	}
	~Engine()
	{

	}
	void RunEngine()
	{

	}

private:
	GLFWwindow* m_Window;
	u_int m_Width, m_Height;

};






