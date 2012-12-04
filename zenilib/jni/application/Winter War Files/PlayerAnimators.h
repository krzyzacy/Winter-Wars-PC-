#pragma once

#include "PlayerAnimator.h"

#include "Seen_Object.h"

class Jumping : public PlayerAnimator
{	
public:
	Jumping() : JumpFrame(1.0f), Frame(1), falling(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

	void proceed() { falling = true; }

private:
	bool falling;
	float JumpFrame;
	int Frame; 
};

class Throwing : public PlayerAnimator
{	
public:
	Throwing() : ThrowFrame(1.0f), Frame(1), finished(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float ThrowFrame;
	int Frame;
	bool finished;
};

class Packing : public PlayerAnimator
{	
public:
	Packing() : PackFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float PackFrame;
	int Frame;
};

class Walking : public PlayerAnimator
{	
public:
	Walking() : WalkFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float WalkFrame;
	int Frame;
};


class Standing : public PlayerAnimator
{	
public:
	Standing() : StandFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();
	
private:
	float StandFrame;
	int Frame;
};

class Scooping : public PlayerAnimator
{	
public:
	Scooping() : ScoopFrame(1.0f), Frame(0) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float ScoopFrame;
	int Frame;
};

class Flinching : public PlayerAnimator
{	
public:
	Flinching() : FlinchFrame(1.0f), Frame(0), finished(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	bool finished;
	float FlinchFrame;
	int Frame;
};

class Dying : public PlayerAnimator
{	
public:
	Dying() : DieFrame(1.0f), Frame(0) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	PlayerAnimator *get_next(PlayerEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float DieFrame;
	int Frame;
};
