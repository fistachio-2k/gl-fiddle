#include <iostream>
#include <glad/gl.h> 
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "stb_image.h"

constexpr std::string_view vertexShaderPath = "../shaders/shader.vert";
constexpr std::string_view fragmentShaderPath = "../shaders/shader.frag";
constexpr std::string_view texturePath = "../assets/container.jpg";

constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HIEGHT = 600;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	///////////////////////////////////////////////////////////////
	//////            GLFW Window Initialization            ///////
	///////////////////////////////////////////////////////////////

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

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

	auto ShaderProgram = Shader(vertexShaderPath.data(), fragmentShaderPath.data());

	///////////////////////////////////////////////////////////////
	//////            VAO+VBO+EBO Initialization            ///////
	///////////////////////////////////////////////////////////////

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	
	// Color Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Mapping Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	///////////////////////////////////////////////////////////////
	//////                Generate Texture                  ///////
	///////////////////////////////////////////////////////////////
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.data(), &width, &height, &nrChannels, 0);
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::TEXTURES::FAILED_TO_LOAD" << std::endl;
	}

	stbi_image_free(data);

	///////////////////////////////////////////////////////////////
	//////                   Render Loop                    ///////
	///////////////////////////////////////////////////////////////

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

		ShaderProgram.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}
