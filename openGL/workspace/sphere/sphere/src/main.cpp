#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "include/Shader.h"
#include<vector>

const unsigned int SCREEN_WIDTH = 512;
const unsigned int SCREENT_HEIGHT = 512;

const GLfloat PI = 3.14159265358979323846f;

// 将球划分为纵横五十个网格
const unsigned int Y_SEGMENTS = 50;
const unsigned int X_SEGMENTS = 50;

int main() {
	
	glfwInit(); // 初始化 GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //使用OPENGL3.3版本，主次版本都为3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心版本，无需向后兼容
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 如果使用 MAC 电脑需要加上这行
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 设置窗口大小为不可变

	auto window = glfwCreateWindow(SCREEN_WIDTH, SCREENT_HEIGHT, "Shpere", nullptr, nullptr); //创建窗口，宽、高，名称
	if (window == nullptr) { // 创建失败，给出日志，终止程序
		std::cout << "Create openGL context Error" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // 将窗口对象设置位当前线程的主上下文

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // 初始化GLAD,加载openGL函数指针地址
		std::cout << "Failure to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREENT_HEIGHT); // 指定当前视口尺寸
	
	Shader shader("res/shader/sphere.vs", "res/shader/sphere.fs"); // 从文件中加载Shader

	std::vector<float> sphereVetetices;
	std::vector<int> sphereIndeices;
	//sphereIndeices.reserve();
	// 所有顶点坐标
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

	// 每个顶点坐标和其横向和竖向坐标构成两个三角面
	for (int i = 0; i < Y_SEGMENTS; i++) {
		for (int j = 0; j < X_SEGMENTS; j++) {
			// 先右后下
			sphereIndeices.push_back(i * (X_SEGMENTS + 1) + j); // 自身顶点索引
			sphereIndeices.push_back((i + 1) * (X_SEGMENTS + 1) + j); // 相邻右边顶点索引
			sphereIndeices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1); // 右边顶点下面一个顶点
			
			}
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO); // 绑定VAO和VBO
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	
	// 将VBO和顶点数据绑定
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
	
	// 设置顶点属性指针
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0
	);
	glEnableVertexAttribArray(0);

	// 解绑VBO和VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 循环渲染
	while (!glfwWindowShouldClose(window)) {
		// 清空颜色缓冲
		glClearColor(0.0f,0.34f,0.57f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);	
		// 使用Shader
		shader.Use();

		glEnable(GL_CULL_FACE); // 开启面剔除(只需展现一个面，否则会有面重合)
		glCullFace(GL_BACK);
		glBindVertexArray(VAO);
		// 使用线框模式
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(
			GL_TRIANGLES,
			X_SEGMENTS* Y_SEGMENTS * 6,
			GL_UNSIGNED_INT,
			0
		);

		//点阵模式绘制
		/*glPointSize(5);
		glDrawElements(
			GL_POINT,
			X_SEGMENTS * Y_SEGMENTS * 6,
			GL_UNSIGNED_INT,
			0
		);*/

		// 交换缓存区并且检查是否有事件触发，如键盘、鼠标
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 删除缓冲区
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &element_buff_object);

	// 终止程序
	glfwTerminate();
	return 0;

	
}