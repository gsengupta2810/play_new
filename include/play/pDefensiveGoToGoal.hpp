#ifndef PDEFENSIVEGOTOGOAL_HPP
#define PDEFENSIVEGOTOGOAL_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

namespace Strategy
{
  class PDefensiveGoToGoal : public Play
  {
  public:
    inline PDefensiveGoToGoal(const BeliefState& state) 
      : Play(state)
    {
      name = "DefensiveGoToGoal";

      assert(HomeTeam::SIZE == 5); // TestPlay is applicable for a team of 3 robots only

      PositionPlay = PLAYTYPE_NO;
      AttackPlay   = PLAYTYPE_YES;
      Tactic::Param param;
      roleList[0].push_back(std::make_pair(Tactic::Attack, param));
      
      roleList[1].push_back(std::make_pair(Tactic::GoalieOur, param));
      
      param.PositionP.x = -HALF_FIELD_MAXX/6;
      param.PositionP.y =  0;
      param.PositionP.finalSlope  = 0;
      roleList[2].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = HALF_FIELD_MAXX/4;
      param.PositionP.y = -HALF_FIELD_MAXY/2;
      param.PositionP.finalSlope  = 0;
      roleList[3].push_back(std::make_pair(Tactic::Position, param));
      
      param.PositionP.x = HALF_FIELD_MAXX/4;
      param.PositionP.y = HALF_FIELD_MAXY/2;
      param.PositionP.finalSlope  = 0;
      roleList[4].push_back(std::make_pair(Tactic::Position, param));
      
      computeMaxTacticTransits();
    }

    inline ~PDefensiveGoToGoal()
    { }

    inline bool applicable(void) const
    {
      if(!Play::applicable()) return false;
      return !state.pr_oppBall;
    }

    inline Result done(void) const
    {
      if(!state.pr_oppBall)
      {
        return NOT_TERMINATED;
      }
      // TODO improve the success condition. Detect Goal.
      return COMPLETED;
    }
  }; // class PTestPlay
} // namespace Strategy

#endif // PTEST_PLAY_HPP
