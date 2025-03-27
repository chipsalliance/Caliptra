[ECC Hardware Specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md#ecc)

The hardware implements both ECDSA and ECDH, supporting:
- Deterministic ECDSA with NIST-Secp384r1 ([RFC6979](https://www.rfc-editor.org/rfc/rfc6979.html), [FIPS 186-5](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-5.pdf)). Supported functions:
  - ECC key pair derivation. The hardware implementation is capable of supporting true key generation; however, the DICE DPE use case is deterministic and as such, this function is cormore aptly described for Caliptra as ECC key pair derivation.
  - Deterministic signature generation.
  - Signature verification.

- ECDH with NIST-Secp384r1 ([RFC6979](https://www.rfc-editor.org/rfc/rfc6979.html), [SP 800-56A](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-56Ar3.pdf)). Supported function:
  - Shared secret calculation.

ECDH is treated as "latent" functionality in V1.0, as thre is no corresponding [caliptra_api.h](https://github.com/chipsalliance/caliptra-sw/blob/main/libcaliptra/inc/caliptra_api.h) entry point defined.

CSTL reviewers may be aided in the understanding of the design by reviewing [ECC hardware design expressed in pseudocode](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md#pseudocode-3).

The ECC design does incorporate what the FIPS 140-3 process describes as Non-invasive Security, described in Caliptra-rtl documentation as [SCA countermeasure](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md#sca-countermeasure-4). This documentation includes [TVLA results](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md#tvla-results).


