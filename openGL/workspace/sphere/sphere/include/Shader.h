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
	* ���ݶ�����ɫ����ƬԪ��ɫ��������Shader
	*/
	Shader(const GLchar* vertex_shader_path, const GLchar* fragment_shader_path);
	~Shader();

	/**
	* ʹ����ɫ��
	*/
	void Use();

	/**
	* ������������Bool���͵ı���
	*/
	void SetBool(const std::string& name, bool value) const;

	/**
	* ���������������α���
	*/
	void SetInt(const std::string& name, int value) const;

	/**
	* �����������ø������ͱ���
	*/
	void SetFloat(const std::string& name, float value) const;

	/**
	* �����������ö�ά��������һ��λ���ط���
	*/
	void SetVec2(const std::string& name, const glm::vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;

	/**
	* ��������������ά��������һ��λ���ط���
	*/
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;


	/**
	* ��������������ά��������һ��λ���ط���
	*/
	void SetVec4(const std::string& name, const glm::vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w) const;

	/**
	* �������Ƹ���2x2����
	*/
	void SetMat2(const std::string& name, const glm::mat2& value) const;

	/**
	* �������Ƹ���3x3����
	*/
	void SetMat3(const std::string& name, const glm::mat3& value) const;

	void SetMat4(const std::string& name, const glm::mat4& value) const;

private:

	/**
	* ����·����ȡ������ɫ����ƬԪ��ɫ����Դ����
	* @param vertex_shader_path ������ɫ���ļ�·��
	* @param fragment_shader_path ƬԪ��ɫ���ļ�·��
	* @param vertex_shader_code ������ɫ������
	* @param fragment_shader_code ƬԪ��ɫ������
	* @return 0 ��ʾ��ȡ�ɹ���������ʾʧ��
	*/
	int GetShaderFromFile(
		const GLchar* vertex_shader_path,
		const GLchar* fragment_shader_path,
		std::string* vertex_shader_code,
		std::string* fragment_shader_code
	);

	/**
	* ���Ӷ�����ɫ�������ƬԪ��ɫ������
	* @return 0 ��ʾ�ɹ���������ʾʧ��
	*/
	int LinkShader(const char* vertex_shader_code, const char* fragment_shader_code);

	/**
	* ��ȡ UniformLocation
	*/
	int GetUniform(const std::string& name) const;

	/**
	* ���������
	* @param shader ��ɫ�����
	* @param type ��ɫ������
	* @return 
	*/
	int CheckCompileErrors(GLuint shader, CompileType type);

};
#endif // !__SHADER_H__

