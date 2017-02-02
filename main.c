#include <GLFW/glfw3.h>

#include "render.c"

#define MULTILINE(...) #__VA_ARGS__

const float vertices[] = {
	0.0,  0.5, 0.0,
	0.5, -0.5, 0.0,
	-0.5, -0.5, 0.0
};

const unsigned char colors[] = {
	255, 0, 0,
	0, 255, 0,
	0, 0, 255
};

const char* vs = MULTILINE(
	in vec3 vp;
	void main() {
	  	gl_Position = vec4(vp, 1.0);
	}
);

const char* fs = MULTILINE(
	out vec4 frag_colour;
	void main() {
	  	frag_colour = vec4(0.5, 0.0, 0.5, 1.0);
	}
);

int main(void) {

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "▲", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

	GLuint shader = create_shader(vs, fs);
	glUseProgram(shader);
	
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        render_triangles(vertices, colors);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

