/*
 *
 */

#ifndef BDD_SEQ_AMO_H
#define BDD_SEQ_AMO_H

#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>
#include <pblib/auxvarmanager.h>
#include <pblib/clausedatabase.h>
#include <pblib/encoder/Encoder.h>
#include <pblib/weightedlit.h>

#include <sstream>
#include <vector>

class BDD_Seq_Amo : public Encoder {
private:
  std::vector<Lit> _literals;
  std::vector<Lit> aux;

public:
  void encode_intern(std::vector<Lit>& literals, ClauseDatabase& formula,
                     AuxVarManager& auxvars);
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);
  int64_t encodingValue(const SimplePBConstraint& pbconstraint);

  BDD_Seq_Amo(PBConfig& config) : Encoder(config) {}
  virtual ~BDD_Seq_Amo() = default;
};

#endif  // BDD_SEQ_AMO_H
