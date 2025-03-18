Self-test coverage considerations - from IG 10.3.A resolution 11:
-	for deterministic ECDSA signature generation, the module shall have a deterministic ECDSA digital signature generation CAST. 
-	Note9: The signature verification self-test for signatures generated using deterministic ECDSA is met with an ECDSA signature verification CAST (specified below). 
-	Note10: the ECDSA signature generation and deterministic ECDSA signature generation methods shall each have their own self-test if both are implemented in the approved mode.
-	for algorithms whose output vary for a given set of inputs such as DSA, ECDSA, and RSA PSS, they shall be self-tested as a CAST for signature generation and verification (as supported by the module). For a KAT, this requires the randomization parameter be fixed. For a comparison test, this requires the randomization parameter be shared across all compared implementations. 
-	Note16: a CAST shall be performed at a minimum on any one approved modulus or curve size that is supported by the module. 
Note17: an ECDSA CAST shall be performed at a minimum, on any one of the implemented NIST-recommended curves (and for which the CAVP certificate includes the curve) in each of the implemented two types of fields (i.e., prime field where GF(p), and binary field where GF(2m)).
-	historically key generation does not have a CAST/KAT; however, key derivation is.
NIST CTG / CMVP are likely to expect a CAST of some type; a KAT is likely needed.
This is (speculatively) included in the MIS JSON as “ECC KPDF”.
-	If SHA-512 variations are supported, the SHA2-384 is not sufficient. See [IG 10.3.A Resolution 2](https://csrc.nist.gov/CSRC/media/Projects/cryptographic-module-validation-program/documents/fips 140-3/FIPS 140-3 IG.pdf#page=66).

![KAT SignatureGenerateVerify](../../Images/KatSignatureGenerateVerify.png)

The relevant excerpt from [140IG] 10.3.A, with bolding added to emphasize the purpose of the excerpt:

> The Encrypt CAST and Decrypt CAST do not need to be performed for each mode(s) that is selected to meet this cipher function requirement, as long the forward and inverse cipher functions (if implemented) are self-tested at least one time within any implemented mode(s). For example, if the module only implements AES GCM (Encrypt/Decrypt) and AES ECB (Encrypt/Decrypt), then the following CASTs would suffice: AES GCM Encrypt (to cover the forward cipher function), AES ECB Decrypt (to cover the inverse cipher function). CASTs on AES GCM Decrypt and AES ECB Encrypt would not be necessary. 
> 
> …
> 
> (a) A CAST for one of the following AES authenticated encryption modes is required if implemented: GCM, CCM …

Per the final sentence of [140IG] 10.3.A Additional Comments, key generation does not require a power-up self-test; a PCT is performed for each key generated. (However, the Caliptra module performs *key derivation*).

