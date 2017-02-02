#include <GLFW/glfw3.h>

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

GLuint create_shader(const char* vs_src, const char* fs_src) {

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vs_src, NULL);
	glCompileShader(vs);

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fs_src, NULL);
	glCompileShader(fs);

	GLuint shader = glCreateProgram();
	glAttachShader(shader, fs);
	glAttachShader(shader, vs);
	glLinkProgram(shader);

	return shader;
}

void render_triangles(const float* vertices, const unsigned char* colors) {

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
	//glTexCoordPointer( size, GL_FLOAT, 0, &d.t.front());

	//glDrawElements(d.mode, d.i.size(), GL_UNSIGNED_SHORT, &d.i.front());
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

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

