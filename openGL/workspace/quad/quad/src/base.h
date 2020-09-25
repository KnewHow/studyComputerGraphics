#pragma once

// 定义窗口尺寸
#define SCREEN_WIDHT 1280
#define SCREEN_HEIGH 720

// 定义四边形绘制顶点，在只有 VAO 和 VBO 模式下使用
const float quad[] = {
	0.5f, 0.5f, 0.0f, // 右上
	0.5f, -0.5f, 0.0f, // 右下
	-0.5f, -0.5f, 0.0f, // 左下
	-0.5f, -0.5f, 0.0f, // 左下
	0.5f, 0.5f, 0.0f, // 右上
	-0.5f, 0.5f, 0.0f // 左上
};

// 四边形的四个顶点，在 EBO 模式下使用
const float quad2[] = {
	0.5f, 0.5f, 0.0f, // 右上
	0.5f, -0.5f, 0.0f, // 右下
	-0.5f, -0.5f, 0.0f, // 左下
	-0.5f, 0.5f, 0.0f // 左上
};

// EBO 索引
const unsigned int indices[] = {
	0,1,3,
	1,2,3
};