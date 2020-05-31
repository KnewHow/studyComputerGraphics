#pragma once

// 定义窗口尺寸
#define SCREEN_WIDHT 1280
#define SCREEN_HEIGH 720

// 定义四边形绘制顶点
const float quad[] = {
	0.5f, 0.5f, 0.0f, // 右上
	0.5f, -0.5f, 0.0f, // 右下
	-0.5f, -0.5f, 0.0f, // 左下
	-0.5f, -0.5f, 0.0f, // 左下
	0.5f, 0.5f, 0.0f, // 右上
	-0.5f, 0.5f, 0.0f // 左上
};