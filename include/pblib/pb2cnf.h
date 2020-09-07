#ifndef PB2CNF_H
#define PB2CNF_H

#include <pblib/PBConfig.h>
#include <pblib/PBSatSolver.h>
#include <pblib/VectorClauseDatabase.h>
#include <pblib/auxvarmanager.h>
#include <pblib/encoder/BDD_Seq_Amo.h>
#include <pblib/encoder/BinaryMerge.h>
#include <pblib/encoder/SWC.h>
#include <pblib/encoder/SortingNetworks.h>
#include <pblib/encoder/adderencoding.h>
#include <pblib/encoder/amo.h>
#include <pblib/encoder/bdd.h>
#include <pblib/encoder/bimander_amo_encoding.h>
#include <pblib/encoder/binary_amo.h>
#include <pblib/encoder/cardencoding.h>
#include <pblib/encoder/commander_encoding.h>
#include <pblib/encoder/k-product.h>
#include <pblib/encoder/naive_amo_encoder.h>
#include <pblib/helper.h>
#include <pblib/incpbconstraint.h>
#include <pblib/pbconstraint.h>
#include <pblib/preencoder.h>

#include <unordered_set>

class PB2CNF {
private:
  PBConfig basic_default_config = std::make_shared<PBConfigClass>();
  VectorClauseDatabase tmpFormula;
  std::vector<int32_t> tmpVariables;
  PreEncoder pre_encoder;
  PBConfig config;
  BDD_Encoder bdd_encoder;
  AdderEncoding adder_encoder;
  AMO_Encoder amo_encoder;
  Binary_AMO_Encoder binary_amo_encoder;
  k_Product k_product_encoer;
  commander_encoding commander_amo_encoding;
  Naive_amo_encoder naive_amo_encoder;
  Bimander_amo_encoding bimander_amo_encoding;
  BDD_Seq_Amo bdd_sec_amo;
  CardEncoding card_encoder;
  SortingNetworks sorting_networks;
  BinaryMerge binary_merge;
  SWC_Encoder swc_encoder;
  statistic* stats;
  bool private_stats;

  PB2CNF(const PB2CNF& other) = delete;
  virtual bool operator==(const PB2CNF& other) const = delete;

  bool encodeWithBestEncoder(std::vector<Encoder*> encoders,
                             SimplePBConstraint& constraint,
                             ClauseDatabase& formula, AuxVarManager& auxVars);
  bool encodeWithBestEncoder(std::vector<Encoder*> encoders,
                             std::shared_ptr<IncSimplePBConstraint> constraint,
                             ClauseDatabase& formula, AuxVarManager& auxVars);

  void encode_inc_with_adder(std::shared_ptr<IncSimplePBConstraint> constraint,
                             ClauseDatabase& formula, AuxVarManager& auxVars);
  void encode_inc_with_card(std::shared_ptr<IncSimplePBConstraint> constraint,
                            ClauseDatabase& formula, AuxVarManager& auxVars);
  void encode_inc_with_swc(std::shared_ptr<IncSimplePBConstraint> constraint,
                           ClauseDatabase& formula, AuxVarManager& auxVars);
  void encode_inc_amk(std::shared_ptr<IncSimplePBConstraint> constraint,
                      IncPBConstraint& incPbconstraint, ClauseDatabase& formula,
                      AuxVarManager& auxVars);
  void encode_inc_pb(std::shared_ptr<IncSimplePBConstraint> constraint,
                     IncPBConstraint& incPbconstraint, ClauseDatabase& formula,
                     AuxVarManager& auxVars);

  void encode_with_adder(SimplePBConstraint& constraint,
                         ClauseDatabase& formula, AuxVarManager& auxVars);
  void encode_with_card(SimplePBConstraint& constraint, ClauseDatabase& formula,
                        AuxVarManager& auxVars);
  void encode_with_bdd(SimplePBConstraint& constraint, ClauseDatabase& formula,
                       AuxVarManager& auxVars);
  void encode_with_swc(SimplePBConstraint& constraint, ClauseDatabase& formula,
                       AuxVarManager& auxVars);
  void encode_with_binary_merge(SimplePBConstraint& constraint,
                                ClauseDatabase& formula,
                                AuxVarManager& auxVars);
  void encode_amo(SimplePBConstraint& constraint, ClauseDatabase& formula,
                  AuxVarManager& auxVars);
  void encode_amk(SimplePBConstraint& constraint, ClauseDatabase& formula,
                  AuxVarManager& auxVars);
  void encode_pb(SimplePBConstraint& constraint, ClauseDatabase& formula,
                 AuxVarManager& auxVars);

  bool try_to_encode_in_threshold(SimplePBConstraint& constraint,
                                  ClauseDatabase& formula,
                                  AuxVarManager& auxVars, int clause_threshold);

public:
  //     PB2CNF(PBConfig & config);
  PB2CNF(PBConfig& config, statistic* stats = 0);
  PB2CNF();
  virtual ~PB2CNF();

  int32_t encodeAtMostK(const std::vector<int32_t>& literals, int64_t k,
                        std::vector<std::vector<int32_t> >& formula,
                        int32_t firstAuxiliaryVariable);
  int32_t encodeAtLeastK(const std::vector<int32_t>& literals, int64_t k,
                         std::vector<std::vector<int32_t> >& formula,
                         int32_t firstAuxiliaryVariable);

  int32_t encodeLeq(const std::vector<int64_t>& weights,
                    const std::vector<int32_t>& literals, int64_t leq,
                    std::vector<std::vector<int32_t> >& formula,
                    int32_t firstAuxiliaryVariable);
  int32_t encodeGeq(const std::vector<int64_t>& weights,
                    const std::vector<int32_t>& literals, int64_t geq,
                    std::vector<std::vector<int32_t> >& formula,
                    int32_t firstAuxiliaryVariable);
  int32_t encodeBoth(const std::vector<int64_t>& weights,
                     const std::vector<int32_t>& literals, int64_t leq,
                     int64_t geq, std::vector<std::vector<int32_t> >& formula,
                     int32_t firstAuxiliaryVariable);
  void encode(PBLib::PBConstraint const& pbconstraint, PBSATSolver& satsolver,
              AuxVarManager& auxVars, int clause_threshold = 0);
  void encode(PBLib::PBConstraint const& pbconstraint, ClauseDatabase& formula,
              AuxVarManager& auxVars);
  void encodeIncInital(IncPBConstraint& incPbconstraint,
                       ClauseDatabase& formula, AuxVarManager& auxVars);
};

#endif  // PB2CNF_H
