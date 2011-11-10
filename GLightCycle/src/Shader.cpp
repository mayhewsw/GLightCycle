/*
 * Shader.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: kimsj
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include "Shader.h"

using namespace std;

GLuint EmptyTexture() {
	GLuint txtnumber;
	unsigned char *data;

	data = (unsigned char *) malloc(glowSize * glowSize * 4);

	glGenTextures(1, &txtnumber);
	glBindTexture(GL_TEXTURE_2D, txtnumber);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glowSize, glowSize, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	free(data);

	return txtnumber;
}

// shader reader - creates null terminated string from file
const char *
readShaderSource(const char* shaderFile) {
	struct stat statBuf;
	FILE* fp = fopen(shaderFile, "r");
	char* buf;

	stat(shaderFile, &statBuf);
	buf = (char *) malloc((statBuf.st_size + 1) * sizeof(char));
	memset(buf, 0, statBuf.st_size + 1);
	fread(buf, 1, statBuf.st_size, fp);
	fclose(fp);

	return buf;
}

// error printing function
void checkError(GLint status, const char *msg) {
	if (!status) {
		printf("%s\n", msg);
		exit(EXIT_FAILURE);
	}
}

// shader initialization
void initShader(const GLchar* vShaderFile, const GLchar* fShaderFile,
		GLint *program) {
	GLint vShader = 0;
	GLint fShader = 0;
	GLint status = 0;

	// read shader files
	const char* vSource = readShaderSource(vShaderFile);
	const char* fSource = readShaderSource(fShaderFile);

	// create program and shader objects
	vShader = glCreateShader(GL_VERTEX_SHADER);
	fShader = glCreateShader(GL_FRAGMENT_SHADER);

	*program = glCreateProgram();

	// attach shaders to the program object
	glAttachShader(*program, vShader);
	glAttachShader(*program, fShader);

	// read shaders
	glShaderSource(vShader, 1, &vSource, NULL);
	glShaderSource(fShader, 1, &fSource, NULL);

	// compile shaders
	glCompileShader(vShader);
	glCompileShader(fShader);

	// error check
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);
	checkError(status, "Failed to compile the vertex shader.");

	glGetShaderiv(fShader, GL_COMPILE_STATUS, &status);
	checkError(status, "Failed to compile the fragment shader.");

	// link
	glLinkProgram(*program);

	glGetProgramiv(*program, GL_LINK_STATUS, &status);
	checkError(status, "Failed to link the shader program object.");
}

void shaderInit() {
	GLenum err;
	err = glewInit();
	  if (err != GLEW_OK) {
	    cout << "GLEW error" << endl;
	  }
	  cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;

	  if (glewGetExtension("GL_ARB_fragment_shader") != GL_TRUE ||
	      glewGetExtension("GL_ARB_vertex_shader") != GL_TRUE ||
	      glewGetExtension("GL_ARB_shader_objects") != GL_TRUE ||
	      glewGetExtension("GL_ARB_shading_language_100") != GL_TRUE) {
	    cout << "Driver does not support OpenGL Shading Language" << endl;
	    exit(1);
	  }
}
