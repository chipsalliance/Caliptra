
# Caliptra Trademark Auditing Process

This document will describe the specific requirements to be reviewed by a 3rd party and attest to Caliptra TAC that the requirements have been met.

List of Topics to review for Trademark Compliance

 * Each of these things will have to be reviewed for an integration to get approval of Trademark Usage

## Caliptra IP

* Show how the RTL was integrated into the device environment
* Show a Run of the tool to verify the RTL Release Hash (in development)
* Show the ROM hash from a release ROM hash
* Show the internal Caliptra FW signing process used to sign Caliptra FW
* Show what options were used to synthesize the RTL
* Show input wires to RTL
  * Clock
  * Reset
  * Power Good, Ready for fuses, Ready for FW, etc.
  * Show how the Generic input/output wires are addressed

## Caliptra Wrapper

* Show how the RTL key is provided and ensure that it is not available to any FW.
* Describe the noise source for the RNG (indicating if Internal RNG or external RNG)
* External RNG description should be shown
* Show error handling integration
* Show how debugging will be enabled and disable in production
* Show SRAM zeroization

## HSM Support

* Show how the FW signing key is created and protected
* If applicable, show LMS sign keys derivations and how HSM protects them
* If applicable, prove LMS verify.

## Fusing

* Show how the fuses are loaded into the Caliptra IP
* Show how to Security State is loaded
* Show the fuse recipe that is expected to fuse
  * Ensure the Public Key Hash is fused
  * Ensure that the security state is fuses.

## Manufacturing

* Indicate how the manufacturing process will flow.  
  * Show the UDS Seed creation
  * Show the CSR extraction and signing

## Cert Chain Verify

* Show that a part can have IDevID Signed Cert.
* Create a valid Caliptra cert chain with IDevID, LDevID, FMC Alias and R-TAlias cert.  Prove that the cert chain verifies.

## SOC Root of Trust

* Show that SOC RoT is sending SOC FMC measurements to Caliptra before running off-chip FW.
* Show the design for the SOC ROT Caliptra FW Storage and fetching
* Describe how Caliptra PA_USER management will be used.

## SOC Run-Time

* Show how SVNs fuses will be incremented.
* Show how keys revoke bits can be revoked.
* Show how Run-Time Entropy will be fused.
* Show how owner key hash will be fused.
* Show how the IDevID Cert gets recreated on part.
* Show how external entities would interact with Calitpra (path through Security processor, direct access, etc.)
