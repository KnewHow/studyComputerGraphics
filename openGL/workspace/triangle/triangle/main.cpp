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
	// 设置版本为3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	// 使用核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 不可改变窗口大小
	glfwWindowHint(GLFW_RESIZABLE, false);
	auto window = glfwCreateWindow(screenWidht, screenHeight, "Triangle", nullptr, nullptr);
	// 如果创建失败，输出错误信息，并且终止 terminate
	if (window == nullptr) {
		cout << "Failed to create OpenGL context" << endl;
		glfwTerminate();
		return -1;
	}
	//将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	// 初始化 GLAD,加载 OpenGL 函数指针的地址函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed init GLAD" << endl;
		return -1;
	}
	// 指定当前视口尺寸，前面两个参数为左下角位置，后面两个参数为窗口的宽、高
	glViewport(0, 0, screenWidht, screenHeight);
	
	// 绑定 VAO和VBO
	GLuint vertexArrayObject; // VAO
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	
	GLuint vertexBufferObject; // VBO
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	// 将顶点数据绑定道当前默认的缓冲区中
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	// 设置顶点属性指针
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 解绑 VAO 和 VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

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

	// 生成并编译着色器
	// 顶点着色器
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

	// 片段着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "Failed to compile fragment shader: " << infoLog << endl;
	}
	
	// 将顶点着色器和片段着色器链接到一个着色器程序
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << " Failure to link shader program: " << infoLog << endl;
	}

	// 删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//渲染循环
	while (!glfwWindowShouldClose(window)) {
		// 清空缓冲区颜色
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 使用着色器程序
		glUseProgram(shaderProgram);

		// 绘制三角形
		glBindVertexArray(vertexArrayObject); // 绑定 VAO
		glDrawArrays(GL_TRIANGLES, 0, 3); // 绘制三角形
		glBindVertexArray(0); // 解除绑定

		// 交换缓冲并且检查是否有触发事件
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 删除 VAO 和 VBO
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glfwTerminate();
	return 0;
}