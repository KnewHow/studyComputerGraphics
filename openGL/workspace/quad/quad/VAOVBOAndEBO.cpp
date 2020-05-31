#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "base.h"

using namespace std;

class VAOVBOAndEBO {
public:
	int draw() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, false);

		auto window = glfwCreateWindow(SCREEN_WIDHT, SCREEN_HEIGH, "QuadWithVAO,VBOAndEBO", nullptr, nullptr);
		if (window == nullptr) {
			cout << "Failed to init window" << endl;
			return -1;
		}
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			cout << "Failed to init glad" << endl;
			return -1;
		}

		glViewport(0, 0, SCREEN_WIDHT, SCREEN_HEIGH);

		// 创建并绑定 VAO,VBO和EBO
		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// 绑定 VBO 并传入数据节点
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad2), quad2, GL_STATIC_DRAW);
		// 绑定 EBO并传入索引数据
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// 设置顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// 解绑 VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// 注意不要解绑 EBO,因为 EBO 存储在 VAO 中
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// 解绑VAO
		glBindVertexArray(0);

		// 顶点着色器和片段着色器源码
		const char* vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"           // 位置变量的属性位置值为0
			"void main()\n"
			"{\n"
			"    gl_Position = vec4(aPos, 1.0);\n"
			"}\n\0";
		const char* fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 FragColor;\n"                           // 输出的颜色向量
			"void main()\n"
			"{\n"
			"    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
			"}\n\0";

		// 创建顶点着色器和片段着色器
		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		int success = 0;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			cout << "Compile vertex shader error: " << infoLog << endl;
		}

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			cout << "Compile fragment shader error: " << infoLog << endl;
		}

		// 将顶点着色器和片段着色器打包到着色器城墙
		int shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			cout << "Link shader program error: " << infoLog << endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		while (!glfwWindowShouldClose(window)) {
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderProgram);

			// 绑定VAO
			glBindVertexArray(VAO);
			// 使用 EBO 绘制四边形
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// 解绑 VAO
			glBindVertexArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		// 解绑 EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// 删除 VAO, VBO， EBO
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glfwTerminate();
		return 0;
	}
};