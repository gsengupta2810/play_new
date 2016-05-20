#ifndef PLAY_BOOK_H
#define PLAY_BOOK_H

// Forward Declarations
namespace Strategy
{
  class BeliefState;
  class Play;
}

namespace Strategy
{
  class PlayBook
  {
  public:
    enum PlayID
    {
      None,
      SetPosition,   
      MAX_PLAYS
    };

  protected:
    const BeliefState& state;
    Play*              playList[MAX_PLAYS];

  public:
    PlayBook(const BeliefState& state);
    
    ~PlayBook();

    void reload(void);
  }; // class PlayBook
} // namespace Strategy

#endif // PLAY_BOOK_H