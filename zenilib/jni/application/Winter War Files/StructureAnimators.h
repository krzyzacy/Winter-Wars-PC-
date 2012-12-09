#pragma once

#include "StructureAnimator.h"

#include "Seen_Object.h"

/*---------------------------------------------
				FORTRESS
---------------------------------------------*/

class Fort_spin : public StructureAnimator
{	
public:
	Fort_spin() : FSFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float FSFrame;
	int Frame; 
};

/*---------------------------------------------
				SNOWMAN
---------------------------------------------*/

class Snowman_stand : public StructureAnimator
{	
public:
	Snowman_stand() : SMFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float SMFrame;
	int Frame; 
};

class Snowman_thwr : public StructureAnimator
{	
public:
	Snowman_thwr() : SMFrame(1.0f), Frame(1), finished(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	bool finished;
	float SMFrame;
	int Frame; 
};

class Snowman_thwl : public StructureAnimator
{	
public:
	Snowman_thwl() : SMFrame(1.0f), Frame(1), finished(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	bool finished;
	float SMFrame;
	int Frame; 
};

/*---------------------------------------------
				FACTORY
---------------------------------------------*/

class Factory_spin : public StructureAnimator
{	
public:
	Factory_spin() : FSFrame(1.0f), Frame(1), finished(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	bool finished;
	float FSFrame;
	int Frame; 
};

class Factory_stop : public StructureAnimator
{	
public:
	Factory_stop() : FSFrame(1.0f), Frame(1), finished(false) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	bool finished;
	float FSFrame;
	int Frame; 
};

/*---------------------------------------------
				HEALING POOL
---------------------------------------------*/

class Pool_stand : public StructureAnimator
{	
public:
	Pool_stand() : PSFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float PSFrame;
	int Frame; 
};

class Pool_heal : public StructureAnimator
{	
public:
	Pool_heal() : PHFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float PHFrame;
	int Frame; 
};

/*---------------------------------------------
				PRESENTS
---------------------------------------------*/

class Present_wrapped : public StructureAnimator
{	
public:
	Present_wrapped() : PWFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float PWFrame;
	int Frame; 
};

class Present_unwrapped : public StructureAnimator
{	
public:
	Present_unwrapped() : PUFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float PUFrame;
	int Frame; 
};

/*---------------------------------------------
				TREE
---------------------------------------------*/

class Tree_owned : public StructureAnimator
{	
public:
	Tree_owned() : TOFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float TOFrame;
	int Frame; 
};

class Tree_unowned : public StructureAnimator
{	
public:
	Tree_unowned() : TUFrame(1.0f), Frame(1) {}
	/* choose the frame to currently render and set it */
	void animate(Zeni::Model *);

	/* get the next state based on what event happened */
	StructureAnimator *get_next(StructureEvent_e);
	
	/* return the model key */
	model_key_t get_model_name();

private:
	float TUFrame;
	int Frame; 
};