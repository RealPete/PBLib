#ifndef COMMANDER_ENCODING_H
#define COMMANDER_ENCODING_H

#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>
#include <pblib/auxvarmanager.h>
#include <pblib/clausedatabase.h>
#include <pblib/encoder/Encoder.h>
#include <pblib/encoder/amo.h>
#include <pblib/encoder/naive_amo_encoder.h>
#include <pblib/weightedlit.h>

#include <sstream>
#include <vector>

// Efficient CNF Encoding for Selecting 1 from N Objects
// Klieber, Kwon 2007

class commander_encoding : public Encoder {
private:
  AMO_Encoder basic_amo_encoder;
  Naive_amo_encoder naive_amo_encoder;
  int k;
  std::vector<Lit> _literals;
  std::vector<Lit> next_literals;
  std::vector<Lit> current_literals;
  void encode_non_recursive(std::vector<Lit>& literals, ClauseDatabase& formula,
                            AuxVarManager& auxvars);
  void encode_intern(std::vector<Lit>& literals, ClauseDatabase& formula,
                     AuxVarManager& auxvars, bool isExactlyOne);

public:
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);
  int64_t encodingValue(const SimplePBConstraint& pbconstraint);

  commander_encoding(PBConfig& config);
  virtual ~commander_encoding() = default;
};

#endif  // COMMANDER_ENCODING_H
