#ifndef POFFENSE_PLAY_HPP
#define POFFENSE_PLAY_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"
#include "fieldConfig.h"

namespace Strategy
{
  class POffensePlay : public Play
  {
    public: 
    inline POffensePlay(const BeliefState& state) : Play(state)
    {
      name = "OffensePlay";
      assert(HomeTeam::SIZE ==5);
      
      PositionPlay = PLAYTYPE_NO;
      AttackPlay   = PLAYTYPE_YES;
      Tactic::Param param;
      
      /* Role 1 - Goalie */
      roleList[0].push_back(std::make_pair(Tactic::GoalieOur,param));
      
      /* Role 2 - Striker */
      roleList[1].push_back(std::make_pair(Tactic::Attack,param));
      
      /* Role 3 - Midfield Player */
      roleList[2].push_back(std::make_pair(Tactic::Steal,param));
      
      /* Role 4 - Midfileld */
      param.DefendP.x = -HALF_FIELD_MAXX/4;
      roleList[3].push_back(std::make_pair(Tactic::Defend,param));
      
      /* Role 5 - Defender*/
      param.DefendP.x = -HALF_FIELD_MAXX/2;
      roleList[4].push_back(std::make_pair(Tactic::Defend,param));
      computeMaxTacticTransits();
    }
    
    inline ~POffensePlay()
    {
      
    }
    
    inline bool applicable(void) const
    {
      //if(HomeTeam::getScore() < AwayTeam::getScore())
        //return true;
      return true;
    }
    
    inline Result done(void) const
    {
      return NOT_TERMINATED;
    }
  };
}
#endif // POFFENSE_PLAY_HPP