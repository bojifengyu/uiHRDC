/*-----------------------------------------------------------------------------
 *  N_Gamma.hpp - A encoder/decoder for naive Gamma
 *
 *  Coding-Style: google-styleguide
 *      https://code.google.com/p/google-styleguide/
 *
 *  Authors:
 *      Takeshi Yamamuro <linguin.m.s_at_gmail.com>
 *      Fabrizio Silvestri <fabrizio.silvestri_at_isti.cnr.it>
 *      Rossano Venturini <rossano.venturini_at_isti.cnr.it>
 *
 *  Copyright 2012 Integer Encoding Library <integerencoding_at_isti.cnr.it>
 *      http://integerencoding.ist.cnr.it/
 *-----------------------------------------------------------------------------
 */

#ifndef __N_GAMMA_HPP__
#define __N_GAMMA_HPP__

#include <misc/encoding_internals.hpp>

#include <compress/EncodingBase.hpp>
#include <io/BitsReader.hpp>
#include <io/BitsWriter.hpp>

namespace integer_encoding {
namespace internals {

class N_Gamma : public EncodingBase {
 public:
  N_Gamma() : EncodingBase(E_N_GAMMA) {}
  ~N_Gamma() throw() {}

  void encodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t *nvalue) const {
    BitsWriter wt(out, *nvalue);
    *nvalue = wt.gammaArray(in, len);
  }

  uint64_t require(uint64_t len) const {
    /* Gamma needs 64-bit for UINT32_MAX */
    return (64 * len) >> 5;
  }

  void decodeArray(const uint32_t *in,
                   uint64_t len,
                   uint32_t *out,
                   uint64_t nvalue) const {
    BitsReader rd(in, len);
    rd.ngammaArray(out, nvalue);
  }
}; /* N_Gamma */

} /* namespace: internals */
} /* namespace: integer_encoding */

#endif /* __N_GAMMA_HPP__ */
