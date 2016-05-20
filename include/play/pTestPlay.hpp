#ifndef PTEST_PLAY_HPP
#define PTEST_PLAY_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"

namespace Strategy
{
  class PTestPlay : public Play
  {
  public:
    inline PTestPlay(const BeliefState& state) 
      : Play(state)
    {
      name = "TestPlay";

      assert(HomeTeam::SIZE == 5); // TestPlay is applicable for a team of 3 robots only

      Tactic::Param param;
      //param.SpinP.radPerSec = 1.0f;
      roleList[0].push_back(std::make_pair(Tactic::Stop, param));
      //param.SpinP.radPerSec = -1.0f;
      roleList[1].push_back(std::make_pair(Tactic::Stop, param));
      //param.SpinP.radPerSec = 5.0f;
      roleList[2].push_back(std::make_pair(Tactic::Stop, param));
      //param.SpinP.radPerSec = 1.0f;
      roleList[3].push_back(std::make_pair(Tactic::Stop, param));
      //param.SpinP.radPerSec = -1.0f;
      roleList[4].push_back(std::make_pair(Tactic::Stop, param));
      
      computeMaxTacticTransits();
    }

    inline ~PTestPlay()
    { }

    inline bool applicable(void) const
    {
      // TODO make it more sophisticated
      return true;
    }

    inline Result done(void) const
    {
      // TODO make it more sophisticated and also use the timeout info to determine if the play has terminated
      return NOT_TERMINATED;
    }
  }; // class PTestPlay
} // namespace Strategy

#endif // PTEST_PLAY_HPP
