#include <GLFW/glfw3.h>

#include "Game.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREE_HEIGHT = 600;

Game Pong(SCREEN_WIDTH, SCREE_HEIGHT);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    Pong.Init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {   
        /* Poll for and process events */
        glfwPollEvents();

        Pong.ProcessInput();
        Pong.Update();        
        
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Pong.Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}