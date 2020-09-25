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

		// �������� VAO,VBO��EBO
		GLuint VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		// �� VBO ���������ݽڵ�
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quad2), quad2, GL_STATIC_DRAW);
		// �� EBO��������������
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// ���ö�������ָ��
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// ��� VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// ע�ⲻҪ��� EBO,��Ϊ EBO �洢�� VAO ��
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// ���VAO
		glBindVertexArray(0);

		// ������ɫ����Ƭ����ɫ��Դ��
		const char* vertexShaderSource =
			"#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"           // λ�ñ���������λ��ֵΪ0
			"void main()\n"
			"{\n"
			"    gl_Position = vec4(aPos, 1.0);\n"
			"}\n\0";
		const char* fragmentShaderSource =
			"#version 330 core\n"
			"out vec4 FragColor;\n"                           // �������ɫ����
			"void main()\n"
			"{\n"
			"    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
			"}\n\0";

		// ����������ɫ����Ƭ����ɫ��
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

		// ��������ɫ����Ƭ����ɫ���������ɫ����ǽ
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

			// ��VAO
			glBindVertexArray(VAO);
			// ʹ�� EBO �����ı���
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// ��� VAO
			glBindVertexArray(0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		// ��� EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		// ɾ�� VAO, VBO�� EBO
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glfwTerminate();
		return 0;
	}
};