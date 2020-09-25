#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;

const float triangle[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

const int screenWidht = 1280;
const int screenHeight = 720;

int main() {
	glfwInit();
	// ���ð汾Ϊ3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	// ʹ�ú���ģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ���ɸı䴰�ڴ�С
	glfwWindowHint(GLFW_RESIZABLE, false);
	auto window = glfwCreateWindow(screenWidht, screenHeight, "Triangle", nullptr, nullptr);
	// �������ʧ�ܣ����������Ϣ��������ֹ terminate
	if (window == nullptr) {
		cout << "Failed to create OpenGL context" << endl;
		glfwTerminate();
		return -1;
	}
	//�����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);

	// ��ʼ�� GLAD,���� OpenGL ����ָ��ĵ�ַ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed init GLAD" << endl;
		return -1;
	}
	// ָ����ǰ�ӿڳߴ磬ǰ����������Ϊ���½�λ�ã�������������Ϊ���ڵĿ���
	glViewport(0, 0, screenWidht, screenHeight);
	
	// �� VAO��VBO
	GLuint vertexArrayObject; // VAO
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	
	GLuint vertexBufferObject; // VBO
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	// ���������ݰ󶨵���ǰĬ�ϵĻ�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	// ���ö�������ָ��
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ��� VAO �� VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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

	// ���ɲ�������ɫ��
	// ������ɫ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "Falied to compile vertex shader: " << infoLog << endl;
	}

	// Ƭ����ɫ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "Failed to compile fragment shader: " << infoLog << endl;
	}
	
	// ��������ɫ����Ƭ����ɫ�����ӵ�һ����ɫ������
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << " Failure to link shader program: " << infoLog << endl;
	}

	// ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// �߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) {
		// ��ջ�������ɫ
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ʹ����ɫ������
		glUseProgram(shaderProgram);

		// ����������
		glBindVertexArray(vertexArrayObject); // �� VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // ����������
		glBindVertexArray(0); // �����

		// �������岢�Ҽ���Ƿ��д����¼�
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ɾ�� VAO �� VBO
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glfwTerminate();
	return 0;
}