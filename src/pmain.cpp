#include <iostream>
#include <cstring>
#include <ctime>
#include "krssg_ssl_msgs/BeliefState.h"
#include "pExec.h"
#include <stdio.h>

#include "ros/ros.h"
#include <krssg_ssl_msgs/TacticPacket.h>
#include "tactics/tactic.h"
#include <tactics/tactic_factory.h>
#include <string>
#include <utility>
#include <fstream>

using namespace krssg_ssl_msgs;
using namespace Strategy;

ros::Subscriber state_sub;
krssg_ssl_msgs::BeliefState state;
std::vector<std::pair<std::string, Strategy::Tactic::Param> > roleList;

void publishing();

void Callback(const krssg_ssl_msgs::BeliefState::ConstPtr& msg)
{
    
  ROS_INFO("in Callback %f ",msg->ballPos.x);

  state.isteamyellow=msg->isteamyellow;
  state.frame_number=msg->frame_number ;
  state.t_capture=msg->t_capture  ;   
  state.t_sent=msg->t_sent   ;
  state.ballPos=msg->ballPos  ;     
  state.ballVel=msg->ballVel  ;
  state.awayPos=msg->awayPos ;
  state.homePos=msg->homePos;
  state.ballDetected=msg->ballDetected;
  state.homeDetected=msg->homeDetected;
  state.awayDetected=msg->awayDetected;
  if(1)
  publishing();
  return;
}

void publishing()
{
  ros::NodeHandle n;
  ros::Publisher tp0_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_0", 1000);
  ros::Publisher tp1_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_1", 1000);
  ros::Publisher tp2_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_2", 1000);
  ros::Publisher tp3_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_3", 1000);
  ros::Publisher tp4_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_4", 1000);
  ros::Publisher tp5_pub = n.advertise<krssg_ssl_msgs::TacticPacket>("tactic_5", 1000);

  //****************************************************************
  krssg_ssl_msgs::TacticPacket tp0, tp1,tp2,tp3,tp4,tp5;
  Robot** robot;
  //****************************************************************

   PExec pExec(&state,n); 
   ROS_INFO("play terminated %d ",pExec.playTerminated());
    if(pExec.playTerminated())
    {
       pExec.evaluatePlay();
       robot=pExec.selectPlay();
    }
      robot=pExec.executePlay();
  
  Tactic::Param tParam;

  tp0.tID = robot[0]->tID;
  //ROS_INFO("in Callback %s \n",tp0.tID);
  //tParam=roleList[0][currTacticIdx].second;
  //tp0.tParamJSON = TacticFactory::instance()->Create(roleList[0][currTacticIdx], 0)->paramToJSON(tParam); // bot id really doesnt matter here
  tp0.tParamJSON =robot[0]->tParamJSON;

  tp1.tID = std::string(robot[1]->tID);
  // //ROS_INFO("in Callback %c \n",tp1.tID);
  // //tParam=roleList[1][currTacticIdx].second;
  // //tp1.tParamJSON = TacticFactory::instance()->Create(roleList[1], 1)->paramToJSON(tParam); // bot id really doesnt matter here
  tp1.tParamJSON =robot[1]->tParamJSON;
  
  tp2.tID = std::string(robot[2]->tID);
  // //ROS_INFO("in Callback %c \n",tp2.tID);
  // //tParam=roleList[2][currTacticIdx].second;
  // //tp2.tParamJSON = TacticFactory::instance()->Create(roleList[2], 2)->paramToJSON(tParam); // bot id really doesnt matter here
  tp2.tParamJSON =robot[2]->tParamJSON;
  
  tp3.tID = std::string(robot[3]->tID);
  // //ROS_INFO("in Callback %c \n",tp3.tID);
  // //tParam=roleList[3][currTacticIdx].second;
  // //tp3.tParamJSON = TacticFactory::instance()->Create(roleList[3], 3)->paramToJSON(tParam); // bot id really doesnt matter here
  tp3.tParamJSON =robot[3]->tParamJSON;
  
  tp4.tID = std::string(robot[4]->tID);
  // //ROS_INFO("in Callback %c \n",tp4.tID);
  // //tParam=roleList[4][currTacticIdx].second;
  // //tp4.tParamJSON = TacticFactory::instance()->Create(roleList[4], 0)->paramToJSON(tParam); // bot id really doesnt matter here
  tp4.tParamJSON =robot[0]->tParamJSON;
  
  // tp5.tID = std::string(robot[5]->tID);
  // //ROS_INFO("in Callback %c \n",tp5.tID);
  // //tParam=roleList[0][currTacticIdx].second;
  // //tp5.tParamJSON = TacticFactory::instance()->Create(roleList[5], 0)->paramToJSON(tParam); // bot id really doesnt matter here
  //tp5.tParamJSON =robot[5]->tParamJSON;

  tp0_pub.publish(tp0);
  tp1_pub.publish(tp1);
  tp2_pub.publish(tp2);
  tp3_pub.publish(tp3);
  tp4_pub.publish(tp4);
  tp5_pub.publish(tp5);  
}

int main(int argc, char  *argv[])
{
  // send a dummy TacticPacket
  ros::init(argc, argv, "play_node");
  ros::NodeHandle n;
  state_sub = n.subscribe("/belief_state", 1000, Callback);
  ros::spin();
  return 0;
}