/* app.c */

#include "in/app.h"
#include "in/camera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <GL/gl.h>
#include <GL/glu.h>

static SDL_Window* win = NULL;
static SDL_GLContext *ctx = NULL;

Camera cam;

Grid grid;

Object objects[MAX_OBJECTS];
int obj_count = 0;

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return false;

	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	win = SDL_CreateWindow("Solar system sim!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!win) {
		SDL_Quit();
		return false;
	}

	ctx = SDL_GL_CreateContext(win);
	if (!ctx) {
		SDL_DestroyWindow(win);
		SDL_Quit();
		return false;
	}
	SDL_GL_SetSwapInterval(1);

	gl_setup();

	cam_init(&cam);
	init_objects(objects, &obj_count);
	init_grid(&grid);

	return true;
}

void run() {
	bool running = true;
	bool paused = false;

	int winW, winH;
	
	SDL_Event ev;
	
	while (running) {
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_WINDOWEVENT:
					if (ev.window.event == SDL_WINDOWEVENT_RESIZED || ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						winW = ev.window.data1;
						winH = ev.window.data2;
						gl_resize(winW, winH);
					}
					break;
				case SDL_KEYDOWN:
					switch (ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = false;
							break;
						case SDLK_SPACE:
							paused = !paused;
							break;
						case SDLK_r:
							// reset everything somehow
							break;
						default:
							break;
					}
				default:
					break;
			}
			// handle_cam_event(&cam, &ev, winW, winH);
		}

		if (!paused) {
			// update_scene();
		}

		// render_scene(&cam);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		apply_cam_view(&cam);

		render_grid(&grid);
		SDL_GL_SwapWindow(win);
	}
}

void gl_setup(){
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    gl_resize(SCREEN_WIDTH,SCREEN_HEIGHT);
}

void gl_resize(int w, int h){
    if (h==0) h=1;
    float aspect = (float)w/(float)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.01, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void cleanup() {
	if (ctx) {
		SDL_GL_DeleteContext(ctx);
	}
	if (win) {
		SDL_DestroyWindow(win);
	}
	SDL_Quit();
}
