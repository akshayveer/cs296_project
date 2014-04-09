/* 
* Base code for CS 296 Software Systems Lab 
* Department of Computer Science and Engineering, IIT Bombay
* Instructor: Parag Chaudhuri
*/

/*! \file dominos.hpp
\brief This contains all function declarations of dominos.cpp.
*/

#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_

namespace cs296
{

//! This is the class that sets up the Box2D simulation world
//! Here we add member functions to control various objects in simulation
//! Since dominos_t is derived class of  base_sim_t we need to override parent class member functions

/*!
\class dominos_t 
\brief This is used to define objects in simulation.
*/

class dominos_t : public base_sim_t
{
private:

//! \brief body_index for specifying body under consideration.
	int body_index;

//! \brief revolute joints in simulation
	b2RevoluteJoint* r_joint[6];

/*! \brief creating a base body for positioning first arm */
	b2Body* base_body;

public:

/*!    \fn dominos_t();
\brief constructor for this class
*/
dominos_t();

/*!    \fn static base_sim_t* create()
\brief This function creates all objects present in dominos.cpp file
\brief Used polymorphism in this function by returning pointer to dominos_t instead of  base_sim_t
*/

static base_sim_t* create()
{
	return new dominos_t;
}

/*!   \fn  void change_to_selected_body(int i)
\brief This function changes the body under consideration.
\param integer i : index of body
*/

 void change_to_selected_body(int i);

/*!   \fn  void rotate_clock_wise()
\brief This function rotates body in clock wise direction.
*/

 void rotate_clock_wise();

/*!    \fn  void rotate_anti_clock_wise()
\brief This function roatates body in anti clock wise direction.
*/

 void rotate_anti_clock_wise();

/*!    \fn  void stop()
\brief This function stops the rotation of body.
*/

 void stop();

/*!    \fn  void release()
\brief This function releases the object present inside the arm.
*/

 void release();

/*!    \fn  void hold()
\brief This function holds the object with the arm using first joints.
*/	

 void hold();

/*!    \fn  void grab()
\brief This function holds the object with the arm using second joints.
*/

 void grab();

/*!    \fn  void move_forward()
\brief This function moves both arms in Anti-clock wise directions
*/

 void move_forward();

/*!    \fn  void move_forward()
\brief This function moves both arms in Clock wise directions
*/

 void move_backward();

};
}

#endif
