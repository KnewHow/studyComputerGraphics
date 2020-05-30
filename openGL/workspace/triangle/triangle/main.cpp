#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<stdlib.h>
#include<stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void framebufferSizeCallBack(GLFWwindow* window, int width, int height) {
    //我们可以通过调用 glViewport 函数来设置窗口的维度
   // glViewport 函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。

    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    // 设置 GLFW的主版本号、次版本号以及配置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 打印 GLFW 的主版本号，次版本号以及小版本
    int major = 0;
    int minor = 0;
    int rev = 0;
    glfwGetVersion(&major, &minor, &rev);
    printf("GLFW: %d.%d.%d", major, minor, rev);
    // 接下来我们创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被 GLFW 的其他函数频繁地用到。
    GLFWwindow* window = glfwCreateWindow(800, 600, "MyWindow", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }
    else {
        // 可以通知 GLFW 将我们窗口的上下文设置为当前线程的主上下文了。
        glfwMakeContextCurrent(window);
    }
    /*在之前我们已经提到，GLAD 是用来管理 OpenGL 的函数指针的，
    * 所以在调用任何 OpenGL 的函数之前我们需要初始化 GLAD。
    * 我们给 GLAD 传入了用来加载系统相关的 OpenGL 函数指针地址的函数。
    * GLFW 给我们的是 glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。

    */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to init GLAD" << endl;
        return -1;
    }
    /**
     * 告诉 GLFW 我们希望每当窗口调整大小的时候调用这个函数
     * 当窗口被第一次显示的时候 framebuffer_size_callback 也会被调用。对于视网膜(Retina)显示屏，width 和 height 都会明显比原输入值更高一点
   */
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallBack);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
