#pragma once 

#include <stdio.h>
#include <stdlib.H>
#define GLFW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

using namespace std;


class Shader {
public:
	GLuint getID(); //obtiene el ID del Shader
	Shader(const char * rutaVertex, const char * rutaFragment);

	void enlazar();
	void desenlazar();

private:
	GLuint shaderID;
	void verificarCompilacion(GLuint id);
	void verificarVinculacion(GLuint id);

};