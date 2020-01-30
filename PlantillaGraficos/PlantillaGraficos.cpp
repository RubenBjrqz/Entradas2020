// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float posXTriangulo = 0.0f, posYTriangulo = 0.0f;

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_RIGHT)
	{
		posXTriangulo += 0.01;
	}
	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_UP)
	{
		posYTriangulo += 0.01;
	}
	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_LEFT)
	{
		posXTriangulo -= 0.01;
	}
	if (action == GLFW_PRESS || action == GLFW_REPEAT && key == GLFW_KEY_DOWN)
	{
		posYTriangulo -= 0.01;
	}
}

void actualizar() 
{
	//posXTriangulo += 0.00001;
}

void dibujar()
{
	glPushMatrix();

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.0f, 0.6f, 0.6f);

	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();

}

int main()
{
	//Declarar una ventana
	GLFWwindow* window;

	//Si no se pudo iniciar GLFW terminamos ejecucion
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Colors", NULL, NULL);

	//Si no se pudo crear la ventana terminamos la ejecucion
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK)
	{
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL =
		glGetString(GL_VERSION);
	cout << "Version OPENGL: " << versionGL;

	//Establecemos que con cada evento de teclado
	//se llama a la función teclado_callback
	glfwSetKeyCallback(window, teclado_callback);

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(0.1,0.1,0.1,1);
		//Borrar!
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Actualizar valores y dibujar
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo eliminamos venta y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}
