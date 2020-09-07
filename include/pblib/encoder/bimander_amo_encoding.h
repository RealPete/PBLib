#ifndef BIMANDER_AMO_ENCODING_H
#define BIMANDER_AMO_ENCODING_H

#include <pblib/SimplePBConstraint.h>
#include <pblib/IncSimplePBConstraint.h>
#include <pblib/PBConfig.h>
#include <pblib/clausedatabase.h>
#include <pblib/auxvarmanager.h>
#include <pblib/weightedlit.h>
#include <pblib/encoder/naive_amo_encoder.h>
#include <pblib/encoder/Encoder.h>

#include <vector>
#include <sstream>

class Bimander_amo_encoding :public Encoder
{
private:
    std::vector<Lit> _literals;
    std::vector<std::vector<Lit> > groups;
    std::vector<Lit> bits;
    int nBits;
    int two_pow_nbits;
    int k;
    int m;
    Naive_amo_encoder naive_amo_encoder;


    void encode_intern( std::vector<Lit>& literals, ClauseDatabase & formula, AuxVarManager & auxvars);    
public:
    void encode(const SimplePBConstraint& pbconstraint, ClauseDatabase & formula, AuxVarManager & auxvars);
    int64_t encodingValue(const SimplePBConstraint& pbconstraint);

    Bimander_amo_encoding(PBConfig & config);
    virtual ~Bimander_amo_encoding();
};

#endif // BINARY_AMO_H
