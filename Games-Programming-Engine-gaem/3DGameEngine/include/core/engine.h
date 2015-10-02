#ifndef ENGINE_H
#define ENGINE_H

// Includes
#include <iostream>
#include <string>

#include <glew\GL\glew.h>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <antTweakBar\AntTweakBar.h>

#include "core\assets.h"
#include "core\sceneManager.h"
#include "core\objectManager.h"
#include "rendering\renderSystem.h"
#include "physics\physicsSystem.h"

#include "core\input.h"
#include "rendering\camera.h"
#include "rendering\modelRenderer.h"


/*! \brief The main game engine

	This class manages all subsystems and resources for the game. It is the heart
	of the engine and is responsible for starting up and shutting down systems as
	well as the game loop.

*/
class Engine
{
public:
	Engine(){};
	~Engine(){};

	sf::RenderWindow* startEditorMode(HWND windowHandle);
	sf::RenderWindow* startGameMode();
	
	void startup(); //!< Initalize everything needed to run the engine
	void initGame(); //!< Returns the game to it's initial state
	void processEvent(sf::Event e); //!< Handle SFML event
	void updateInput(float t); //!< Calls update in the Input singleton class. Call straight after event poll
	void update(float t); //!< Update all sub systems here!
	void render();
	void renderEditorMode(Camera* camera); //!< Render through a given camera. Only used by editor to render through special editor camera
	void resetInput(); //!< Must be called at end of frame to reset key states
	void shutDown(); //!< Anything that needs to be stopped elegantly or in certain order, put here

	
	SceneManager* getSceneManager(); //!< The editor requires a reference to this and can use this getter to obtain it
	ObjectManager* Engine::getObjectManager();

	// Getters, for main to get properties for Editor for example
	int getWidth();
	int getHeight();

private:
	// Core Engine
	sf::RenderWindow _window;
	SceneManager _sceneMngr;
	ObjectManager _objMngr;
	Input* _input;
	
	// Sub Systems
	RenderSystem _rendSys;
	BehaviourSystem _behvrSys;
	PhysicsSystem _physicsSys;

	// Engine Vars
	sf::Vector2u _screenSize;

	// Time
	float _refreshRate;
	float _fixedTime; //!< Fixed delta time
};



#endif