/*
 *
 */

#ifndef NAIVE_AMO_ENCODER_H
#define NAIVE_AMO_ENCODER_H

#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>
#include <pblib/auxvarmanager.h>
#include <pblib/clausedatabase.h>
#include <pblib/encoder/Encoder.h>
#include <pblib/weightedlit.h>

#include <sstream>
#include <vector>

class Naive_amo_encoder : public Encoder {
private:
  std::vector<Lit> _literals;

public:
  void encode_intern(std::vector<Lit>& literals, ClauseDatabase& formula);
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);
  int64_t encodingValue(const SimplePBConstraint& pbconstraint);

  Naive_amo_encoder(PBConfig& config) : Encoder(config) {}

  virtual ~Naive_amo_encoder() = default;
};

#endif  // COMMANDER_ENCODING_H
