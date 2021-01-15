#include <SDL2/SDL.h>
#undef main

#include "imgui/imgui.h"
#include "imgui_sdl.h"

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("SDL2 ImGui Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	ImGui::CreateContext();
	ImGuiSDL::Initialize(renderer, 800, 600);

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
	{
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderTarget(renderer, nullptr);
	}

	bool run = true;
	while (run)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			ImGuiSDL::ProcessEvent(&e);
			if (e.type == SDL_QUIT) {
			   	run = false;
			}
		}
		
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Image");
		ImGui::Image(texture, ImVec2(100, 100));
		ImGui::End();

		SDL_SetRenderDrawColor(renderer, 114, 144, 154, 255);
		SDL_RenderClear(renderer);

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		SDL_RenderPresent(renderer);
	}

	ImGuiSDL::Deinitialize();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	ImGui::DestroyContext();

	return 0;
}
