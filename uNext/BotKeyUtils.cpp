#include <SDL_events.h>

#include "Core.h"

#include "BotKeyUtils.h"

bool BotKeyUtils::isAlreadyJumping()
{
	if (1 == CCore::oMap->getPlayer()->jumpState || CCFG::keySpace) {
		return true;
	}

	return false;
}

bool BotKeyUtils::isAlreadyGoingRight()
{
	if (CCore::keyDPressed) {
		return true;
	}

	return false;
}

void BotKeyUtils::pressKey(int key)
{
	SDL_Event sdlEvent;
	sdlEvent.type = SDL_KEYDOWN;
	sdlEvent.key.keysym.sym = key;
	SDL_PushEvent(&sdlEvent);
}

void BotKeyUtils::releaseKey(int key)
{
	SDL_Event sdlEvent;
	sdlEvent.type = SDL_KEYUP;
	sdlEvent.key.keysym.sym = key;
	SDL_PushEvent(&sdlEvent);
}