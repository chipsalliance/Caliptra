<p style="text-align: center;">Caliptra: A Datacenter System on a Chip (SoC) Root of Trust (RoT)</p>

# Roadmap to 2.1

This document lays out our roadmap and items to get to Caliptra 2.1 Core and
Subsystem.

Original **Date: Mar 31st 2025**

Drop dead: earliest RTL integration in Sept 2025

## Complete 2.0 closing items

* Validation
* Subsystem on FPGA
* CDC
* RDC & Synthesis
* Lint recheck
* Caliptra 2.0 Subsystem Release: April’25

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
* KV
    * FPV for interfaces between KV and crypto engines
* VeeR DCLS
    * Validation pending
* LOCK
    * otp\_ctrl changes to support zeroization and in field programming
        * Confirm and implement changes required for fuse ratcheting
    * https://github.com/chipsalliance/caliptra-rtl/issues/808: SHAKE256 and SHA3-256
    * Add key vault slot with AES / HMAC / ECDH / ML-KEM Decaps data paths (Bharat proposal)
    * https://github.com/chipsalliance/caliptra-rtl/issues/688: Allow some KV slots' HMAC results to be fed to firmware
        * If not, find some way for the HPKE nonce to be xor'd with a counter and extracted to the AES engine
    * https://github.com/chipsalliance/caliptra-rtl/issues/848: allow HMAC operations where the message spans multiple blocks, some of which may be in KV (supports FIPS-compliant key combiners)


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
