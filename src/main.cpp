#include <iostream>
#include <glad/gl.h> 
#include <GLFW/glfw3.h>

const char* vertexShaderSource = R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";

const char* fragmentShaderSource_A = R"(#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})";

const char* fragmentShaderSource_B = R"(#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(0.2f, 0.5f, 1.0f, 1.0f);
})";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void checkShaderCompileResult(unsigned int shader)
{
	int  success;
	char infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void checkShaderProgramLinkResult(unsigned int shaderProgram)
{
	int  success;
	char infoLog[512];

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKAGE_FAILED\n" << infoLog << std::endl;
	}
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

	///////////////////////////////////////////////////////////////
	//////                Shader Compilation                ///////
	///////////////////////////////////////////////////////////////

	glViewport(0, 0, 800, 600);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	checkShaderCompileResult(vertexShader);

	// Fragment shader A
	unsigned int fragmentShader_A = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader_A, 1, &fragmentShaderSource_A, NULL);
	glCompileShader(fragmentShader_A);

	checkShaderCompileResult(fragmentShader_A);

	// Fragment shader B
	unsigned int fragmentShader_B = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader_B, 1, &fragmentShaderSource_B, NULL);
	glCompileShader(fragmentShader_B);

	checkShaderCompileResult(fragmentShader_B);

	unsigned int shaderProgram_A = glCreateProgram();

	glAttachShader(shaderProgram_A, vertexShader);
	glAttachShader(shaderProgram_A, fragmentShader_A);

	glLinkProgram(shaderProgram_A);

	unsigned int shaderProgram_B = glCreateProgram();

	glAttachShader(shaderProgram_B, vertexShader);
	glAttachShader(shaderProgram_B, fragmentShader_B);

	glLinkProgram(shaderProgram_B);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader_A);
	glDeleteShader(fragmentShader_B);

	checkShaderProgramLinkResult(shaderProgram_A);
	checkShaderProgramLinkResult(shaderProgram_B);


	///////////////////////////////////////////////////////////////
	//////            VAO+VBO+VEO Initialization            ///////
	///////////////////////////////////////////////////////////////

	//constexpr float vertices[] = {
	//	 0.5f,  0.5f, 0.0f,  // top right
	//	 0.5f, -0.5f, 0.0f,  // bottom right
	//	-0.5f, -0.5f, 0.0f,  // bottom left
	//	-0.5f,  0.5f, 0.0f   // top left 
	//};

	constexpr float verticesA[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	 0.0f,  0.0f, 0.0f  // center
	};

	constexpr float verticesB[] = {
	-0.5f,  0.5f, 0.0f,  // top left 
	-0.5f, -0.5f, 0.0f,  // bottom left
	 0.0f,  0.0f, 0.0f   // center
	};

	constexpr unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	unsigned int VAO_A;
	glGenVertexArrays(1, &VAO_A);
	glBindVertexArray(VAO_A);

	unsigned int VBO_A;
	glGenBuffers(1, &VBO_A);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_A);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	unsigned int VAO_B;
	glGenVertexArrays(1, &VAO_B);
	glBindVertexArray(VAO_B);

	unsigned int VBO_B;
	glGenBuffers(1, &VBO_B);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	///////////////////////////////////////////////////////////////
	//////                   Render Loop                    ///////
	///////////////////////////////////////////////////////////////

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram_A);
		glBindVertexArray(VAO_A);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shaderProgram_B);
		glBindVertexArray(VAO_B);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO_A);
	glDeleteVertexArrays(1, &VAO_B);
	glDeleteBuffers(1, &VBO_A);
	glDeleteBuffers(1, &VBO_B);

	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram_A);
	glDeleteProgram(shaderProgram_B);

	glfwTerminate();
	return 0;
}
