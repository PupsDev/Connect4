#include <iostream>
#include <SDL.h>
#include <vector>
#include "SDL_image.h"

#include "connect.h"
#include "minimax.h"

const int grid_cell_size = 120;
const int offset = 20;
const int grid_cell_size_2 = grid_cell_size / 2 - offset;

int SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    // CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    // CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx)
    {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void drawCoin(SDL_Renderer *renderer, int x, int y, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    SDL_RenderDrawCircle(renderer, x + grid_cell_size_2 + offset, y + grid_cell_size_2 + offset, grid_cell_size_2);

    SDL_RenderFillCircle(renderer, x + grid_cell_size_2 + offset, y + grid_cell_size_2 + offset, grid_cell_size_2);
}
void drawCoinTextured(SDL_Renderer *renderer, int x, int y, SDL_Texture *texture)
{

    // SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    // SDL_RenderDrawCircle(renderer, x + grid_cell_size_2 + offset, y+ grid_cell_size_2+ offset, grid_cell_size_2);

    // SDL_RenderFillCircle(renderer, x + grid_cell_size_2 + offset, y+ grid_cell_size_2+ offset, grid_cell_size_2);

    // SDL_Rect dest = { (grid_width *grid_cell_size)/2-offset,
    //                         ( grid_height *grid_cell_size)/2+offset,

    //                          grid_cell_size/2,
    //                           grid_cell_size/2};//un SDL_Rect qui sers de destination à l'image
    SDL_Rect dest = {x + offset, y + offset, grid_cell_size / 2, grid_cell_size / 2}; // un SDL_Rect qui sers de destination à l'image
    SDL_RenderCopy(renderer, texture, NULL, &dest);                                   // copie de surface grâce au SDL_Renderer
}

void drawCoinTexturedFull(SDL_Renderer *renderer, int i, int j, int x, int y, SDL_Texture *texture)
{

    // SDL_RenderFillRect(renderer, &grid_cursor_ghost);
    // SDL_RenderDrawCircle(renderer, x + grid_cell_size_2 + offset, y+ grid_cell_size_2+ offset, grid_cell_size_2);

    // SDL_RenderFillCircle(renderer, x + grid_cell_size_2 + offset, y+ grid_cell_size_2+ offset, grid_cell_size_2);

    // SDL_Rect dest = { (grid_width *grid_cell_size)/2-offset,
    //                         ( grid_height *grid_cell_size)/2+offset,

    //                          grid_cell_size/2,
    //                           grid_cell_size/2};//un SDL_Rect qui sers de destination à l'image

    SDL_Rect imgPartRect;
    imgPartRect.x = i * 240;
    imgPartRect.y = j * 240;
    imgPartRect.w = 240;
    imgPartRect.h = 240;
    SDL_Rect dest = {x + offset - 2, y + offset - 2, grid_cell_size / 2 + 25, grid_cell_size / 2 + 25}; // un SDL_Rect qui sers de destination à l'image
    SDL_RenderCopy(renderer, texture, &imgPartRect, &dest);                                             // copie de surface grâce au SDL_Renderer
}
int main()
{

    Minimax<Puissance4> minimax;
    minimax.depth = 9;

    auto current = Puissance4();

    bool played = false;

    int grid_width = 7;
    int grid_height = 6;
    // Joueur 1 = 0
    // joueur 2 = 1
    int turn = 0;
    int colonne_selected;

    std::vector<std::vector<int>> columns(7);

    // SDL_Surface *surfaceRouge = IMG_Load("rouge.png");
    SDL_Surface *surfaceRougeFull = IMG_Load("texture/rougeV1_transparent.png");
    SDL_Surface *surfaceJauneFull = IMG_Load("texture/jauneV1_transparent.png");

    // SDL_Surface *surfaceBleu = IMG_Load("bleu.png");

    // + 1 so that the last grid lines fit in the screen.
    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 1;

    // Place the grid cursor in the middle of the screen.
    SDL_Rect grid_cursor = {
        .x = (grid_width - 1) / 2 * grid_cell_size,
        .y = (grid_height - 1) / 2 * grid_cell_size,
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

    // The cursor ghost is a cursor that always shows in the cell below the
    // mouse cursor.
    SDL_Rect grid_cursor_ghost = {grid_cursor.x, grid_cursor.y, grid_cell_size,
                                  grid_cell_size};

    // Color palette.
    // SDL_Color blue = {2, 43, 220}; // Barely Blue
    SDL_Color blue = {4, 33, 176};

    SDL_Color white{255, 255, 255};
    SDL_Color gray{200, 200, 200};
    SDL_Color red{255, 0, 0};
    SDL_Color green{0, 255, 0};
    SDL_Color yellow{255, 215, 0};

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
                                    &renderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // SDL_Texture *textureRouge = SDL_CreateTextureFromSurface(renderer, surfaceRouge);
    SDL_Texture *textureRougeFull = SDL_CreateTextureFromSurface(renderer, surfaceRougeFull);
    SDL_Texture *textureJauneFull = SDL_CreateTextureFromSurface(renderer, surfaceJauneFull);
    // SDL_Texture *textureBleu = SDL_CreateTextureFromSurface(renderer, surfaceBleu);
    SDL_SetWindowTitle(window, "SDL Grid");

    SDL_bool quit = SDL_FALSE;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;
    colonne_selected = 0;

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                case SDLK_UP:
                    grid_cursor.y -= grid_cell_size;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    grid_cursor.y += grid_cell_size;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    grid_cursor.x -= grid_cell_size;
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    grid_cursor.x += grid_cell_size;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                grid_cursor.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor.y = (event.motion.y / grid_cell_size) * grid_cell_size;
                // std::cout << "("<< grid_cursor.y/grid_cell_size <<", "<< grid_cursor.x/grid_cell_size <<")" << std::endl;
                colonne_selected = grid_cursor.x / grid_cell_size;

                current = current.play(turn, colonne_selected);

                columns = current.board;

                turn = 1 - turn;
                played = true;

                // if(turn ==0)
                // {
                //     columns[colonne_selected].push_back(1);
                //     turn = 1-turn;
                // }
                // else
                // {
                //     columns[colonne_selected].push_back(2);
                //     turn = 1-turn;

                // }

                break;
            case SDL_MOUSEMOTION:
                grid_cursor_ghost.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                grid_cursor_ghost.y = (event.motion.y / grid_cell_size) * grid_cell_size;

                if (!mouse_active)
                    mouse_active = SDL_TRUE;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                    mouse_hover = SDL_TRUE;
                else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                    mouse_hover = SDL_FALSE;
                break;
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }

        // Draw grid background.
        SDL_SetRenderDrawColor(renderer, blue.r, blue.g,
                               blue.b, blue.a);
        SDL_RenderClear(renderer);

        // Draw grid lines.
        for (int x = grid_cell_size_2 + offset; x < grid_width * grid_cell_size; x += grid_cell_size)
        {
            for (int y = grid_cell_size_2 + offset; y < grid_width * grid_cell_size; y += grid_cell_size)
            {

                drawCoin(renderer, y - grid_cell_size_2 - offset, x - grid_cell_size_2 - offset, white);
                // drawCoinT(renderer, y - grid_cell_size_2 - offset, x - grid_cell_size_2 - offset, white);
            }
        }

        // Draw grid ghost cursor.
        if (mouse_active && mouse_hover)
        {
            drawCoin(renderer, grid_cursor_ghost.x, grid_cursor_ghost.y, gray);
            // drawCoinT(renderer, grid_cursor_ghost.x, grid_cursor_ghost.y, gray);
        }
        // Draw coins
        for (int i = 0; i < columns.size(); i++)
        {
            int columnsize = columns[i].size();
            for (int j = 0; j < columnsize; j++)
            {
                if (columns[i][j] == 1)
                {

                    // drawCoin(renderer, (i * grid_cell_size), ((5 - j) * grid_cell_size), red);
                    // drawCoinTextured(renderer, (i * grid_cell_size), ((5 - j) * grid_cell_size), textureRouge);
                    drawCoinTexturedFull(renderer, i, j, (i * grid_cell_size), ((5 - j) * grid_cell_size), textureRougeFull);
                }
                else
                {
                    // drawCoin(renderer, (i * grid_cell_size), ((5 - j) * grid_cell_size), yellow);
                    // drawCoinTextured(renderer, (i * grid_cell_size), ((5 - j) * grid_cell_size), textureBleu);
                    drawCoinTexturedFull(renderer, i, j, (i * grid_cell_size), ((5 - j) * grid_cell_size), textureJauneFull);
                }
            }
        }

        SDL_RenderPresent(renderer);

        if (played)
        {
            // current = minimax.play(current, turn);
            current = minimax.play_alpha_beta_pruning(current, turn, INT_MIN, INT_MAX);

            turn = 1 - turn;
            played = false;
            columns = current.board;
        }

        // Joueur 2
        for (int i = 0; i < columns.size(); i++)
        {
            int columnsize = columns[i].size();
            for (int j = 0; j < columnsize; j++)
            {
                if (columns[i][j] == 1)
                {

                    // drawCoin(renderer, (i * grid_cell_size), ((5 - j) * grid_cell_size), red);
                    drawCoinTexturedFull(renderer, i, j, (i * grid_cell_size), ((5 - j) * grid_cell_size), textureRougeFull);
                }
                else
                {
                    // drawCoin(renderer, (i * grid_cell_size), ((5 - j) * grid_cell_size), yellow);
                    drawCoinTexturedFull(renderer, i, j, (i * grid_cell_size), ((5 - j) * grid_cell_size), textureJauneFull);
                }
            }
        }

        SDL_RenderPresent(renderer);

        if (current.end())
        {
            if (current.evaluate(1) == 0)
            {
                cout << "Égalité" << endl;
            }
            else if (current.evaluate(1) < 0)
            {
                cout << "Joueur 1 a gagné" << endl;
            }
            else
            {
                cout << "Joueur 2 a gagné" << endl;
            }
            sleep(5);
            break;
        }
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
