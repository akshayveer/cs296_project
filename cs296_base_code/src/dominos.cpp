
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

    //! \brief arm2 body object for second arm of crane
    b2Body* arm2;

    //! \brief hand first part
    b2Body* h1;


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

      //! \brief second triangle

      vertices[0].Set(0,7+1.5);
      vertices[1].Set(1.2,7);
      vertices[2].Set(-1.2,7);
      shape.Set(vertices,3);
      arm1->CreateFixture(&shape,0.5);

    }
    
    //! \brief creating revolute joint between base body and first arm
    {
      r_jointDef.Initialize(base_body,arm1,b2Vec2(-40,-1+6.5*2+1.5));
      r_jointDef.enableLimit=0;
      r_jointDef.lowerAngle=-0.5*b2_pi;

      r_jointDef.enableMotor=1;
      r_jointDef.maxMotorTorque =100000.0f;
      r_jointDef.motorSpeed=0;
      r_joint[0] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
    }

    //! \brief creating second arm
    {
      //! \brief first triangle

      vertices[0].Set(0,0);
      vertices[1].Set(1.2,1.5);
      vertices[2].Set(-1.2,1.5);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(-40,-1+6.5*2+1.5+1.5+7*2+1.5);
      arm2=m_world->CreateBody(&dynamic_bd);
      arm2->CreateFixture(&shape,0.1);

      //! \brief creating rectangle

      shape.SetAsBox(14,1.2,b2Vec2(10,1.5+1.2),0);
      arm2->CreateFixture(&shape,0.2);

      //! \brief creating second triangle

      vertices[0].Set(10+14-1.2,0);
      vertices[1].Set(10+14,1.5);
      vertices[2].Set(10+14-1.2-1.2,1.5);
      shape.Set(vertices,3);
      arm2->CreateFixture(&shape,0.2);

    }

    //! \brief revolute joint between first arm and second arm
    {
      r_jointDef.Initialize(arm1,arm2,b2Vec2(-40,-1+6.5*2+1.5+1.5+7*2+1.5));
      r_jointDef.maxMotorTorque =10000.0f;
      r_jointDef.upperAngle=b2_pi/15;
      r_jointDef.lowerAngle=-b2_pi/15;
      r_joint[1] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
    }

    //! \brief first half of hand
    {
      //! \brief first part
      vertices[0].Set(0,0);
      vertices[1].Set(-0.5,0.5);
      vertices[2].Set(-0.5,-0.5);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(-40+10+14-1.2,-1+6.5*2+1.5+1.5+7*2+1.5);
      h1=m_world->CreateBody(&dynamic_bd);
      h1->CreateFixture(&shape,0.1);

      shape.SetAsBox(4,0.5,b2Vec2(-4-0.5,0),0);
      h1->CreateFixture(&shape,0.2);

      vertices[0].Set(-0.5-4*2+0.2+0.5,-0.5-0.5);
      vertices[1].Set(-0.5-4*2+0.2+0.5+0.5,-0.5);
      vertices[2].Set(-0.5-4*2+0.2,-0.5);
      shape.Set(vertices,3);
      h1->CreateFixture(&shape,0.1);


      //! \brief second part

      vertices[0].Set(0,0);
      vertices[1].Set(0.5,-0.5);
      vertices[2].Set(-0.5,-0.5);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(-40+10+14-1.2-0.5-4*2+0.5,-1+6.5*2+1.5+1.5+7*2+1.5-0.5-0.5);
      b2Body* b1=m_world->CreateBody(&dynamic_bd);
      b1->CreateFixture(&shape,0.1);

      shape.SetAsBox(0.5,3,b2Vec2(0,-0.5-3),0);
      b1->CreateFixture(&shape,0.2);

      vertices[0].Set(-0.5,-0.5-3*2+1);
      vertices[1].Set(-0.5,-0.5-3*2);
      vertices[2].Set(5,-0.5-3*2);
      shape.Set(vertices,3);
      b1->CreateFixture(&shape,0.10);

      //! \brief creating joint between arm2 and first hand
      r_jointDef.enableLimit=0;
      r_jointDef.Initialize(arm2,h1,b2Vec2(-40+10+14-1.2,-1+6.5*2+1.5+1.5+7*2+1.5));
      r_jointDef.upperAngle=(b2_pi/15);
      r_joint[2] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);

      //! \brief creating joint
      r_jointDef.Initialize(h1,b1,b2Vec2(-40+10+14-1.2-0.5-4*2+0.5,-1+6.5*2+1.5+1.5+7*2+1.5-0.5-0.5));
      r_jointDef.lowerAngle=(-b2_pi/15);
      r_joint[3] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);


    }

    //! \brief second half of hand

    {
      //! \brief first part
      vertices[0].Set(0,0);
      vertices[1].Set(0.5,0.5);
      vertices[2].Set(0.5,-0.5);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(-40+10+14-1.2,-1+6.5*2+1.5+1.5+7*2+1.5);
      h1=m_world->CreateBody(&dynamic_bd);
      h1->CreateFixture(&shape,0.1);

      shape.SetAsBox(4,0.5,b2Vec2(4+0.5,0),0);
      h1->CreateFixture(&shape,0.2);

      vertices[0].Set(0.5+4*2-0.2-0.5,-0.5-0.5);
      vertices[1].Set(0.5+4*2+-0.2,-0.5);
      vertices[2].Set(0.5+4*2-0.2-1,-0.5);
      shape.Set(vertices,3);
      h1->CreateFixture(&shape,0.1);


      //! \brief second part

      vertices[0].Set(0,0);
      vertices[1].Set(0.5,-0.5);
      vertices[2].Set(-0.5,-0.5);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(-40+10+14-1.2+0.5+2*4-0.2-0.5,-1+6.5*2+1.5+1.5+7*2+1.5-0.5-0.5);
      b2Body* b1=m_world->CreateBody(&dynamic_bd);
      b1->CreateFixture(&shape,0.1);

      shape.SetAsBox(0.5,3,b2Vec2(0,-0.5-3),0);
      b1->CreateFixture(&shape,0.2);

      vertices[0].Set(0.5,-0.5-3*2+1);
      vertices[1].Set(0.5,-0.5-3*2);
      vertices[2].Set(-5,-0.5-3*2);
      shape.Set(vertices,3);
      b1->CreateFixture(&shape,0.10);

      //! \brief creating joint between arm2 and first hand
      r_jointDef.Initialize(arm2,h1,b2Vec2(-40+10+14-1.2,-1+6.5*2+1.5+1.5+7*2+1.5));
      r_jointDef.lowerAngle=(-b2_pi/15);
      r_joint[4] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);

      //! \brief creating joint
      r_jointDef.Initialize(h1,b1,b2Vec2(-40+10+14-1.2+0.5+2*4-0.2-0.5,-1+6.5*2+1.5+1.5+7*2+1.5-0.5-0.5));
      r_jointDef.upperAngle=(b2_pi/15);
      r_joint[5] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
        
    }

    {
      shape.SetAsBox(2,2.0f);
      dynamic_bd.position.Set(-10.0f,1.0f);
      b2Body* ground=m_world->CreateBody(&dynamic_bd); 
      ground->CreateFixture(&shape, 0.0f);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
