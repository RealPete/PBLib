#ifndef K_PRODUCT_AMO_H
#define K_PRODUCT_AMO_H

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

// A New SAT Encoding of the At-Most-One Constraint
// Jingchao Chen 2010

class k_Product : public Encoder {
private:
  AMO_Encoder basic_amo_encoder;
  Naive_amo_encoder naive_amo_encoder;
  int minimum_lit_count;
  int k;
  std::vector<Lit> _literals;

  void encode_intern(std::vector<Lit>& literals, ClauseDatabase& formula,
                     AuxVarManager& auxvars);
  void encode_non_recursive(std::vector<Lit>& literals, ClauseDatabase& formula,
                            AuxVarManager& auxvars);

public:
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);
  int64_t encodingValue(const SimplePBConstraint& pbconstraint);

  k_Product(PBConfig& config);
  virtual ~k_Product() = default;
};

#endif  // K_PRODUCT_AMO_H
