#ifndef T2K_ActionInitialization_h
#define T2K_ActionInitialization_h

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class T2K_ActionInitialization : public G4VUserActionInitialization
{
  public:
    T2K_ActionInitialization();
    virtual ~T2K_ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

#endif


