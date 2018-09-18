//
//  Window.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

Window::Window() // Load from file, or if not found w = 50 & h = 50
{
    // Load config
    reloadConfig();
 
    // Init SDL & subsystems
    SDL_Init(SDL_INIT_VIDEO | SDL_VIDEO_OPENGL | SDL_INIT_TIMER); // Add audio subsystem?
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    
    // Create window
#ifdef FULLSCREEN_ENABLED
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, loader->getInt("screen.width"), loader->getInt("screen.height"), SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
#else
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, loader->getInt("screen.width"), loader->getInt("screen.height"), SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
#endif
    
    context = SDL_GL_CreateContext(window);
    if(context == nullptr)
    {
        printf("[ERROR] Couldn't create GL context\n");
        exit(0);
    }
    
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        printf("[ERROR] Error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("[INFO] Initialized GLEW: \n\tGL   Version: %s\n\tGLSL Version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_GL_SetSwapInterval(1); // Vsync
    
    render_surface = SDL_CreateRGBSurfaceWithFormat(0, GAME_WIDTH, GAME_HEIGHT, 32, SDL_PIXELFORMAT_ARGB8888);
    SDL_SetSurfaceBlendMode(render_surface, SDL_BLENDMODE_BLEND);
    renderer = SDL_CreateSoftwareRenderer(render_surface);
    
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Alpha color --> Invisible
    
    if(TTF_Init() == -1)
    {
        printf("TTF_Init error: %s\n", TTF_GetError());
        exit(2);
    }
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
    font = TTF_OpenFont(GET_FILE_PATH(FONT_PATH, "Raleway-Regular.ttf"), 64); // Window opened = font initialized
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    if(!font)
    {
        ERROR("Couldn't open font file...");
        printf("%s\n", TTF_GetError());
        exit(0);
    }
    
    // Set up level
    level = Loader::loadLevel(GET_FILE_PATH(LEVEL_PATH, "/testlevel.level"), 50, 50, renderer);
    
    // Set up scaling
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SCALE_X = (float) w / (float) GAME_WIDTH;
    SCALE_Y = (float) h / (float) GAME_HEIGHT;
    SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
    
    // Reload elements of the menu
    reloadElementTextures(renderer);
    
    // Set up keystates & level
    keyStates = SDL_GetKeyboardState(NULL);
    level->window = this;
    openMenu(new PlayerOverlay(level->player));
    
    // Set up random stuff ( Debug & initial stuff on screen)
    
#ifdef DEBUG_OVERLAY
    openMenu(new DebugOverlay(level));
#endif
    
    openMenu(new MainMenu()); // Skip main menu
    // openMenu(new DialogOverlay("Hello World!\nThis is a test...\nThis is a test for very long lines\nwhich should get a line break or should\nbe newlined by hand"));
    
    openMenu(new LightOverlay(renderer));
    
    NPC *npc = new NPC(TILE_SIZE * 8, TILE_SIZE * 1, 0);
    npc->texts.push_back({3, 0, (char*) "Hello World\nI mean player..."});
    npc->texts.push_back({0, 0, (char*) "Please stop talking\nto me..."});
    level->addEntity(npc);
    
    Slime *slimeg = new Slime(10 * TILE_SIZE, 5 * TILE_SIZE, 1);
    Slime *slimeb = new Slime(10 * TILE_SIZE, 15 * TILE_SIZE, 10);
    Slime *slimeo = new Slime(10 * TILE_SIZE, 25 * TILE_SIZE, 20);
    Slime *slimer = new Slime(10 * TILE_SIZE, 35 * TILE_SIZE, 30);
    level->addEntity(slimeg);
    level->addEntity(slimeb);
    level->addEntity(slimeo);
    level->addEntity(slimer);
    
    Projectile *projectile = new Projectile(0, 0, (float) PI * 15.0f / 8.0f);
    level->addEntity(projectile);
        
    for(int i = 0; i < 22; i++)
    {
        level->addEntity(new EntityItem(5, i, new Item("test", renderer)));
        level->addEntity(new EntityItem(3, i, new Item("test2", renderer)));
    }
}

Window::~Window()
{
    delete level;
    SDL_DestroyWindow(window);
}

void Window::update()
{
    // Put update stuff here
    float x = 0, y = 0;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_UP])]) y -= SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_DOWN])]) y += SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_RIGHT])]) x += SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_LEFT])]) x -= SPEED;
    
    level->player->updateMovement(x, y); // Update player movement
    level->player->actionPressed = keyStates[GLOBAL_KEY_CONFIG[BUTTON_INVENTORY]];
    
    level->update(); // Update rest of level according to player
}

void Window::openMenu(Menu *m)
{
    m->active = true;
    menus.push_back(m);
    m->open(this);
}

void Window::render(SDL_Renderer *renderer)
{
    level->render(renderer); // Render level, but don't update
    
    for(int i = 0; i < (int) menus.size(); i++)
    {
        if(menus[i]->shouldWindowClose() || menus[i]->menuShouldBeClosed)
        {
            if(i != 0) menus[menus.size() - 1]->active = true;
            menus[i]->onClose();
            menus.erase(menus.begin() + i);
        } else menus[i]->render(renderer, keyStates);
    }
}

uint32_t secondCallback(uint32_t delay, void *args)
{
    Window* w = (Window*) args;
    w->fps = w->frames;
    w->frames = 0;
    return delay;
}

static const float *verticies = new float[2 * 6]
{
    -1, -1,
    1, -1,
    1, 1,
    -1, -1,
    -1, 1,
    1, 1
};

static const float *uv_vert = new float[2 * 6]
{
    0, 0,
    1, 0,
    1, 1,
    0, 0,
    0, 1,
    1, 1
};

void Window::runGameLoop()
{
    running = true;
    SDL_Event e;
    SDL_AddTimer(1000, secondCallback, this);
    
    auto clock = std::chrono::high_resolution_clock(); // Create high accuracy clock
    
    bool mousePressed = false;
    
    // Init gl
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), verticies, GL_STATIC_DRAW);
    
    GLuint uv;
    glGenBuffers(1, &uv);
    glBindBuffer(GL_ARRAY_BUFFER, uv);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), uv_vert, GL_STATIC_DRAW);
    
    GLuint vert = compileShader(GET_FILE_PATH(LEVEL_PATH, "shader.vert"), GL_VERTEX_SHADER);
    GLuint frag = compileShader(GET_FILE_PATH(LEVEL_PATH, "shader.frag"), GL_FRAGMENT_SHADER);
    GLuint prog = glCreateProgram();
    
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    
    GLint status;
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        printf("Couldn't link shader program...\n");
    }
    
    while(running)
    {
        ++frames;
        auto start_time = clock.now(); // Now
        
        while(SDL_PollEvent(&e))
        {
            if((e.type == SDL_MOUSEBUTTONDOWN && mousePressed) || (e.type == SDL_MOUSEBUTTONUP && !mousePressed))
            {
                continue;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN) mousePressed = true;
            if(e.type == SDL_MOUSEBUTTONUP) mousePressed = false;
            
            if(e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION)
            {
                // No touch events...
                continue;
            }

            for(int i = (int) menus.size() - 1; i >= 0; i--) menus[i]->updateElements(e);
            
            // Handle events of the window
            if(e.type == SDL_WINDOWEVENT)
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
				else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					int w, h;
					SDL_GetWindowSize(window, &w, &h);
					SCALE_X = (float)w / (float)GAME_WIDTH;
					SCALE_Y = (float)h / (float)GAME_HEIGHT;
					SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
				}
            }
            else if(e.type == SDL_QUIT) exitGame(this); // Just close the whole thing...
            
            // Player & Level control:
            if(!toUpdate) continue; // We're paused...
            
            if(e.type == SDL_KEYDOWN)
            {                
                if(e.key.keysym.sym == SDLK_ESCAPE) openMenu(new PauseMenu());
                else if(e.key.keysym.sym == GLOBAL_KEY_CONFIG[BUTTON_SHOOT])
                {
                    for(int i = 0; i < 5; i++) // Shoot n projectiles
                    {
                        ExplodingProjectile *p = new ExplodingProjectile(NORMAL, level->player->x_pos, level->player->y_pos, (float) TO_RAD(rand() % 360));
                        level->addEntity(p);
                    }
                }
                else if(e.key.keysym.sym == GLOBAL_KEY_CONFIG[BUTTON_INVENTORY]) openMenu(new Inventory(level->player));
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    int xdif = (int) (e.button.x / SCALE_X) - PLAYER_OFFSET_X + level->player->xoff;
                    int ydif = (int) (e.button.y / SCALE_Y) - PLAYER_OFFSET_Y + level->player->yoff;
                    float angle = -(float) atan2(ydif, xdif);
                    
                    Projectile *p = new Projectile(level->player->x_pos, level->player->y_pos, angle);
                    level->addEntity(p);
                }
            }
        }
        
        glClearColor(0, 1, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // Black
        SDL_RenderClear(renderer); // Everything black
        
        // Update & render
        toUpdate = true;
        for(int i = 0; i < (int) menus.size(); i++) if(!menus[i]->shouldLevelBeUpdated) toUpdate = false;
        if(toUpdate) update();
        render(renderer);
        
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, render_surface->w, render_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, render_surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glBindTexture(GL_TEXTURE_2D, texID);
        
        glUseProgram(prog);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, uv);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glUseProgram(0);
        
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            printf("[ERROR] GL Error: %d\n", err);
        }
        
        //glDeleteTextures(1, &texID);
        
        auto end_time = clock.now();
        auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::this_thread::sleep_for(std::chrono::microseconds(16666) - difference);
        
        // SDL_RenderPresent(renderer); // Draw & limit FPS when opened
        SDL_GL_SwapWindow(window);
    }
    
    exitGame(this);
}

void Window::reloadConfig()
{
    loader = new ConfigLoader(GET_FILE_PATH(LEVEL_PATH, "informatik.config"));
}

void exitGame(Window *window)
{
    Loader::LevelLoader loader(window->level);
    loader.saveFile(window->level->levelFile.c_str());
    
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    SDL_Quit();
        
    exit(0);
}
