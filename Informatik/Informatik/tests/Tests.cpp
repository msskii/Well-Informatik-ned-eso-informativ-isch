#include "Tests.hpp"

// Only accessable for tests
namespace Tests
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running = false;
    
    void createWindow()
    {
        SDL_Init(SDL_INIT_EVERYTHING); // For tests: init every subsystem there is
        window = SDL_CreateWindow("Tests", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    }
    
    void handleEvents()
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_WINDOWEVENT)
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
            }
        }
    }
    
    void destroyWindow()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}

void Tests::testPNG()
{
    createWindow();
    
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *s = IMG_Load((TEXTURE_PATH + "/test.png").c_str());
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    
    running = true;
    while(running)
    {
        handleEvents();
        SDL_RenderCopy(renderer, t, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyTexture(t);
    SDL_FreeSurface(s);
    
    destroyWindow();
}

void Tests::testAudio()
{
	Mix_Init(MIX_INIT_MP3);
}

void Tests::testSockets()
{
	SDL_Init(SDL_INIT_VIDEO); // Init what here?
	SDLNet_Init();

	IPaddress address;
	SDLNet_ResolveHost(&address, NULL, 5543); // Create listening socket on port 5543
	TCPsocket server = SDLNet_TCP_Open(&address); // Open the server on said address
	TCPsocket client = NULL;

	while(client == NULL) client = SDLNet_TCP_Accept(server);

	const char *data = "Hello World!\n\0";
	SDLNet_TCP_Send(client, data, 14);
}

void Tests::testLevelLoader()
{
    printf("Textfile of level: %s\n", LevelLoader("testlevel.level").buildLevel()->textFile); // Test loading level
}

void Tests::testNPCLoader()
{
    loadNPCs("test.npc");
}

void Tests::testTextLoader()
{
    TextLoader("test.text");
}
