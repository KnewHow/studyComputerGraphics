#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<stdlib.h>
#include<stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void framebufferSizeCallBack(GLFWwindow* window, int width, int height) {
    //���ǿ���ͨ������ glViewport ���������ô��ڵ�ά��
   // glViewport ����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���

    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    // ���� GLFW�����汾�š��ΰ汾���Լ�����
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // ��ӡ GLFW �����汾�ţ��ΰ汾���Լ�С�汾
    int major = 0;
    int minor = 0;
    int rev = 0;
    glfwGetVersion(&major, &minor, &rev);
    printf("GLFW: %d.%d.%d", major, minor, rev);
    // ���������Ǵ���һ�����ڶ���������ڶ����������кʹ�����ص����ݣ����һᱻ GLFW ����������Ƶ�����õ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "MyWindow", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }
    else {
        // ����֪ͨ GLFW �����Ǵ��ڵ�����������Ϊ��ǰ�̵߳����������ˡ�
        glfwMakeContextCurrent(window);
    }
    /*��֮ǰ�����Ѿ��ᵽ��GLAD ���������� OpenGL �ĺ���ָ��ģ�
    * �����ڵ����κ� OpenGL �ĺ���֮ǰ������Ҫ��ʼ�� GLAD��
    * ���Ǹ� GLAD ��������������ϵͳ��ص� OpenGL ����ָ���ַ�ĺ�����
    * GLFW �����ǵ��� glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ�����

    */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to init GLAD" << endl;
        return -1;
    }
    /**
     * ���� GLFW ����ϣ��ÿ�����ڵ�����С��ʱ������������
     * �����ڱ���һ����ʾ��ʱ�� framebuffer_size_callback Ҳ�ᱻ���á���������Ĥ(Retina)��ʾ����width �� height �������Ա�ԭ����ֵ����һ��
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
