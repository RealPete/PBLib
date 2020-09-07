#ifndef ENCODER_H
#define ENCODER_H

#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>

class Encoder {
protected:
  PBConfig config;
  int64_t valueFunction(int64_t number_of_clauses, int64_t numer_of_auxvars);

public:
  Encoder(PBConfig& config);

  void virtual encode(const SimplePBConstraint& pbconstraint,
                      ClauseDatabase& formula, AuxVarManager& auxvars) = 0;
  void virtual encode(
      const std::shared_ptr<IncSimplePBConstraint>& pbconstraint,
      ClauseDatabase& formula, AuxVarManager& auxvars);

  int64_t virtual encodingValue(const SimplePBConstraint& pbconstraint) = 0;
  int64_t virtual encodingValue(
      const std::shared_ptr<IncSimplePBConstraint>& pbconstraint);
};

#endif
