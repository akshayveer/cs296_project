
/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  
  dominos_t::dominos_t()
  {
    body_index=1;

    /*! \brief definitions are copied when creating body objects 
               so we can use same  definitions to every object
    */

    /*! \brief static_bd used for static bodies.
        \brief dynamic_bd used for dynamic bodies.
        \brief shape used for creating rectangular shapes
        \brief circle circle shape
        \brief vertices for creating triangle shape 
    */

    b2BodyDef static_bd,dynamic_bd;
    dynamic_bd.type=b2_dynamicBody;
    b2RevoluteJointDef r_jointDef;

    b2PolygonShape shape;
    b2CircleShape circle;
    b2Vec2 vertices[3];

    /*! \brief base_body creating a base body for positioning first arm */
    b2Body* base_body;

    //! \brief arm1 creating first arm of crane
    b2Body* arm1;


    /*! \brief creating ground body */

    { 
      shape.SetAsBox(55.5f,2.0f);
      static_bd.position.Set(0.0f,-3.0f);
      b2Body* ground=m_world->CreateBody(&static_bd); 
      ground->CreateFixture(&shape, 0.0f);
    }

    /*! \brief creating a base body for positioning first arm */

    {
      /*! \brief creating rectangle */

      static_bd.position.Set(-40,-1+6.5);
      shape.SetAsBox(1.75,6.5);
      base_body=m_world->CreateBody(&static_bd);
      base_body->CreateFixture(&shape,0.0);

      /*! \brief creating triangle */

      vertices[0].Set(0,6.5+1.5);
      vertices[1].Set(1.75,6.5);
      vertices[2].Set(-1.75,6.5);
      shape.Set(vertices,3);
      base_body->CreateFixture(&shape,0.0);
    }

    /*! \brief creating first arm */

    {
      //! \brief rectangle part

      dynamic_bd.position.Set(-40,-1+6.5*2+1.5+7+1.5);
      shape.SetAsBox(1.2,7);
      arm1=m_world->CreateBody(&dynamic_bd);
      arm1->CreateFixture(&shape,0.5);

      //! \brief triangle part

      vertices[0].Set(0,-7-1.5);
      vertices[1].Set(1.2,-7);
      vertices[2].Set(-1.2,-7);
      shape.Set(vertices,3);
      arm1->CreateFixture(&shape,0.5);

    }
    
    //! \brief creating revolute joint between base body and first arm
    {
      r_jointDef.Initialize(base_body,arm1,b2Vec2(-40,-1+6.5*2+1.5));
      r_jointDef.enableLimit=1;
      r_jointDef.lowerAngle=-0.3*b2_pi;

      r_jointDef.enableMotor=1;
      r_jointDef.maxMotorTorque =10000.0f;
      r_jointDef.motorSpeed=0;
      r_joint1 = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
