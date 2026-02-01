#include <glad/glad.c>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float cubeRotationAngle = 0.0f;

float fov = 100.0f;

float sprint = 1.0f;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Camera", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    //--------- 
    Shader shader("shader.vsh", "shader.fsh");

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

    int n = 25;

    glm::vec3 cubePositions[n * n * n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                cubePositions[n * n * i + n * j + k] = glm::vec3((float)(k - (n / 2)), (float)(i - (n / 2)), (float)(j - (n / 2)));
            }
        }
    }

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
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.01f, 0.0f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.setMat4("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < sizeof(cubePositions) / (3 * sizeof(float)); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(cubeRotationAngle), glm::vec3(1.0f, 1.0f, 1.0f));
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); 

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)) * cameraSpeed * sprint;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::vec3(cameraFront.x, 0.0f, cameraFront.z)) * cameraSpeed * sprint;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * sprint;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * sprint;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos.y -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.y += 0.05f;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        sprint = 2.0f;
    }
    else
        sprint = 1.0f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cubeRotationAngle += 10.0f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cubeRotationAngle -= 10.0f;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset * 10.0f;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 100.0f)
        fov = 100.0f;
}
