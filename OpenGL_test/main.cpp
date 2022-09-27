
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>



int main() 
{
	//Initialisation
	glfwInit();
	//charger la bonne version de openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Core package
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, 0.0f,
		0.5f, 0.0f,
		0.0f, 0.5f,

		-0.25f, 0.25f,
		0.0f, 0.0f,
		0.25f, 0.25f
	};

	GLuint indices[] = 
	{
		0,3,4, //premier triangle
		4,5,1, //second triangle
		3,5,2  //third triangle
	};


	//creation de la fenetre
	GLFWwindow* window = glfwCreateWindow(800, 800, "My first window", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//charge les trucs de glad, pour utiliser les fonctions openGL
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAOs[1], VBOs[1], EBO;
	glGenVertexArrays(1, &VAOs[0]);
	glGenBuffers(1, &VBOs[0]);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//faire en fonction des vertices genre 2D = 2 et 3D = 3
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//creation du back buffer avec la couleur qu'on veut
	glClearColor(1.0f, 0.5f, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//swap le back buffer et front buffer
	glfwSwapBuffers(window);

	float previousTime = 0;
	float angle = 0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//afficher window et fermer que quand on clic sur la croix
	while (!glfwWindowShouldClose(window)) 
	{
		
		if ((float)glfwGetTime() > previousTime)
		{
			angle += 0.1f;
			previousTime = (float)glfwGetTime() + 0.1f;
		}
		/*glClearColor((float)cos(angle), (float)sin(angle), (float)tan(angle), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);*/

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_LINE_LOOP, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAOs[0]);
	glDeleteBuffers(1, &VBOs[0]);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}