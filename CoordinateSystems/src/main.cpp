#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const std::string SHADER_DIR = "/home/terrydavis/Desktop/Dev/C++/Graphics/LearnOpenGL/CoordinateSystems/shaders/";

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float FOV = 100.0f;

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shaders", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    //--------- 
    Shader shader(SHADER_DIR + "shader.vsh", SHADER_DIR + "shader.fsh");

    float vertices[] = {
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,
         0.25f, -0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
         0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 1.0f,
         0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 1.0f,
        -0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,
                                              
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
         0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  1.0f, 1.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  1.0f, 1.0f, 1.0f,
        -0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 1.0f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
                                              
        -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
        -0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 1.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
        -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
                                              
         0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
         0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 1.0f,
         0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
         0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
         0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
                                              
        -0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
         0.25f, -0.25f, -0.25f,  1.0f, 1.0f, 1.0f,
         0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
         0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
        -0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
                                              
        -0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
         0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
         0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
        -0.25f,  0.25f,  0.25f,  0.0f, 0.0f, 1.0f,
        -0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 1.0f,
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3(-2.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  0.0f,  0.0f),

        glm::vec3( 0.0f, -2.0f,  0.0f),
        glm::vec3(-1.0f, -2.0f,  0.0f),
        glm::vec3( 1.0f, -2.0f,  0.0f),
        glm::vec3(-2.0f, -2.0f,  0.0f),
        glm::vec3( 2.0f, -2.0f,  0.0f),

        glm::vec3( 0.0f,  2.0f,  0.0f),
        glm::vec3(-1.0f,  2.0f,  0.0f),
        glm::vec3( 1.0f,  2.0f,  0.0f),
        glm::vec3(-2.0f,  2.0f,  0.0f),
        glm::vec3( 2.0f,  2.0f,  0.0f),

        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window)) 
    {
        processInput(window);

        glClearColor(0.01f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        float time = glfwGetTime() * 10;

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(FOV), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        for (unsigned int i = 0; i < sizeof(cubePositions) / (3 * sizeof(float)); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = time * (i + 1) * pow(-1, i);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.7f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
