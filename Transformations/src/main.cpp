#include <glad/glad.c>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Textures", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //------
    Shader shader("shaders/shader.vsh", "shaders/shader.fsh");

    float vertices[] = {
        // positions       // colors 
         0.4,  0.4,  0.0,   0.2, 0.0, 1.0,
         0.4, -0.4,  0.0,   0.1, 0.0, 0.8,
        -0.4, -0.4,  0.0,   0.1, 0.0, 0.8,
        -0.4,  0.4,  0.0,   0.2, 0.0, 1.0,

         0.4,  0.4,  0.0,   0.0, 0.3, 0.9,
         0.4, -0.4,  0.0,   0.0, 0.2, 1.0,
        -0.4, -0.4,  0.0,   0.0, 0.2, 1.0,
        -0.4,  0.4,  0.0,   0.0, 0.3, 0.9,

         0.4,  0.4,  0.0,   0.2, 0.4, 0.8,
         0.4, -0.4,  0.0,   0.1, 0.3, 1.0,
        -0.4, -0.4,  0.0,   0.1, 0.3, 1.0,
        -0.4,  0.4,  0.0,   0.2, 0.4, 0.8,

         0.4,  0.4,  0.0,   0.1, 0.2, 1.0,
         0.4, -0.4,  0.0,   0.4, 0.0, 1.0,
        -0.4, -0.4,  0.0,   0.4, 0.0, 1.0,
        -0.4,  0.4,  0.0,   0.1, 0.2, 1.0,
    };

    int indices[] = {
        0, 1, 3,
        1, 2, 3,

        4, 5, 7,
        5, 6, 7,

        8, 9, 11,
        9, 10,11,

        12, 13, 15,
        13, 14, 15
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glm::mat4 scale(1.0);

    unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.01, 0.0, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      
        // glm::scale(scale);
        float time = glfwGetTime();
        glm::mat4 transform = glm::mat4(1.0);
        transform = glm::translate(transform, glm::vec3(0.0, sin(time), 0.0));
        transform = glm::rotate(transform, time * 2, glm::vec3(cos(time), sin(time), 0));
        transform = glm::scale(transform, glm::vec3(sin(time), sin(time), 1));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        transform = glm::mat4(1.0);
        transform = glm::translate(transform, -glm::vec3(0.0, cos(time), 0.0));
        transform = glm::rotate(transform, time * 2, glm::vec3(cos(time), sin(time), 0));
        transform = glm::scale(transform, glm::vec3(cos(time), cos(time), 1));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(int)));

        transform = glm::mat4(1.0);
        transform = glm::translate(transform, glm::vec3(sin(time), 0.0, 0.0));
        transform = glm::rotate(transform, time * 2, glm::vec3(sin(time), cos(time), 0));
        transform = glm::scale(transform, glm::vec3(sin(time), cos(time), 1));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(12 * sizeof(int)));

        transform = glm::mat4(1.0);
        transform = glm::translate(transform, -glm::vec3(cos(time), 0.0, 0.0));
        transform = glm::rotate(transform, time * 2, glm::vec3(sin(time), cos(time), 0)); 
        transform = glm::scale(transform, glm::vec3(cos(time), sin(time), 1));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(18 * sizeof(int)));

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

