#pragma once

// ���崰�ڳߴ�
#define SCREEN_WIDHT 1280
#define SCREEN_HEIGH 720

// �����ı��λ��ƶ��㣬��ֻ�� VAO �� VBO ģʽ��ʹ��
const float quad[] = {
	0.5f, 0.5f, 0.0f, // ����
	0.5f, -0.5f, 0.0f, // ����
	-0.5f, -0.5f, 0.0f, // ����
	-0.5f, -0.5f, 0.0f, // ����
	0.5f, 0.5f, 0.0f, // ����
	-0.5f, 0.5f, 0.0f // ����
};

// �ı��ε��ĸ����㣬�� EBO ģʽ��ʹ��
const float quad2[] = {
	0.5f, 0.5f, 0.0f, // ����
	0.5f, -0.5f, 0.0f, // ����
	-0.5f, -0.5f, 0.0f, // ����
	-0.5f, 0.5f, 0.0f // ����
};

// EBO ����
const unsigned int indices[] = {
	0,1,3,
	1,2,3
};