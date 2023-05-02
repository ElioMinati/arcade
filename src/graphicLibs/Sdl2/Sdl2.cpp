/*
** EPITECH PROJECT, 2023
** arcade
** File description:
** Sdl2
*/

#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include "Sdl2.hpp"
#include "MapMessages.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

extern "C" Arcade::IGraphicLib *entryPoint()
{
    return new Arcade::Sdl2();
}

Arcade::Sdl2::Sdl2()
{
}

void Arcade::Sdl2::setGraphicMaps(std::unordered_map<char, Arcade::Colors> colorMap, std::unordered_map<char, char> textureMap)
{
    _colorMap = colorMap;
    _charDisplayMap = textureMap;
}

Arcade::Keys Arcade::Sdl2::getUserInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return Arcade::Keys::ESC;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        return Arcade::Keys::UP_ARROW;
                    case SDLK_DOWN:
                        return Arcade::Keys::DOWN_ARROW;
                    case SDLK_LEFT:
                        return Arcade::Keys::LEFT_ARROW;
                    case SDLK_RIGHT:
                        return Arcade::Keys::RIGHT_ARROW;
                    case SDLK_ESCAPE:
                        return Arcade::Keys::ESC;
                    case SDLK_KP_ENTER:
                        return Arcade::Keys::ENTER;
                    case SDLK_v:
                        return Arcade::Keys::V;
                    case SDLK_g:
                        return Arcade::Keys::G;
                    case SDLK_m:
                        return Arcade::Keys::M;
                    case SDLK_r:
                        return Arcade::Keys::R;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return Arcade::Keys::NO;
}

void Arcade::Sdl2::displayGrid(std::vector<std::string> map)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (map == Arcade::gameOverMessage) {
        int screenWidth, screenHeight;
        SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

        int elementWidth, elementHeight;
        SDL_QueryTexture(gameOver, NULL, NULL, &elementWidth, &elementHeight);

        SDL_Rect destRect = {(screenWidth - elementWidth) / 2, (screenHeight - elementHeight) / 2, elementWidth, elementHeight};
        SDL_RenderCopy(renderer, gameOver, NULL, &destRect);
    } else {
        for (std::size_t y = 0; y < map.size(); ++y) {
            for (std::size_t x = 0; x < map[y].size(); ++x) {
                if (rawSpritesMap.size() > 0 && userDefinedSprites.find(map[y][x]) != userDefinedSprites.end()) {
                    SDL_Rect destRect = {static_cast<int>(x) * displayGap, static_cast<int>(y) * displayGap, displayGap, displayGap};
                    SDL_RenderCopy(renderer, userDefinedSprites[map[y][x]], NULL, &destRect);
                } else if (_colorMap.find(map[y][x]) != _colorMap.end()) {
                    int w = 0;
                    int h = 0;
                    SDL_QueryTexture(customColorSprites[_colorMap[map[y][x]]], NULL, NULL, &w, &h);
                    SDL_Rect destRect = { static_cast<int>(x) * displayGap, static_cast<int>(y) * displayGap, w, h };
                    SDL_RenderCopy(renderer, customColorSprites[_colorMap[map[y][x]]], NULL, &destRect);
                } else {
                    int w = 0;
                    int h = 0;
                    SDL_QueryTexture(customColorSprites[Arcade::Colors::ARC_COLOR_BLACK], NULL, NULL, &w, &h);
                    SDL_Rect destRect = { static_cast<int>(x) * displayGap, static_cast<int>(y) * displayGap, w, h };
                    SDL_RenderCopy(renderer, customColorSprites[Arcade::Colors::ARC_COLOR_BLACK], NULL, &destRect);
                }
            }
        }
    }
}

void Arcade::Sdl2::displayScore(int score, std::vector<std::string> grid)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::string("score: " + std::to_string(score)).c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int x = (grid[0].size() * displayGap) + 50;
    int y = static_cast<int>((grid.size() * displayGap) / 2);
    SDL_Rect rect = {x, y, 200, 100};
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Arcade::Sdl2::displayHighScore(int score, std::vector<std::string> grid)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::string("High Score: " + std::to_string(score)).c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int x = (grid[0].size() * displayGap) + 50;
    int y = static_cast<int>((grid.size() * displayGap) / 2 + 100);
    SDL_Rect rect = {x, y, 200, 100};
    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Arcade::Sdl2::start()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Map2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    for (auto &color: colorPairs) {
        SDL_Surface *surface = SDL_CreateRGBSurface(0, displayGap, displayGap, 32, 0, 0, 0, 0);
        Uint32 pixel = SDL_MapRGBA(surface->format, color.second.r, color.second.g, color.second.b, color.second.a);
        SDL_FillRect(surface, NULL, pixel);
        
        customColorSprites[color.first] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    font = TTF_OpenFont("assets/Russo_One.ttf", 24);
    gameOver = SDL_CreateTextureFromSurface(renderer, IMG_Load("assets/game-over.jpg"));
    SDL_Delay(1000/60);
}

void Arcade::Sdl2::setSpritesMap(std::unordered_map<char, std::string> spriteMap)
{
    rawSpritesMap.clear();
    userDefinedSprites.clear();
    rawSpritesMap = spriteMap;
    for (auto &rawSprite: rawSpritesMap) {
        userDefinedSprites[rawSprite.first] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, displayGap, displayGap);
        userDefinedSprites[rawSprite.first] = IMG_LoadTexture(renderer, rawSprite.second.c_str());
    }
}

std::size_t Arcade::Sdl2::playSound(std::string path)
{
    static_cast<void>(path);
    // if (path.empty())
    //     return 0;
    // if (soundBuffers.find(path) != soundBuffers.end()) {
    //     SDL_AudioSpec spec;
    //     Uint32 audio_len;

    //     soundBuffers[path] = buf;
    //     if (!soundBuffers[path] = SDL_LoadWAV_RW(file, 1, &spec, &buf, &audio_len)) {
    //         soundBuffers.erase(path);
    //         return 0;
    //     }
    // }
    // currentMusicPlaying[usedMusicIndex] = (soundBuffers[path]);
    // SDL_PauseAudioDevice(currentMusicPlaying[usedMusicIndex], 0);
    // usedMusicIndex++;
    // return usedMusicIndex - 1;
    return 0;
}

void Arcade::Sdl2::stopSound(std::size_t index)
{
    static_cast<void>(index);
    // if (currentMusicPlaying[index] != currentMusicPlaying.end()) {
    //     SDL_PauseAudioDevice(currentMusicPlaying[index], 1);
    //     currentMusicPlaying.erase(index);
    // }
}


Arcade::Sdl2::~Sdl2()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    customColorSprites.clear();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}