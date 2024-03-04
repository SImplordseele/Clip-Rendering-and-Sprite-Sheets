#include "definition.hpp"
int main(int argc, char* argv[]) {
	if(!Init()) return -1;
	if (!LoadMedia()) return -1;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_event)) {
			if (g_event.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		//Render top left circle
		g_image.render(0, 0, &circle[0]);
		//Render top right circle
		g_image.render(screen_width - circle[1].w, 0, &circle[1]);
		//Render bottom left circle
		g_image.render(0, screen_height - circle[2].h, &circle[2]);
		//Render bottom right circle
		g_image.render(screen_width - circle[3].w, screen_height - circle[3].h, &circle[0]);

		SDL_RenderPresent(g_screen);
	}
	CLOSE();
	return 0;
}