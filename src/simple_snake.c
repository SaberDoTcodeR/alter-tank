#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

const int step = 5;
void moveCircle(SDL_Keycode key, double* snake_x, double* snake_y) {
	switch (key) {
		case SDLK_UP:
			*snake_y -= step;
			break;
		case SDLK_DOWN:
			*snake_y += step;
			break;
		case SDLK_RIGHT:
			*snake_x += step;
			break;
		case SDLK_LEFT:
			*snake_x -= step;
			break;
	}
}

bool hasEatenFood(double snake_x, double snake_y, double food_x, double food_y, double radius, double rx, double ry) {
	double distance = sqrt(pow(snake_x - food_x, 2) + pow(snake_y - food_y, 2));
	return distance < radius + (rx + ry) / 2;
}

void changeFoodLocation(double * food_x, double * food_y) {
	*food_x = rand() % 600 + 100;
	*food_y = rand() % 400 + 100;
}

const int EXIT = 12345;
int handleEvents(double* snake_x, double* snake_y) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
    	if (event.type == SDL_QUIT)
    	    return EXIT;
    	if (event.type == SDL_KEYDOWN)
    		moveCircle(event.key.keysym.sym , snake_x, snake_y);
    }
}
#ifdef main
#undef main
#endif /*main*/
int main(int argc,char*argv[]) {
    double snake_x = 100;
    double snake_y = 100;
    double snake_radius = 20;
    int snake_score = 0;

    double food_x = 300;
    double food_y = 300;
    double food_rx = 15;
    double food_ry = 10;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("workshop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                          SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface *image = SDL_LoadBMP("tank.bmp");
    if (image == NULL)
        SDL_ShowSimpleMessageBox(0, "Image init error", SDL_GetError(),
                                 window);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,
                                                        image);
    if (texture == NULL)
        SDL_ShowSimpleMessageBox(0, "Texture init error",
                                 SDL_GetError(), window);

    int begining_of_time = SDL_GetTicks();
    const double FPS = 50;
    const int SPEED = 70;

        int start_ticks = SDL_GetTicks();

        SDL_Rect dstrect;
        SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
        dstrect.w /= 4;
        dstrect.h /= 4;
        float x_pos = 500;
        float y_pos = 400;
        float x_vel = 0;
        float y_vel = 0;


        //SDL_RenderCopy(renderer, texture, NULL, NULL);


        int close_r = 0;
        while oli(!close_r)
        {
            int up = 0, down = 0, right = 0, left = 0;
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        close_r = 1;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.scancode) {
                            case SDL_SCANCODE_UP :
                                up = 1;
                                break;
                            case SDL_SCANCODE_DOWN :
                                down = 1;
                                break;
                            case SDL_SCANCODE_RIGHT :
                                right = 1;
                                break;
                            case SDL_SCANCODE_LEFT :
                                left = 1;
                                break;
                        }
                        break;
                }
            }
            if (up&&!down){ y_vel = -SPEED;x_vel=0;}

            if (down&&!up)
            {y_vel = +SPEED;
            x_vel=0;}

            if (right&&!left)
            { y_vel=0;x_vel = SPEED;}

            if (left&&!right)
            {y_vel=0;x_vel = -SPEED;}
            x_pos += x_vel / 30;
            y_pos += y_vel / 30;
            if (x_pos <= 0)x_pos = 0;
            if (y_pos <= 0)y_pos = 0;
            if (x_pos > 800 - dstrect.w)
                x_pos = 800 - dstrect.w;
            if (y_pos > 600 - dstrect.h)
                y_pos = 600 - dstrect.h;
            dstrect.x =(int)x_pos;
            dstrect.y =(int)y_pos;SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL ;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL , &dstrect, 0.001, NULL, flip);
            //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
            SDL_RenderPresent(renderer);
            while (SDL_GetTicks() - start_ticks < 1000 / FPS);
            x_vel=0;
            y_vel=0;



        }



    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
