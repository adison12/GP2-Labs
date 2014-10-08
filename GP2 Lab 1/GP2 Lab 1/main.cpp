#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

SDL_Window * window;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

bool running = true;

void render(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);

	glEnd();

	SDL_GL_SwapWindow(window);
}

void update(){}

void initWindow(int width, int height, bool fullscreen){
	window = SDL_CreateWindow("Lab1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
}

void CleanUp(){
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void initOpenGL(){
	glcontext = SDL_GL_CreateContext(window);
	
	if (!glcontext)
	{
		std::cout << "Error Creating OpenGL Context" << SDL_GetError << std::endl;
	}

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//function to set/reset viewport
void setViewport(int width, int height){
	GLfloat ratio;

	if (height == 0){
		height = 1;
	}

	ratio = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

int main(int argc, char * arg[]){

	initWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	initOpenGL();

	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;

		return -1;
	}

	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE){
				running = false;
			}
		}

		update();
		render();
	}





	CleanUp();
	return 0;
}

