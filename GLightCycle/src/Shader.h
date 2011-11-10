/*
 * Shader.h
 *
 *  Created on: Nov 9, 2011
 *      Author: kimsj
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>

void shaderInit();
GLuint EmptyTexture(int, int);
const char *readShaderSource(const char*);
void checkError(GLint, const char *);
void initShader(const GLchar*, const GLchar*, GLint *);

#endif /* SHADER_H_ */
