#ifndef SATSOLVERCLAUSEDATABASE_H
#define SATSOLVERCLAUSEDATABASE_H

#include <pblib/clausedatabase.h>

#include "BasicSATSolver.h"

#include <vector>

class SATSolverClauseDatabase : public ClauseDatabase
{
protected:
  BasicSATSolver * satsolver;
  virtual void addClauseIntern(const std::vector< int32_t >& clause);

public:
    SATSolverClauseDatabase(PBConfig config, BasicSATSolver * satsolver);

};

#endif // SATSOLVERCLAUSEDATABASE_H