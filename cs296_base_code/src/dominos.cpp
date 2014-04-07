
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

    

    //! \brief arm1 creating first arm of crane
    b2Body* arm1;

    //! \brief arm2 body object for second arm of crane
    b2Body* arm2;

   

    float x1,y1,l1,h1,h2,w1=5,w2=1;
    /*! \brief creating ground body */

    { 
      shape.SetAsBox(55.5f,2.0f);
      static_bd.position.Set(0.0f,-3);
      b2Body* ground=m_world->CreateBody(&static_bd); 
      ground->CreateFixture(&shape, 0.0f);
    }

    /*! \brief creating a base body for positioning first arm */

    {
      /*! \brief creating rectangle */
      l1=1.75;h1=6.5;x1=-40;y1=-1+h1;

      dynamic_bd.position.Set(x1,y1);
      shape.SetAsBox(l1,h1);
      base_body=m_world->CreateBody(&dynamic_bd);
      base_body->CreateFixture(&shape,1000.0);

      /*! \brief creating triangle */
      h2=1.5;
      vertices[0].Set(0,h1+h2);
      vertices[1].Set(l1,h1);
      vertices[2].Set(-l1,h1);
      shape.Set(vertices,3);
      base_body->CreateFixture(&shape,0.0);

    }

    /*! \brief creating first arm */

    {
      //! \brief rectangle part
      y1=y1+h1+h2+h2; h1=10; y1+=h1; l1=1.2; 

      dynamic_bd.position.Set(x1,y1);
      shape.SetAsBox(l1,h1);
      arm1=m_world->CreateBody(&dynamic_bd);
      arm1->CreateFixture(&shape,0.5);

      //! \brief triangle part

      vertices[0].Set(0,-h1-h2);
      vertices[1].Set(l1,-h1);
      vertices[2].Set(-l1,-h1);
      shape.Set(vertices,3);
      arm1->CreateFixture(&shape,0.5);

      //! \brief second triangle

      vertices[0].Set(0,h1+h2);
      vertices[1].Set(l1,h1);
      vertices[2].Set(-l1,h1);
      shape.Set(vertices,3);
      arm1->CreateFixture(&shape,0.5);

    }
    
    //! \brief creating revolute joint between base body and first arm
    {
      r_jointDef.Initialize(base_body,arm1,b2Vec2(x1,y1-h1-h2));
      r_jointDef.enableLimit=1;
      r_jointDef.lowerAngle=-b2_pi/2;

      r_jointDef.enableMotor=1;
      r_jointDef.maxMotorTorque =10000000.0f;
      r_jointDef.motorSpeed=0;
      r_joint[0] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
    }

    //! \brief creating second arm
    {
      //! \brief first triangle
      y1+=(h1+h2);

      vertices[0].Set(0,0);
      vertices[1].Set(l1,h2);
      vertices[2].Set(-l1,h2);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(x1,y1);
      arm2=m_world->CreateBody(&dynamic_bd);
      arm2->CreateFixture(&shape,0.1);

      //! \brief creating rectangle
      l1=17; h1=1.2; w1=3;

      shape.SetAsBox(l1,h1,b2Vec2(l1-w1,h2+h1),0);
      arm2->CreateFixture(&shape,0.2);

      //! \brief creating second triangle


      vertices[0].Set(l1-w1+l1-w2-h1,0);
      vertices[1].Set(l1-w1+l1-w2,h2);
      vertices[2].Set(l1-w1+l1-w2-h1-h1,h2);
      shape.Set(vertices,3);
      arm2->CreateFixture(&shape,0.2);

    }

    //! \brief revolute joint between first arm and second arm
    {
      r_jointDef.Initialize(arm1,arm2,b2Vec2(x1,y1));
      r_jointDef.maxMotorTorque =10000000.0f;
      r_jointDef.upperAngle=b2_pi/2;
      r_jointDef.lowerAngle=-b2_pi/4;
      r_joint[1] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
    }

    //! \brief first half of hand
    {
      //! \brief first part
      x1+=(l1-w1+l1-w2-h1); h2=0.5;

      vertices[0].Set(0,0);
      vertices[1].Set(-h2,h2);
      vertices[2].Set(-h2,-h2);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(x1,y1);
      b2Body* b1=m_world->CreateBody(&dynamic_bd);
      b1->CreateFixture(&shape,0.1);

      l1=3;h1=0.5;

      shape.SetAsBox(l1,h1,b2Vec2(-l1-h1,0),0);
      b1->CreateFixture(&shape,0.2);

      w2=0.2;

     vertices[0].Set(-h2-l1-l1+w2+h2,-h1-h2);
      vertices[1].Set(-h2-l1-l1+w2+h2+h2,-h1);
      vertices[2].Set(-h2-l1-l1+w2,-h1);
      shape.Set(vertices,3);
      b1->CreateFixture(&shape,0.1);


      //! \brief second part

      vertices[0].Set(0,0);
      vertices[1].Set(h2,-h2);
      vertices[2].Set(-h2,-h2);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(x1+-h2-l1-l1+w2+h2,y1-h1-h2);
      b2Body* b2=m_world->CreateBody(&dynamic_bd);
      b2->CreateFixture(&shape,0.1);

      //! \brief creating joint between first part and second part
      r_jointDef.enableLimit=0;
      r_jointDef.Initialize(b1,b2,b2Vec2(x1+-h2-l1-l1+w2+h2,y1-h1-h2));
      r_jointDef.lowerAngle=(-b2_pi/8);
      r_jointDef.upperAngle=0;
      r_joint[3] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);

      l1=0.5; h1=3;
      shape.SetAsBox(l1,h1,b2Vec2(0,-h2-h1),0);
      b2->CreateFixture(&shape,0.2);

      w2=1; w1=5;
      vertices[0].Set(-h2,-h2-h1-h1+w2);
      vertices[1].Set(-h2,-h2-h1-h1);
      vertices[2].Set(w1,-h2-h1-h1);
      shape.Set(vertices,3);
      b2->CreateFixture(&shape,0.10);

      //! \brief creating joint between arm2 and first hand
      r_jointDef.Initialize(arm2,b1,b2Vec2(x1,y1));
      r_jointDef.upperAngle=(b2_pi/15);
      r_joint[2] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
      
      
    }

    //! \brief second half of hand

    {
      //! \brief first part
      vertices[0].Set(0,0);
      vertices[1].Set(h2,h2);
      vertices[2].Set(h2,-h2);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(x1,y1);
      b2Body* b1=m_world->CreateBody(&dynamic_bd);
      b1->CreateFixture(&shape,0.1);

      l1=3;h1=0.5;

      shape.SetAsBox(l1,h1,b2Vec2(l1+h2,0),0);
      b1->CreateFixture(&shape,0.2);

      w2=0.2;
      vertices[0].Set(h2+l1+l1-w2-h2,-h1-h2);
      vertices[1].Set(h2+l1+l1-w2,-h1);
      vertices[2].Set(h2+l1+l1-w2-h2-h2,-h1);
      shape.Set(vertices,3);
      b1->CreateFixture(&shape,0.1);


      //! \brief second part

      vertices[0].Set(0,0);
      vertices[1].Set(h2,-h1);
      vertices[2].Set(-h1,-h1);
      shape.Set(vertices,3);
      dynamic_bd.position.Set(x1+h2+l1+l1-w2-h2,y1-h1-h2);
      b2Body* b2=m_world->CreateBody(&dynamic_bd);
      b2->CreateFixture(&shape,0.1);

      //! \brief creating joint
      r_jointDef.Initialize(b1,b2,b2Vec2(x1+h2+l1+l1-w2-h2,y1-h1-h2));
      r_jointDef.upperAngle=(b2_pi/8);
      r_jointDef.lowerAngle=0;
      r_joint[5] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);

      l1=0.5; h1=3;
      shape.SetAsBox(l1,h1,b2Vec2(0,-h2-h1),0);
      b2->CreateFixture(&shape,0.2);

      w2=1; w1=5;

      vertices[0].Set(h2,-h2-h1-h1+w2);
      vertices[1].Set(h2,-h2-h1-h1);
      vertices[2].Set(-w1,-h2-h1-h1);
      shape.Set(vertices,3);
      b2->CreateFixture(&shape,0.10);

      //! \brief creating joint between arm2 and first hand
      r_jointDef.Initialize(arm2,b1,b2Vec2(x1,y1));
      r_jointDef.lowerAngle=(-b2_pi/15);
      r_joint[4] = (b2RevoluteJoint*)m_world->CreateJoint(&r_jointDef);
        
    }

  /*  {
      shape.SetAsBox(2,2.0f);
      dynamic_bd.position.Set(-10.0f,1.0f);
      b2Body* ground=m_world->CreateBody(&dynamic_bd); 
      b2FixtureDef wedgefd;
      wedgefd.shape = &shape;
      wedgefd.density = 0.5f;
      wedgefd.friction = 1.0f;
      wedgefd.restitution = 0.0f;
      ground->CreateFixture(&wedgefd);
    }*/

    {
        b2CircleShape c1,c2,c3;
        c1.m_radius = 0.1;
        c2.m_radius = 2;
        static_bd.position.Set(6,10);
        dynamic_bd.position.Set(6,10);
        b2Body* b2=m_world->CreateBody(&dynamic_bd);
        b2->CreateFixture(&c2,0.5);
        b2Body* b1=m_world->CreateBody(&static_bd);
        b1->CreateFixture(&c1,0.0f);
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(b1,b2,b2Vec2(6,10));
        jointDef.enableMotor=true;
        jointDef.maxMotorTorque =10000.0f;
        jointDef.motorSpeed=-3.0f;
        m_world->CreateJoint(&jointDef);
    }

    {
        b2CircleShape c1,c2;
        c1.m_radius = 0.1;
        c2.m_radius = 2;
        static_bd.position.Set(22,10);
        dynamic_bd.position.Set(22,10);
        b2Body* b2=m_world->CreateBody(&dynamic_bd);
        b2->CreateFixture(&c2,0.5);
        b2Body* b1=m_world->CreateBody(&static_bd);
        b1->CreateFixture(&c1,0.0f);
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(b1,b2,b2Vec2(22,10));
        jointDef.enableMotor=true;
        jointDef.maxMotorTorque =10000.0f;
        jointDef.motorSpeed=-3.0f;
        m_world->CreateJoint(&jointDef);
    }

    {
      int up_pieces = 19, down_pieces = 18, left_pieces = 2, right_pieces = 2;
      int up_x = 6-0.1, up_y = 10+2;
      int down_x = 6-0.1, down_y = 10-2;
      float32 x = 0.5, y = 0.1;

      b2PolygonShape shape_h;
      shape_h.SetAsBox(x, y);

      b2PolygonShape shape_v;
      shape_v.SetAsBox(y, x);

      b2FixtureDef fd_h;
      fd_h.filter.groupIndex = -8;
      fd_h.shape = &shape_h;
      fd_h.density = 50.0f;
      fd_h.friction = 1.0f;
      fd_h.restitution = 0.0f;

      b2FixtureDef fd_v;
      fd_v.filter.groupIndex = -8;
      fd_v.shape = &shape_v;
      fd_v.density = 50.0f;
      fd_v.friction = 1.0f;
      fd_v.restitution = 0.0f;

      b2RevoluteJointDef jointDef;
      jointDef.localAnchorA.Set(-x,0);
      jointDef.localAnchorB.Set(x,0);

      b2RevoluteJointDef jointDef1;
      jointDef1.localAnchorA.Set(0,-x);
      jointDef1.localAnchorB.Set(0,x);

      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(up_x, up_y);

      b2Body* body_up[up_pieces];
      body_up[0] = m_world->CreateBody(&bd);
      body_up[0]->CreateFixture(&fd_h);

      for(int i = 1; i<up_pieces; i++){
        bd.position.Set(up_x + 2 * x * i, up_y);
        body_up[i] = m_world->CreateBody(&bd);
        body_up[i]->CreateFixture(&fd_h);
        jointDef.bodyA = body_up[i];
        jointDef.bodyB = body_up[i-1];
        m_world->CreateJoint(&jointDef);
      }

      bd.position.Set(down_x, down_y);
      b2Body* body_down[down_pieces];
      body_down[0] = m_world->CreateBody(&bd);
      body_down[0]->CreateFixture(&fd_h);

      for(int i = 1; i<down_pieces; i++){
        bd.position.Set(down_x + 2 * x * i, down_y);
        body_down[i] = m_world->CreateBody(&bd);
        body_down[i]->CreateFixture(&fd_h);
        jointDef.bodyA = body_down[i];
        jointDef.bodyB = body_down[i-1];
        m_world->CreateJoint(&jointDef);
      }

      bd.position.Set(down_x, down_y);
      b2Body* body_left[left_pieces];
      body_left[0] = m_world->CreateBody(&bd);
      body_left[0]->CreateFixture(&fd_v);

      for(int i = 1; i<left_pieces; i++){
        bd.position.Set(down_x, down_y + 2 * x * i);
        body_left[i] = m_world->CreateBody(&bd);
        body_left[i]->CreateFixture(&fd_v);
        jointDef1.bodyA = body_left[i];
        jointDef1.bodyB = body_left[i-1];
        m_world->CreateJoint(&jointDef1);
      };

      bd.position.Set(down_x+down_pieces, down_y);
      b2Body* body_right[right_pieces];
      body_right[0] = m_world->CreateBody(&bd);
      body_right[0]->CreateFixture(&fd_v);

      for(int i = 1; i<right_pieces; i++){
        bd.position.Set(down_x+down_pieces, down_y + 2 * x * i);
        body_right[i] = m_world->CreateBody(&bd);
        body_right[i]->CreateFixture(&fd_v);
        jointDef1.bodyA = body_right[i];
        jointDef1.bodyB = body_right[i-1];
        m_world->CreateJoint(&jointDef1);
      };

      jointDef.localAnchorA.Set(-x,0);
      jointDef.localAnchorB.Set(0,x);
      jointDef.bodyA = body_up[0];
      jointDef.bodyB = body_left[left_pieces-1];
      m_world->CreateJoint(&jointDef);

      jointDef.localAnchorA.Set(-x,0);
      jointDef.localAnchorB.Set(0,-x);
      jointDef.bodyA = body_down[0];
      jointDef.bodyB = body_left[0];
      m_world->CreateJoint(&jointDef);

      jointDef.localAnchorA.Set(x,0);
      jointDef.localAnchorB.Set(0,x);
      jointDef.bodyA = body_up[up_pieces-1];
      jointDef.bodyB = body_right[right_pieces-1];
      m_world->CreateJoint(&jointDef);

      jointDef.localAnchorA.Set(x,0);
      jointDef.localAnchorB.Set(0,-x);
      jointDef.bodyA = body_down[down_pieces-1];
      jointDef.bodyB = body_right[0];
      m_world->CreateJoint(&jointDef);
  }
    

  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
