#define GLEW_STATIC
#include "shader.h"
#include <GL\glew.h>
#include <iostream>
#include <fstream>

static void printMat(glm::mat4 phi)
{
	printf(" matrix: \n");
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				printf("%f ", phi[j][i]);
			printf("\n");
		}
}

Shader::Shader(const std::string& fileName)
{
	
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");
	glBindAttribLocation(m_program, 3, "color");
	glBindAttribLocation(m_program, 4, "weight");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
	m_uniforms[3] = glGetUniformLocation(m_program, "lightColor");
	m_uniforms[4] = glGetUniformLocation(m_program, "links_num");
	m_uniforms[5] = glGetUniformLocation(m_program, "link");
	m_uniforms[6] = glGetUniformLocation(m_program, "T");
	m_uniforms[7] = glGetUniformLocation(m_program, "eyePosition");
}

Shader::~Shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(glm::mat4 MVP ,glm::mat4 Normal , int const shpIndx, const int links_num, std::vector<glm::mat4> T, glm::vec3 camPos)
{

	
	//if(Normal[0][3]>0 || Normal[3][0]>0)
	//{
	//	printMat(Normal);
	//	printMat(MVP);
	//}
	
	int r = ((shpIndx+1) & 0x000000FF) >>  0;
	int g = ((shpIndx+1) & 0x0000FF00) >>  8;
	int b = ((shpIndx+1) & 0x00FF0000) >> 16;
	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[2], 0.0f, 0.0f, 1.0f);
	glUniform3f(m_uniforms[3], r/255.0f, g/255.0f, b/255.0f);

	glUniform1i(m_uniforms[4], links_num);
	glUniform1i(m_uniforms[5], shpIndx);
	glUniformMatrix4fv(m_uniforms[6], T.size(), GL_FALSE, &T[0][0][0]);
	glUniform4f(m_uniforms[7], camPos.x, camPos.y, camPos.z, 1);
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

unsigned int Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}
