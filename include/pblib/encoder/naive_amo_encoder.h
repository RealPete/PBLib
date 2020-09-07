/*
 *
 */

#ifndef NAIVE_AMO_ENCODER_H
#define NAIVE_AMO_ENCODER_H

#include <pblib/SimplePBConstraint.h>
#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/clausedatabase.h>
#include <pblib/auxvarmanager.h>
#include <pblib/weightedlit.h>
#include <pblib/encoder/Encoder.h>

#include <vector>
#include <sstream>

class Naive_amo_encoder : public Encoder
{
private:
    std::vector<Lit> _literals;

public:
    void encode_intern( std::vector<Lit>& literals, ClauseDatabase & formula);
    void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase& formula, AuxVarManager& auxvars);
    int64_t encodingValue(const SimplePBConstraint& pbconstraint);

    Naive_amo_encoder(PBConfig & config);
    virtual ~Naive_amo_encoder();
};

#endif // COMMANDER_ENCODING_H
