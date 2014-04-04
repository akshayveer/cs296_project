/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */

#ifndef _DOMINOS_HPP_
#define _DOMINOS_HPP_

namespace cs296
{
  //! This is the class that sets up the Box2D simulation world
  //! here we add member functions to control various parts
  //! Used polymorphism by making base_sim_t to point to dominos_t
  //! We have base_sim_t pointer so need to add override patent class member functions in derived class

  class dominos_t : public base_sim_t
  {
  private:

    //! \brief body_index for considering specified body
    int body_index;

    //! \brief base body and arm1 joint 
    b2RevoluteJoint* r_joint1;

  public:
    

    dominos_t();
    
    static base_sim_t* create()
    {
      return new dominos_t;
    }

    //! \brief change action to specified body

    virtual void change_to_selected_body(int i){
      body_index=i; 
    }
    //! \brief rotate body in clock wise

    virtual void rotate_clock_wise(){
      if(body_index==1){
        r_joint1->SetMotorSpeed(-1);
      }
    }

    //! \brief roatate body in anti clock wise

    virtual void rotate_anti_clock_wise(){
      if(body_index==1){
        r_joint1->SetMotorSpeed(1);
      }
    }

    virtual void stop(){
      r_joint1->SetMotorSpeed(0);
    }

  };
}
  
#endif
