
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

    /*! \brief creating ground body */

    { 
      shape.SetAsBox(55.5f,2.0f);
      static_bd.position.Set(0.0f,-3.0f);
      b2Body* ground=m_world->CreateBody(&static_bd); 
      ground->CreateFixture(&shape, 0.0f);
    }

    /*! \brief creating a base body for positioning first arm */

    {
      /*! \brief creating circle */

      circle.m_radius=1.5;
      dynamic_bd.position.Set(-40,-1+1.75);
      b2Body* wheel=m_world->CreateBody(&dynamic_bd);
      wheel->CreateFixture(&circle,0.5);

      /*! \brief creating rectangle */

      dynamic_bd.position.Set(-40,-1+1.75+6.5);
      shape.SetAsBox(1.75,6.5);
      base_body=m_world->CreateBody(&dynamic_bd);
      base_body->CreateFixture(&shape,0.5);

      /*! \brief creating triangle */

      vertices[0].Set(0,6.5+1.75*0.8);
      vertices[1].Set(1.75,6.5);
      vertices[2].Set(-1.75,6.5);
      shape.Set(vertices,3);
      base_body->CreateFixture(&shape,0.5);

      /*! \brief creating revolute joint between circle and rectangle */

      //r_jointDef.Initialize(base_body,wheel,wheel->GetWorldCenter());
      r_jointDef.bodyA=base_body;
      r_jointDef.bodyB=wheel;
      r_jointDef.localAnchorA.Set(0,-6.5);
      r_jointDef.localAnchorB.Set(0,0);
      r_jointDef.enableMotor = true;
      r_jointDef.motorSpeed=2.0f;
      r_jointDef.maxMotorTorque =10.0f;
      m_world->CreateJoint(&r_jointDef);
    }
    
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
