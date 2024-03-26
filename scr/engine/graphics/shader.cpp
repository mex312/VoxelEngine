#include "shader.h"
#include "../../external/glad.h"
#include <iostream>

namespace engine {
    Shader::Shader(u32 id) : id(id) {}

    Shader::~Shader() {
        glDeleteProgram(id);
    }

    void Shader::use() const {
        glUseProgram(id);
    }

    Shader *Shader::loadShader(const std::string &vertexSource, const std::string &fragmentSource) {
        u32 vertex = glCreateShader(GL_VERTEX_SHADER);
        const char *vertexText = vertexSource.c_str();
        glShaderSource(vertex, 1, &vertexText, nullptr);
        glCompileShader(vertex);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

                return nullptr;
            }
        }


        u32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fragmentText = fragmentSource.c_str();
        glShaderSource(fragment, 1, &fragmentText, nullptr);
        glCompileShader(fragment);
        {
            int success;
            char infoLog[512];
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
                std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

                return nullptr;
            }
        }


        u32 id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return new Shader(id);
    }
}