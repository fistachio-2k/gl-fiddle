#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

constexpr std::string_view vertexShaderPath = "../shaders/shader.vert";
constexpr std::string_view fragmentShaderPath = "../shaders/shader.frag";
constexpr std::string_view texturePath0 = "../assets/container.jpg";
constexpr std::string_view texturePath1 = "../assets/awesomeface.png";

constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HIEGHT = 600;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

int main()
{
    ///////////////////////////////////////////////////////////////
    //////            GLFW Window Initialization            ///////
    ///////////////////////////////////////////////////////////////

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

    GLFWwindow* window = glfwCreateWindow(800, 600, "gl-fiddle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoaderLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HIEGHT);

    ///////////////////////////////////////////////////////////////
    //////                Shader Compilation                ///////
    ///////////////////////////////////////////////////////////////

    auto shaderProgram = Shader(vertexShaderPath.data(), fragmentShaderPath.data());

    ///////////////////////////////////////////////////////////////
    //////            VAO+VBO+EBO Initialization            ///////
    ///////////////////////////////////////////////////////////////

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);


float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    float cubeRotation[] = {
        22.f, 35.f, 66.f, 140.f, 111.f, 227.f, 312.f, 180.f, 299.f, 10.f
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    // Texture Mapping Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    ///////////////////////////////////////////////////////////////
    //////                Generate Texture                  ///////
    ///////////////////////////////////////////////////////////////

    Texture texture0 = Texture(texturePath0, GL_RGB);
    Texture texture1 = Texture(texturePath1, GL_RGBA);

    shaderProgram.use();

    shaderProgram.setInt("ourTexture0", 0);
    shaderProgram.setInt("ourTexture1", 1);

    float mixCof = 0.5f;
    shaderProgram.setFloat("mixCof", mixCof);

    ///////////////////////////////////////////////////////////////
    //////                     Misc.                        ///////
    ///////////////////////////////////////////////////////////////

    glEnable(GL_DEPTH_TEST);  

    ///////////////////////////////////////////////////////////////
    //////                 Camera Control                   ///////
    ///////////////////////////////////////////////////////////////

    
    float deltaTime = 0.0f; 
    float lastFrame = 0.0f;

    auto cameraPos = glm::vec3(0.f, 0.f, 3.f);
    auto cameraUp = glm::vec3(0.f, 1.f, 0.f);
    auto cameraFront = glm::vec3(0.f, 0.f, -1.f);


    auto processInput = [&cameraPos, &cameraUp, &cameraFront, &deltaTime, window]()
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        float cameraSpeed = 5.f * deltaTime; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    };

    ///////////////////////////////////////////////////////////////
    //////                   Render Loop                    ///////
    ///////////////////////////////////////////////////////////////
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        processInput();

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        texture0.bind();

        glActiveTexture(GL_TEXTURE1);
        texture1.bind();

        shaderProgram.use();

        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(SCR_WIDTH) / SCR_HIEGHT, 0.1f,100.0f);

        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);

        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = cubeRotation[i];
            model = glm::rotate(model, glm::radians(angle) + static_cast<float>(glfwGetTime()) / (i + 1),glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            mixCof -= 0.01f;
            shaderProgram.setFloat("mixCof", std::max(std::min(mixCof, 1.f), 0.f));
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            mixCof += 0.01f;
            shaderProgram.setFloat("mixCof", std::max(std::min(mixCof, 1.f), 0.f));
        }
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
