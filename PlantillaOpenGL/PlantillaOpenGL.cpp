// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "Vertice.h"
using namespace std;

Shader *shader;
GLuint posicionID;
GLuint colorID;

vector<Vertice> triangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

void inicializarTriangulo() {
	Vertice v1 =
	{
		vec3(0.0f, 0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f,1.0f)
	};
	Vertice v2 =
	{
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f,1.0f)
	};
	Vertice v3 =
	{
		vec3(0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f,1.0f)
	};

	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}

void dibujar() {
	//Elegir el sahder 
	shader->enlazar();
	//Elegir un vertex array
	glBindVertexArray(vertexArrayTrianguloID);
	//dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());
	//Soltar el vertex array
	glBindVertexArray(0);
	//Soltar Shader
	shader->desenlazar();
}

void actualizar() {


}



int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//Si no se pudo iniciar glfw
	//terminamos ejecución 
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Si se pudo inciar GLFW
	//Entonces inicializamos la ventana

	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//Si no podemos iniciar la ventana 
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecer el contexto
	glfwMakeContextCurrent(window);


	//Una vez establecido el contexto
	//Activamos fnciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK)
	{
		cout << glewGetErrorString(errorGlew);

	}


	const GLubyte *versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: "
		<< versionGL;

	inicializarTriangulo();

	const char *rutaVertex =
		"VertexShader.shader";
	const char *rutaFragment =
		"FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atrubutos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");


	//Desenlazar el shade
	shader->desenlazar();

	//Crear un vertec array
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);

	//Crear vertex buffer
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);

	//Llenar el buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);

	//Habiliar atributps de shader
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	//Especificar a OpénGL como se va a comunicar
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Soltar vertex array y buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		glViewport(0, 0,1024, 768);
		//Establecer el color de orrado
		glClearColor(0.5, 0.4, 1, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

