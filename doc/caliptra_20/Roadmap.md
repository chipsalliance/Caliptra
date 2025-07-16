<p style="text-align: center;">Caliptra: A Datacenter System on a Chip (SoC) Root of Trust (RoT)</p>

# Roadmap to 2.1

This document lays out our roadmap and items to get to Caliptra 2.1 Core and
Subsystem.

## Timeline

* Caliptra 2.1 SS
    * HW release: End of August, 2025
    * ROM release: TBD, expect 4-6 weeks after HW release
    * FMC release: TBD
    * RT FW release: TBD
    * FIPS Certificate availability: TBD
    * Audit Completion: TBD
    * Target: earliest RTL integration in Sept 2025

## HW Features:

* Adam's Bridge External Mu (Mostly verification)
    * FPV for
        * external /mu
        * ML-DSA streaming mode while maintaining support fixed mode
        * Updates as a result of RTL updates
            * point wise mult and inverse entities
            * entity and controller block updates
* ML-KEM
    * Specification and implementation
    * FPV
    * DV for external /mu
* Standalone SHAKE256 hardware
    * Ingest of OT SHAKE256
    * FPV to be scoped and implemented
* Add AES-GCM DMA
* AXI streaming boot support in I3C and integration
* VeeR DCLS
    * Integration and Validation pending
* OCP LOCK
    * Implementation per the published
      [specification](https://github.com/chipsalliance/Caliptra/blob/main/doc/ocp_lock/Specification_v0.8.5.pdf)
    * otp\_ctrl changes to support zeroization and in field programming
        * Confirm and implement changes required for fuse ratcheting
    * SHAKE256 and SHA3-256
        * https://github.com/chipsalliance/caliptra-rtl/issues/808
    * Add fuse register for passing obfuscated HEK seed from MCU to Caliptra Core. DOE deobfuscates the HEK seed into KV22
    * Allow AES and HMAC engines to write a key into KV23 that is released to the storage device's line-rate encryption engine.
        * https://github.com/chipsalliance/caliptra-rtl/issues/894
    * Add KV-AES data path rules
        * AES(key = \*, msg = KV, dest = \*) is disallowed
        * AES(key = KV16, op = ECB-Decrypt, dest != KV23) is disallowed
            * Where KV16 is populated by ROM and is not allowed to be copied between slots.

## Reviews, documentation, code health:

* ROM/RTL Security reviews
    * 3P SAFE reviews (Scope, timelines, who will drive)
* FIPS requirements fleshed out
* Documentation framework to have all high and low level specifications available in a single website
    * Generate static website from markdown.
    * Add IP level specifications, register definitions and programming guides
* DV and dashboard instrumentation
    * Implement tooling to simplify DV configuration with VCS and Verilator, allowing downstream consumers to run top and block level DV.
    * Identify DV agents to be developed in the open source to avoid having to require VIP support.  As a stop gap, provide VIP integration details to partners so that they can reproduce the DV coverage results.
    * Integrate DV coverage reports into Caliptra's block and top level.
* Time permitting software coverage
    * Line and function coverage dashboards, generated from software emulation traces.
