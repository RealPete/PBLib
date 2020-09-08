#ifndef BINARY_AMO_H
#define BINARY_AMO_H
#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>
#include <pblib/auxvarmanager.h>
#include <pblib/clausedatabase.h>
#include <pblib/encoder/Encoder.h>
#include <pblib/weightedlit.h>

#include <sstream>
#include <vector>

// Frisch, A. M. and Peugniez, T. J. (2001) Solving non-Boolean satisfiability
// problems with stochastic local search, in Proc. of the Seventeenth Int. Joint
// Conf. on Artificial Intelligence, Seattle, Washington, pp. 282-288. enhanced
// binary encoding
class Binary_AMO_Encoder : public Encoder {
private:
  std::vector<Lit> _literals;
  std::vector<Lit> bits;
  int nBits;
  int two_pow_nbits;
  int k;

  void encode_intern(std::vector<Lit>& literals, ClauseDatabase& formula,
                     AuxVarManager& auxvars);

public:
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);
  int64_t encodingValue(const SimplePBConstraint& pbconstraint);

  Binary_AMO_Encoder(PBConfig& config) : Encoder(config) {}
  virtual ~Binary_AMO_Encoder() = default;
};

#endif  // BINARY_AMO_H
