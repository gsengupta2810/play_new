#ifndef PEXEC_H
#define PEXEC_H

#include "cs.hpp"
#include "naivePS.h"
#include "expPS.h"
#include "play.hpp"
#include "ps.h"
#include <tactics/tactic_factory.h>

// Forward Declarations
namespace Strategy
{
  class BeliefState;
  class Robot;
}

namespace Strategy
{

        //private PS_CLASS ----------- this was used by default
  class PExec : public NaivePS
                
  {
  private:
    Play::Result playResult;
    Robot*       robot[HomeTeam::SIZE];
    Tactic*    tacticCS[HomeTeam::SIZE];

  public:
    PExec(BeliefState& state);

    ~PExec();

  private:
    // Stores the index to the tactics in all role that is to be executed by the team
    unsigned int currTacticIdx;

    // Current tactic in execution by each bot
    std::pair<string, Tactic::Param> currTactic[HomeTeam::SIZE];

    void assignRoles(unsigned int*);

    bool canTransit(void);

    bool tryTransit(void);

  public:
    void selectPlay(void);

    Robot* executePlay(unsigned int*);

    void evaluatePlay(void);

    bool playTerminated(void);

    bool playCompleted(void);
  }; // class PExec
} // namespace Strategy

#endif // PEXEC_H