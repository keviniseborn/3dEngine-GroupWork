#ifndef LEVEL_CONTROLLER_H
#define LEVEL_CONTROLLER_H

#include "behaviour\behaviour.h"
#include "physics\physicsBody.h"
#include "rendering\GUI.h"
#include "custom\playerController.h"
#include "behaviour\custom.h"
#include "core\input.h"

/*! \brief Custom Enemy Class

	Handles enemy bullet logic

*/

class LevelController : public Behaviour
{
public:
	LevelController(){};
	~LevelController(){};
	int getScore()		{return _score;}
	void incScore(int i){_score+=i;}
protected:
	void initialize();
	void onActive();
	void update(float t); //!< Update function;
	 
private:
	PlayerController* _player;
	SPtr_GUI _gui;
	int _score;
};







#endif