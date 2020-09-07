#ifndef AMO_H
#define AMO_H
#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>
#include <pblib/auxvarmanager.h>
#include <pblib/clausedatabase.h>
#include <pblib/encoder/Encoder.h>
#include <pblib/weightedlit.h>

#include <sstream>
#include <vector>

// nested amo encoding ...
class AMO_Encoder : public Encoder {
private:
  std::vector<Lit> _literals;

  void encodeEq(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
                AuxVarManager& auxvars);
  int64_t clauseCount(int32_t n);
  int64_t litCount = 0;

public:
  void encode_intern(std::vector<Lit>& literals, ClauseDatabase& formula,
                     AuxVarManager& auxvars);
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);

  virtual int64_t encodingValue(const SimplePBConstraint& pbconstraint);

  AMO_Encoder(PBConfig& config) : Encoder(config){};
  ~AMO_Encoder() = default;
};

#endif  // AMO_H
