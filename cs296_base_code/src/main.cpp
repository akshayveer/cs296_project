/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

//! These are user defined include files
//! Included in double quotes - the path to find these has to be given at compile time
#include "render.hpp"
#include "cs296_base.hpp"
#include "callbacks.hpp"

//! GLUI is the library used for drawing the GUI
//! Learn more about GLUI by reading the GLUI documentation
//! Learn to use preprocessor diectives to make your code portable
#ifndef __APPLE__
#include "GL/glui.h"
#else
#include "GL/glui.h"
#endif

//! These are standard include files
//! These are usually available at standard system paths like /usr/include
//! Read about the use of include files in C++
#include <cstdio>
#include <sys/time.h>


//! Notice the use of extern. Why is it used here?
namespace cs296
{
  extern int32 test_index;
  extern int32 test_selection;
  extern int32 test_count;
  extern cs296::sim_t* entry;
  extern cs296::base_sim_t* test;
  extern cs296::settings_t settings;
  extern const int32 frame_period;
  extern float settings_hz;
  extern int32 width;
  extern int32 height;
  extern int32 main_window;
};

//! This opens up the cs296 namespace
//! What is the consequence of opening up a namespace?
using namespace cs296;


//! This function creates all the GLUI gui elements
/*
void create_glui_ui(void)
{
  GLUI *glui = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
  
  glui->add_statictext("Simulation Timesteps"); 
ls
  GLUI_Spinner* velocityIterationSpinner =
    glui->add_spinner("Velocity Iterations", GLUI_SPINNER_INT, &settings.velocity_iterations);
  velocityIterationSpinner->set_int_limits(1, 500);
  
  GLUI_Spinner* positionIterationSpinner =
    glui->add_spinner("Position Iterations", GLUI_SPINNER_INT, &settings.position_iterations);
  positionIterationSpinner->set_int_limits(0, 100);
  
  GLUI_Spinner* hertzSpinner =
    glui->add_spinner("Sim steps per frame", GLUI_SPINNER_FLOAT, &settings_hz);
  hertzSpinner->set_float_limits(5.0f, 200.0f);


  
  new GLUI_Column( glui, false );
  glui->add_statictext("Simulation Parameters"); 
  glui->add_checkbox("Warm Starting", &settings.enable_warm_starting);
  glui->add_checkbox("Time of Impact", &settings.enable_continuous);
  glui->add_checkbox("Sub-Stepping", &settings.enable_sub_stepping);


  
  new GLUI_Column( glui, false );
  glui->add_statictext("Display Options"); 
  GLUI_Panel* drawPanel =	glui->add_panel("Draw");
  glui->add_checkbox_to_panel(drawPanel, "Shapes", &settings.draw_shapes);
  glui->add_checkbox_to_panel(drawPanel, "Joints", &settings.draw_joints);
  glui->add_checkbox_to_panel(drawPanel, "AABBs", &settings.draw_AABBs);
  glui->add_checkbox_to_panel(drawPanel, "Statistics", &settings.draw_stats);
  glui->add_checkbox_to_panel(drawPanel, "Profile", &settings.draw_profile);
  
  new GLUI_Column( glui, false );
  glui->add_button("Pause", 0, callbacks_t::pause_cb);
  glui->add_button("Single Step", 0, callbacks_t::single_step_cb);
  glui->add_button("Restart", 0, callbacks_t::restart_cb);
  
  glui->add_button("Quit", 0,(GLUI_Update_CB)callbacks_t::exit_cb);
  glui->set_main_gfx_window( main_window );
}

*/

//! This is the main function
int main(int argc, char** argv)
{
  test_count = 1;
  test_index = 0;
  test_selection = test_index;
  
  int it=0;
  if(scanf("%d",&it) > 0);
  
  entry = sim;
  test = entry->create_fcn();
  float32 loop_time=0.0f,velocity_time=0.0f,step_time=0.0f,collision_time=0.0f,position_time=0.0f;
  
  struct timeval tp;
  gettimeofday(&tp,NULL);
  double start=tp.tv_sec*1000.0+tp.tv_usec/1000.0;
  for(int i=0;i<it;i++){
	for(int k=0;k<15;k++){
		test->change_to_selected_body(k%8);
		test->move_forward();
		test->move_backward();
		test->left();
		test->right();
		test->rotate_clock_wise();
		test->rotate_anti_clock_wise();
	}
	b2World* my_world = test->get_world();
    	my_world->Step(1/settings.hz,settings.velocity_iterations,settings.position_iterations);
    	const b2Profile& profile = my_world->GetProfile();
    	velocity_time += profile.solveVelocity;
    	collision_time += profile.collide;
    	position_time += profile.solvePosition;
    	step_time += profile.step;
  }
  gettimeofday(&tp,NULL);
  double end=tp.tv_sec*1000.0+tp.tv_usec/1000.0;
  loop_time=end-start;

  printf("Number of Iterations: %d\n",it);
  printf("Average time per step is %f ms\n",step_time/it);
  printf("Average time for collisions is %f ms\n",collision_time/it);
  printf("Average time for velocity updates is %f ms\n",velocity_time/it);
  printf("Average time for position updates is %f ms\n\n",position_time/it);
  printf("Total loop time is %f ms", loop_time);
  return 0;

  /*

  //! This initializes GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(width, height);

  char title[50];
  sprintf(title, "CS296 Base Code. Running on Box2D %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);
  main_window = glutCreateWindow(title);

  //! Here we setup all the callbacks we need
  //! Some are set via GLUI
  GLUI_Master.set_glutReshapeFunc(callbacks_t::resize_cb);  
  GLUI_Master.set_glutKeyboardFunc(callbacks_t::keyboard_cb);
  GLUI_Master.set_glutSpecialFunc(callbacks_t::keyboard_special_cb);
  GLUI_Master.set_glutMouseFunc(callbacks_t::mouse_cb);
  //! Others are set directly
  glutDisplayFunc(callbacks_t::display_cb);
  glutMotionFunc(callbacks_t::mouse_motion_cb);
  glutKeyboardUpFunc(callbacks_t::keyboard_up_cb); 
  glutTimerFunc(frame_period, callbacks_t::timer_cb, 0);

  //! We create the GLUI user interface
  create_glui_ui();

  //! Enter the infinite GLUT event loop
  glutMainLoop();

  */
  
  return 0;
}
