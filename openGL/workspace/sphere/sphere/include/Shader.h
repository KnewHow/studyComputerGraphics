#ifndef __SHADER_H__
#define __SHADER_H__
#include<glad/glad.h>
#include<string>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>

enum class CompileType {
	PROGRAM = 1,
	SHADER = 2
};

class Shader {
public:
	unsigned int ID;
	/**
	* 根据顶点着色器和片元着色器来构造Shader
	*/
	Shader(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path);
	~Shader();

	/**
	* 使用着色器
	*/
	void Use();

	/**
	* 根据名称设置Bool类型的变量
	*/
	void SetBool(const std::string& name, bool value) const;

	/**
	* 根据名称设置整形变量
	*/
	void SetInt(const std::string& name, int value) const;

	/**
	* 根据名称设置浮点类型变量
	*/
	void SetFloat(const std::string& name, float value) const;

	/**
	* 根据名称设置二维向量，后一个位重载方法
	*/
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;

	/**
	* 根据名称设置三维向量，后一个位重载方法
	*/
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;


	/**
	* 根据名称设置四维向量，后一个位重载方法
	*/
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;

	/**
	* 根据名称更新2x2矩阵
	*/
	void SetMat2(const std::string& name, const glm::mat2& value) const;

	/**
	* 根据名称更新3x3矩阵
	*/
	void SetMat3(const std::string& name, const glm::mat3& value) const;

	void SetMat4(const std::string& name, const glm::mat4& value) const;

private:

	/**
	* 根据路径获取顶点着色器和片元着色器的源代码
	* @param vertex_shader_path 顶点着色器文件路径
	* @param fragment_shader_path 片元着色器文件路径
	* @param vertex_shader_code 顶点着色器代码
	* @param fragment_shader_code 片元着色器代码
	* @return 0 表示读取成功，其他表示失败
	*/
	int GetShaderFromFile(
		const GLchar* vertex_shader_path,
		const GLchar* fragment_shader_path,
		std::string* vertex_shader_code,
		std::string* fragment_shader_code
	);

	/**
	* 链接顶点着色器代码和片元着色器代码
	* @return 0 表示成功，其他表示失败
	*/
	int LinkShader(const char* vertex_shader_code, const char* fragment_shader_code);

	/**
	* 获取 UniformLocation
	*/
	int GetUniform(const std::string& name) const;

	/**
	* 检查编译错误
	* @param shader 着色器编号
	* @param type 着色器类型
	* @return 
	*/
	int CheckCompileErrors(GLuint shader, CompileType type);

};
#endif // !__SHADER_H__

