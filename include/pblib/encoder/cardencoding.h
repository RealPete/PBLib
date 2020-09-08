#ifndef CARDENCODING_H
#define CARDENCODING_H

#include <pblib/IncSimplePBConstraint.h>
#include <pblib/IncrementalData.h>
#include <pblib/PBConfig.h>
#include <pblib/SimplePBConstraint.h>
#include <pblib/auxvarmanager.h>
#include <pblib/clausedatabase.h>
#include <pblib/encoder/Encoder.h>
#include <pblib/weightedlit.h>

// Cardinality Networks and their Applications (SAT 2009)
// Roberto As ́ın, Robert Nieuwenhuis, Albert Oliveras, Enric Rodr
// ́ıguez-Carbonell
class CardEncoding : public Encoder {
private:
  class CardIncData : public IncrementalData {
  private:
    std::vector<Lit> outlits;

  public:
    CardIncData(std::vector<Lit>& outlits) : outlits(outlits) {}
    virtual ~CardIncData() = default;
    virtual void encodeNewGeq(int64_t newGeq, ClauseDatabase& formula,
                              AuxVarManager& auxVars,
                              std::vector<int32_t> conditionals);
    virtual void encodeNewLeq(int64_t newLeq, ClauseDatabase& formula,
                              AuxVarManager& auxVars,
                              std::vector<int32_t> conditionals);
  };

public:
  void encode(const std::shared_ptr<IncSimplePBConstraint>& pbconstraint,
              ClauseDatabase& formula, AuxVarManager& auxvars);
  void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxvars);

  int64_t encodingValue(const SimplePBConstraint& pbconstraint);
  int64_t encodingValue(
      const std::shared_ptr<IncSimplePBConstraint>& pbconstraint);

  CardEncoding(PBConfig& config) : Encoder(config) {}
  virtual ~CardEncoding() = default;
};

#endif  // CARDENCODING_H
