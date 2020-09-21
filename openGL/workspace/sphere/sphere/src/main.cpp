#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "include/Shader.h"
#include<vector>

const unsigned int SCREEN_WIDTH = 512;
const unsigned int SCREENT_HEIGHT = 512;

const GLfloat PI = 3.14159265358979323846f;

// ���򻮷�Ϊ�ݺ���ʮ������
const unsigned int Y_SEGMENTS = 50;
const unsigned int X_SEGMENTS = 50;

int main() {
	
	glfwInit(); // ��ʼ�� GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //ʹ��OPENGL3.3�汾�����ΰ汾��Ϊ3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ʹ�ú��İ汾������������
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // ���ʹ�� MAC ������Ҫ��������
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // ���ô��ڴ�СΪ���ɱ�

	auto window = glfwCreateWindow(SCREEN_WIDTH, SCREENT_HEIGHT, "Shpere", nullptr, nullptr); //�������ڣ����ߣ�����
	if (window == nullptr) { // ����ʧ�ܣ�������־����ֹ����
		std::cout << "Create openGL context Error" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // �����ڶ�������λ��ǰ�̵߳���������

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // ��ʼ��GLAD,����openGL����ָ���ַ
		std::cout << "Failure to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREENT_HEIGHT); // ָ����ǰ�ӿڳߴ�
	
	Shader shader("res/shader/sphere.vs", "res/shader/sphere.fs"); // ���ļ��м���Shader

	std::vector<float> sphereVetetices;
	std::vector<int> sphereIndeices;
	//sphereIndeices.reserve();
	// ���ж�������
	for (int y = 0; y <= Y_SEGMENTS; y++) {
		for (int x = 0; x <= X_SEGMENTS; x++) {
			float alpha = PI * (float)y / (float)Y_SEGMENTS;
			float bata = PI * (float)x / X_SEGMENTS * 2.0f;
			
			float xPos = std::cos(bata) * std::sin(alpha);
			float yPos = std::cos(alpha);
			float zPos = std::sin(bata) * std::sin(alpha);


			sphereVetetices.push_back(xPos);
			sphereVetetices.push_back(yPos);
			sphereVetetices.push_back(zPos);
		}
	}

	// ÿ������������������������깹������������
	for (int i = 0; i < Y_SEGMENTS; i++) {
		for (int j = 0; j < X_SEGMENTS; j++) {
			// ���Һ���
			sphereIndeices.push_back(i * (X_SEGMENTS + 1) + j); // ����������
			sphereIndeices.push_back((i + 1) * (X_SEGMENTS + 1) + j); // �����ұ߶�������
			sphereIndeices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1); // �ұ߶�������һ������
			
			}
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO); // ��VAO��VBO
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	
	// ��VBO�Ͷ������ݰ�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		sphereVetetices.size() * sizeof(float),
		&sphereVetetices[0],
		GL_STATIC_DRAW
	);

	// EBO
	GLuint element_buff_object;
	glGenBuffers(1, &element_buff_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buff_object);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sphereIndeices.size() * sizeof(int),
		&sphereIndeices[0],
		GL_STATIC_DRAW
	);
	
	// ���ö�������ָ��
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0
	);
	glEnableVertexAttribArray(0);

	// ���VBO��VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ѭ����Ⱦ
	while (!glfwWindowShouldClose(window)) {
		// �����ɫ����
		glClearColor(0.0f,0.34f,0.57f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	
		// ʹ��Shader
		shader.Use();

		glEnable(GL_CULL_FACE); // �������޳�(ֻ��չ��һ���棬����������غ�)
		glCullFace(GL_BACK);
		glBindVertexArray(VAO);
		// ʹ���߿�ģʽ
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(
			GL_TRIANGLES,
			X_SEGMENTS* Y_SEGMENTS * 6,
			GL_UNSIGNED_INT,
			0
		);

		//����ģʽ����
		/*glPointSize(5);
		glDrawElements(
			GL_POINT,
			X_SEGMENTS * Y_SEGMENTS * 6,
			GL_UNSIGNED_INT,
			0
		);*/

		// �������������Ҽ���Ƿ����¼�����������̡����
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ɾ��������
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &element_buff_object);

	// ��ֹ����
	glfwTerminate();
	return 0;

	
}