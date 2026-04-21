**Caliptra Checklist and Evaluation Methodology**

**Version 1.0**

# Table of Contents
- [Introduction](#introduction)
- [Caliptra Documentation](#caliptra-documentation)
- [Checklist Summary](#checklist-summary)
- [Part I: Common Requirements](#part-i-common-requirements)
  - [Assets](#assets)
  - [Interfaces](#interfaces)
  - [SoC Root of Trust (RoT)](#soc-root-of-trust-rot)
  - [Specific Functionality](#specific-functionality)
  - [Secure Processes](#secure-processes)
- [Part II: Caliptra Core Trademark — Additional Requirements (Passive Mode)](#part-ii-caliptra-core-trademark--additional-requirements-passive-mode)
- [Part III: Caliptra Subsystem Trademark — Additional Requirements](#part-iii-caliptra-subsystem-trademark--additional-requirements)

# Introduction

The **Caliptra Checklist and Evaluation Methodology** document serves as a comprehensive guide for ensuring the secure and correct integration of the Caliptra intellectual property (IP) into a system-on-chip (SoC). Caliptra is a hardware root-of-trust (RoT) IP designed to provide foundational security services within a computing system. Proper integration of Caliptra is crucial to enabling these security services and maintaining the overall security posture of the final product.

This document outlines detailed requirements and evaluation methodologies across various domains, including asset management, interface implementations, and secure process adherence. The primary goals are to:

* **Ensure security compliance:** Provide clear and testable requirements that align with industry best practices and standards, such as those from NIST and FIPS.  
    
* **Facilitate evaluation:** Offer comprehensive evaluation methodologies that allow for consistent and thorough assessment of compliance with the checklist items.

* **Promote clarity and specificity:** Avoid vague language by specifying exact requirements, thereby making the checklist actionable and reducing ambiguity during the evaluation process.

* **Address critical security areas:** Focus on key areas that have significant impact on the security of Caliptra integration, such as cryptographic key management, secure boot processes, and access control mechanisms.

* **Enhance integration efficiency:** By providing a clear roadmap of requirements, the document aims to streamline the integration process and assist manufacturers in proactively addressing security considerations.

The checklist items have been developed through a thorough analysis of:

* **Caliptra specifications:** Reviewing the Caliptra IP documentation to extract relevant requirements and ensure alignment with the intended security features.  
    
* **Industry standards and best practices:** Incorporating guidelines from recognized standards to enhance the robustness of security mechanisms.

* **Feedback and collaboration:** Integrating input from various stakeholders, including security experts and industry professionals, to refine the checklist and address potential gaps.

* **Asset-based analysis:** Identifying critical assets within the Caliptra integration context and tailoring requirements to protect these assets effectively.

> **Document Structure:** This checklist is divided into three parts.
> Evaluators MUST apply **Part I (Common Requirements)** to all integrations,
> plus the part that corresponds to the elected trademark type:
> **Part II** for the *Caliptra Core Trademark (Passive Mode)*, or
> **Part III** for the *Caliptra Subsystem Trademark*.

By adhering to the checklist and employing the specified evaluation methodologies, manufacturers and evaluators can work collaboratively to ensure that the Caliptra integration meets stringent security requirements, thereby bolstering the trustworthiness of the final product.

### Key Words

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://www.rfc-editor.org/rfc/rfc2119).

# Caliptra Documentation

The Caliptra Specification is maintained within the [ChipsAlliance Caliptra repository](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md).  This is a live link. Each generation, the main specification will be updated and the older specifications will be maintained for reference for designs based on that specification.  For example, here is the specification for [Calitpra 1.X](https://github.com/chipsalliance/Caliptra/blob/main/doc/caliptra_1x/Caliptra.md).

The [HW specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md) and [HW integration specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraIntegrationSpecification.md) also have their own live links. For previous versions of the hardware specification, download the official release from [Releases](https://github.com/chipsalliance/caliptra-rtl/releases) and review the corresponding documentation in the `docs` folder.

This checklist is built from these specifications with the goal to help ensure that Caliptra is integrated correctly within a design. To demonstrate compliance with this checklist, vendors must provide necessary collateral to security auditors, which may include documentation such as: integrated RTL, synthesized netlist reports, GLS FEV reports, SoC boot diagrams, etc. Some integration requirements may not be verified through tool reports or through code analysis. For such requirements, integrators must provide documentation summarizing plans and procedures (for example, generation of an obfuscation key in compliance with NIST).

# Checklist Summary

The following is a consolidated list of all requirements to ensure comprehensive coverage:

1. **Assets**  
   * UDS Seed and Field Entropy  
   * Firmware Authentication Keys  
   * IDEVID Generation and Endorsement Flow  
   * Obfuscation Key  
   * Fuses Management  
2. **Interfaces**
   * Mailbox Interface Compliance    
   * Debug Interface Management  
   * Interface Wires Implementation  
3. **SoC Root of Trust (RoT)**  
   * Boot and Initialization Process Compliance  
   * Handling of Caliptra PA_USER Management  
   * Random Number Generator (RNG) Implementation    
4. **Specific Functionality**  
   * Caliptra Mode Selection and State Handling  
   * Error Handling Mechanisms  
   * Logging Functionality in SoC  
5. **Secure Processes**  
   * Development Process Integrity  
   * Production Process Security  
   * Flaw Remediation Process

# Part I: Common Requirements

The requirements in this section apply to **all** Caliptra integrations,
regardless of whether the integrator is pursuing the Caliptra Core Trademark
(Passive Mode) or the Caliptra Subsystem Trademark.

## Assets

### UDS Seed and Field Entropy

#### *Generation and Provisioning*

* **Checklist Item:**  
  * **Requirement:** The UDS seed MUST be statistically uniquely generated using a cryptographically secure random number generator (CSRNG) seeded by an entropy source compliant with [NIST Entropy Source Certification](https://csrc.nist.gov/projects/cryptographic-module-validation-program/entropy-validations) SP 800-90B.
  * **Evaluation Methodology:** Manufacturers MUST provide documentation demonstrating compliance with applicable standards for entropy and random number generation.   
* **Checklist Item:**  
  * **Requirement:** The confidentiality and integrity of the UDS seed MUST be protected during generation, storage, and provisioning. Access to this asset must be strictly controlled, and any temporary storage MUST be sanitized after use.  
  * **Evaluation Methodology:** Manufacturers MUST detail the security measures employed during the handling of the UDS seed, including access controls, secure storage practices, and sanitization procedures.  
* **Checklist Item:**  
  * **Requirement**: Field Entropy SHOULD be generated on die, and not be exposed outside the die.  
  * **Evaluation Methodology**: Manufacturers SHOULD detail the generation process for, and document exposure of field entropy.

#### *Access to Fuses*

* **Checklist Item:**  
  * **Requirement:** Access to the fuses containing the UDS seed and field entropy MUST be restricted exclusively to the mechanisms needed for loading these values into Caliptra's fuse registers. No other components or firmware may have read or write access, except for essential hardware functions like fuse sense and distribution logic.  
  * **Evaluation Methodology:** Manufacturers MUST provide architectural diagrams and RTL code excerpts demonstrating that only authorized hardware mechanisms can access these fuses.

### FW Authentication Keys

* **Checklist Item:**  
  * **Requirement:** Firmware authentication keys MUST be generated in accordance with [NIST SP 800-208](https://csrc.nist.gov/pubs/sp/800/208/final) and [FIPS 186-5](https://csrc.nist.gov/pubs/fips/186-5/final).
  * **Requirement:** Signature generation operations using the firmware authentication key MUST only be allowed by authorized entities.
  * **Requirement:** Firmware authentication keys MUST be stored in a manner that prevents disclosure of private key material. The manner of storage MUST only permit keys to be exported or copied to systems that enforce the same controls on usage and disclosure of the key.
  * **Requirement:** Signature generation operations using the firmware authentication key MUST be logged.
  * **Requirement:** Firmware authentication keys SHOULD be created and stored in a Hardware Security Module (HSM).
  * **Requirement:** Firmware authentication keys SHOULD require multi-party authentication to perform signing operations.
  * **Evaluation Methodology:** Manufacturers MUST describe their key management practices, including storage solutions, access controls, and procedures to prevent unauthorized usage.

### IDEVID Generation and Endorsement Flow

#### *CSR Handling*

* **Checklist Item:**  
  * **Requirement:** Handling and transmission of the IDevID and any other CSRs generated by Caliptra MUST ensure that only authentic endorsement requests are signed by the CA.  
  * **Evaluation Methodology:** Manufacturers MUST outline the mechanisms used to protect the CSR during transmission from Caliptra to the endorsement environment, including cryptographic protections and secure channels.

#### *Certificate Provisioning*

* **Checklist Item:**  
  * **Requirement:** The IDEVID certificates, including CA certificates, MUST adhere to specified formats and cryptographic standards (e.g. key sizes and algorithms as per NIST guidelines). Acceptable algorithms and key strengths MUST meet or exceed the security strength that the Caliptra IP produces. These requirements apply to the entire CA cert chain.
  * **Evaluation Methodology:** Manufacturers MUST demonstrate compliance with the required formats and standards by providing examples of the certificate chain that is created.

### Obfuscation Key

#### *Generation and Handling*

* **Checklist Item:**  
  * **Requirement:** The obfuscation key ([cptra_obf_key](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraIntegrationSpecification.md#interface)) MUST be generated using a method that ensures 256 bits of entropy, such as an [ESV](https://csrc.nist.rip/Projects/cryptographic-module-validation-program/entropy-validations/esv) certified entropy source or an on-die Physically Unclonable Function (PUF) that is compliant with industry standards. 
  * **Evaluation Methodology:** Manufacturers MUST provide documentation on the obfuscation key generation method, including entropy measurements and compliance with relevant standards if applicable.  
* **Checklist Item:**  
  * **Requirement:** The obfuscation key MUST NOT be accessible (readable or modifiable) to firmware or any on-chip non-Caliptra entities, including preventing oracle attacks. The obfuscation key MUST not be on any scannable path. 
  * **Evaluation Methodology:** Manufacturers MUST demonstrate, through architectural documentation and security analyses, that the obfuscation key is inaccessible to firmware and other unauthorized components.

### Fuses

#### *Access Control*

* **Checklist Item:**  
  * **Requirement:** Fuses containing Caliptra secrets MUST NOT be readable by any mutable code in the SoC. Access MUST be restricted to secure hardware mechanisms and essential hardware functions like fuse sense and distribution logic.
  * **Evaluation Methodology:** Manufacturers MUST provide hardware design documentation showing access controls on fuse read/write mechanisms, ensuring only authorized hardware components can access these fuses.

#### *JTAG and Debug Interfaces*

* **Checklist Item:**  
  * **Requirement:** When JTAG or other debug interfaces are enabled, they MUST NOT allow access to Caliptra's fuses or fuse shadow registers containing secrets. This applies to both pre and post SoC reset states.  
  * **Evaluation Methodology:** Manufacturers MUST explain how debug interfaces are managed to prevent unauthorized access to sensitive fuses, including any hardware or firmware controls in place.

#### *Integrity Maintenance*

* **Checklist Item:**  
  * **Requirement:** The integrity of each fuse SHOULD be maintained throughout the lifespan of the device to prevent degradation or tampering that could affect security.  
  * **Evaluation Methodology:** Manufacturers SHOULD describe the techniques used to ensure fuse integrity, such as redundancy, error correction codes (ECC), or other protective measures.

#### *In-Field Programmable Fuses*

* **Checklist Item:**  
  * **Requirement:** Authorization mechanisms SHOULD be implemented for in-field programmable fuses to prevent unauthorized updates that could lead to denial-of-service or other attacks.  
  * **Evaluation Methodology:** Manufacturers SHOULD document the authorization processes required to program fuses in the field, including cryptographic protections or authentication steps.

#### *Caliptra SVN (Security Version Number) Management*

* **Checklist Item:**  
  * **Requirement:** Before updating any Caliptra SVN fuses, the SoC SHOULD verify that the firmware integrity and authenticity have been validated, and that the new SVN is greater than the current one.  
  * **Evaluation Methodology:** Manufacturers SHOULD describe the SVN update process, including checks performed to prevent unauthorized or erroneous updates.

## Interfaces

### *Mailbox Interface Compliance*

* **Checklist Item:**  
  * **Requirement:** The SoC Manager SHOULD implement the mailbox interface according to the Caliptra specification, ensuring proper handling of commands and status registers. Using the Caliptra Libraries (RUST and C version) provided by the Caliptra WG release is recommended as a reference codebase.  
  * **Evaluation Methodology:** Manufacturers SHOULD provide evidence, such as interface specifications or test results, demonstrating compliance with the mailbox interface requirements.

### *Debug Interface Management*

* **Checklist Item:**  
  * **Requirement:** The debug interfaces, including JTAG, MUST be securely managed to prevent unauthorized access to Caliptra internals or sensitive data.  
  * **Evaluation Methodology:** Manufacturers MUST explain how debug interfaces are controlled, including secure enable/disable mechanisms, and how they prevent unauthorized access to Caliptra.

### *Hardware Implementation*

* **Checklist Item:**  
  * **Requirement:** Hardware implementation of Caliptra MUST adhere to the SoC Integration Requirements of the RTL release that was used. Refer to docs/CaliptraIntegrationSpecification.md (section "SoC integration requirements") from the official release that was consumed for integration, as listed in [Releases](https://github.com/chipsalliance/caliptra-rtl/releases). Integrators pursuing the **Caliptra Subsystem Trademark** must additionally consult the Caliptra Subsystem Integration Specification for Subsystem-specific integration requirements.
  * **Evaluation Methodology:** Manufacturers MUST show the hardware implementation complies to the integration requirements in the caliptra-rtl repo and, if pursuing the Caliptra Subsystem Trademark, also complies to the integration requirements in the caliptra-ss repo. Note: the scope of the RTL integration requirements are limited to the hardware and ROM instantiation and do not cover firmware capabilities.

## SoC Root of Trust (RoT)

### *Boot and Initialization Process*

* **Checklist Item:**
  * **Requirement:** SoC firmware that interacts with Caliptra as the privileged PA\_USER MUST be measured, and those measurements MUST be submitted to Caliptra. Other SoC firmware SHOULD be measured. Configuration data that modifies the security properties of firmware MUST also be measured. 
  * **Requirement:** Measurements of firmware and configuration MUST be submitted to Caliptra before execution of the firmware, or usage of the configuration data. Measurements MUST be submitted to Caliptra by the same entity that collected the measurement (e.g. SoC FMC cannot pass measurements to SoC FW for submission to the Caliptra mailbox).   
  * **Evaluation Methodology:** Manufacturers MUST provide a detailed description of how measurements are communicated to Caliptra.  

### *Caliptra PA_USER (1.X) or AXI_USER (2.X) Management*

* **Checklist Item:**  
  * **Requirement:** The management of Caliptra's PA_USER (for 1.X implementations) or AXI_USER (for 2.X implementations) MUST ensure isolation and protection of privileged operations, preventing unprivileged users from forging measurements or accessing privileged functions.
  * **Evaluation Methodology:** Manufacturers MUST document how the applicable USER values are mapped in hardware and the mechanisms in place to isolate privileged operations from unprivileged ones.

### *Random Number Generator (RNG) Implementation*

* **Checklist Item:**  
  * **Requirement:** If an RNG is included in the Caliptra Wrapper, it SHOULD be securely implemented, and its design SHOULD meet applicable cryptographic standards. The source of entropy (internal or external) SHOULD be specified.  
  * **Evaluation Methodology:** Manufacturers SHOULD demonstrate that the RNG, including entropy sources, is compliant with standards like [NIST SP 800-90A](https://csrc.nist.gov/pubs/sp/800/90/a/r1/final), [SP 800-90B](https://csrc.nist.gov/pubs/sp/800/90/b/final), [SP 800-90C](https://csrc.nist.gov/pubs/sp/800/90/c/4pd).

## Specific Functionality

### *Caliptra Life Cycle Selection and State Handling*

* **Checklist Item:**  
  * **Requirement:** Where SoC behavior necessary to meet other requirements in this document is conditioned on SoC lifecycle state, the SoC MUST ensure that its own lifecycle is in a state that meets the requirements here prior to transitioning Caliptra's operational mode from unprovisioned to manufacturing or production.  
  * **Evaluation Methodology:** Manufacturers MUST provide a state machine diagram or equivalent documentation showing how Caliptra's mode transitions are managed and synchronized with the SoC's states.

### *Error Handling*

* **Checklist Item:**  
  * **Requirement:** The SoC MUST correctly implement error handling and reporting mechanisms for interactions with Caliptra, especially for security-relevant events, without leaking sensitive information.  
  * **Evaluation Methodology:** Manufacturers MUST document the error handling procedures, including what information is reported, how errors are logged, and measures taken to prevent information leakage. Specific error codes and messages should be reviewed for appropriateness.

### *Log Functionality in SoC*

* **Checklist Item:**
  * **Requirement:** The SoC SHOULD implement logging functionality that allows the compounded measurements stored by Caliptra to be reconstructed.
  * **Evaluation Methodology:** Manufacturers SHOULD describe the logging mechanism, including how logs are structured and how they integrate with Caliptra's measurement processes.

## Secure Processes

### Development Process

#### *Testing and Verification*

* **Checklist Item:**  
  * **Requirement:** The product SHOULD undergo thorough testing and verification during development, focusing on both functional correctness and security aspects. This includes testing of specific features and security mechanisms.  
  * **Evaluation Methodology:** Manufacturers SHOULD present test plans, results, and security analyses covering critical functionalities such as:  
    * Field programmable entropy API  
    * Generation and endorsement of attestation messages  
    * CSR generation and handling  
    * DICE identity provisioning  
    * Attestation processes  
    * Debug state transitions  
    * SVN updates and enforcement  
    * Firmware updates (FMC and RT FW)

### Production Process

#### *Debugging Controls*

* **Checklist Item:**  
  * **Requirement:** The SoC MUST put Caliptra into a debug state when the SoC is operating in a mode that permits the usage of code/data which differs from the measurements submitted to Caliptra.
  * **Requirement:** The SoC MUST put Caliptra into a debug state any time test or debug logic allows read or write access to Caliptra logic or SRAM.
  * **Evaluation Methodology:** In Caliptra Core mode the debug state transition must be handled by the SoC manager, and in Caliptra Subsystem mode the SoC must follow the debug unlock procedure. Manufacturers MUST describe how debugging is enabled for the SoC and for Caliptra, including any fuse settings, access controls, and procedures to disable debugging interfaces.

#### *Flaw Remediation Process*

* **Checklist Item:**  
  * **Requirement:** There MUST be a defined process for handling reported vulnerabilities, including assessment, communication, and deployment of security updates or mitigations.  
  * **Evaluation Methodology:** Manufacturers MUST provide their flaw remediation policy. This policy must describe how vulnerabilities are received (e.g., bug bounty programs), evaluated, and prioritized, and how updates are securely delivered to devices in the field. Procedures for notifying stakeholders and compliance with relevant regulations should also be described.

---

# Part II: Caliptra Core Trademark — Additional Requirements (Passive Mode)

The requirements in this section apply **only** to integrations pursuing the
**Caliptra Core Trademark (Passive Mode)**. All requirements in Part I also
apply.

## RTL Configuration

### *Core Mode*

* **Checklist Item:**
  * **Requirement:** The macro `CALIPTRA_MODE_SUBSYSTEM` MUST NOT be defined in
    `config_defines.svh` or in any build process. Defining this macro activates
    Subsystem-mode behavior and is incompatible with a Caliptra Core Trademark integration.
  * **Evaluation Methodology:** Manufacturers MUST provide the `config_defines.svh`
    used in the integration and demonstrate that `CALIPTRA_MODE_SUBSYSTEM` is
    absent.

### *TRNG Configuration (Core)*

* **Checklist Item:**
  * **Requirement:** The internal TRNG (`CALIPTRA_INTERNAL_TRNG`) is optional in
    Core Trademark integrations. If the internal TRNG is not enabled, the SoC
    MUST provide a compliant external TRNG via the Caliptra TRNG HW API. If the
    internal TRNG is used, the TRNG self-test threshold registers
    (`CPTRA_iTRNG_ENTROPY_CONFIG0` and `CPTRA_iTRNG_ENTROPY_CONFIG1`) MUST NOT
    be left at 0, as a zero value disables entropy self-testing.
  * **Evaluation Methodology:** Manufacturers MUST document the TRNG configuration
    choice, provide evidence of the TRNG source (internal or external), and, if
    the internal TRNG is enabled, demonstrate that the self-test threshold
    registers are set to non-zero values.

## Interface Connectivity

### *DMA Assist Engine Isolation*

* **Checklist Item:**
  * **Requirement:** All AXI manager output interfaces of the Caliptra IP MUST
    be tied to logic 0 and MUST NOT be connected to the SoC AXI interconnect.
    The DMA assist block is inactive in Passive Mode and must not be wired to any
    SoC interconnect fabric.
  * **Evaluation Methodology:** Manufacturers MUST provide RTL or integration
    schematics demonstrating that all AXI manager signals from Caliptra are
    grounded and not routed to the SoC interconnect.

### *SHA Accelerator Access Restriction*

* **Checklist Item:**
  * **Requirement:** The SHA accelerator block MUST be inaccessible to SoC
    components when Caliptra Core is integrated in Passive mode, if integrating
    version 2.0 or later. In such designs, AXI streaming mode is disabled; the SHA
    accelerator is available only in Caliptra-internal mailbox mode. No SoC
    agent may access the SHA accelerator via any path.
  * **Evaluation Methodology:** Manufacturers MUST demonstrate through RTL
    review or architecture documentation that no SoC agent has a path to the
    SHA accelerator, and that AXI streaming mode is not enabled. The value
    driven for the strap `strap_ss_caliptra_dma_axi_user` is used as a
    gating condition for SHA accelerator access via AXI. There shall
    not be a path from any SoC AXI manager that drives this AXI_USER value
    to Caliptra Core's AXI subordinate interface. This requirement applies
    for Caliptra Core release versions 2.0.0 and later.

### *Subsystem Strap Isolation*

* **Checklist Item:**
  * **Requirement:** All `strap_ss_*` Subsystem-mode strap signals (except for
    strap_ss_caliptra_dma_axi_user) MUST be tied to logic 0.
    The signals `ss_debug_intent`, `cptra_obf_field_entropy_vld`,
    `cptra_obf_field_entropy`, `cptra_obf_uds_seed_vld`, and
    `cptra_obf_uds_seed` MUST be tied to 0.
    Integrators may need to drive a non-zero value on the strap
    `strap_ss_caliptra_dma_axi_user` to maintain compliance with
    [SHA Accelerator Access Restriction](#SHA-Accelerator-Access-Restriction).
  * **Evaluation Methodology:** Manufacturers MUST provide RTL evidence
    (e.g., tie-off assertions or integration top-level wiring) demonstrating
    that all listed strap signals are permanently grounded.

## Secure Processes

### Development Process

#### *Integrity of Hardware and ROM*

* **Checklist Item:**
  * **Requirement:** The Caliptra RTL MUST be from an official release or TAC approved modification. Changes to the RTL other than those documented in the Integrator RTL Modification Requirements MUST be published to GitHub to obtain approval for the modification. Refer to docs/CaliptraIntegrationSpecification.md (section "Integrator RTL Modification Requirements") from the official release that was consumed for integration, as listed in [Releases](https://github.com/chipsalliance/caliptra-rtl/releases).
  * **Evaluation Methodology:** Manufacturers MUST show all changes made to RTL files. Manufacturers MUST show that changes to files in the Integrator RTL modification list are limited to the scope described in those requirements, and MUST show TAC approval for other changes. The [audit tools](https://github.com/chipsalliance/caliptra-rtl/tree/main/tools) can be used to identify changes.
* **Checklist Item:**
  * **Requirement:** Netlists, layout, and other development collateral derived from the RTL MUST maintain the same behavior as the released RTL when Caliptra is in the [Production Non-Debug state](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md#caliptra-security-states).
  * **Evaluation Methodology:** Manufacturers MUST provide evidence that collateral derived from the released RTL has not had its behavior modified.
* **Checklist Item:**
  * **Requirement:** Cryptographic hash of the Caliptra ROM used in final hardware design MUST match reference hash of official Caliptra releases.
  * **Evaluation Methodology:** Manufacturers MUST demonstrate that the SHA384 hash of ROM matches that of the official release that is integrated.

---

# Part III: Caliptra Subsystem Trademark — Additional Requirements

The requirements in this section apply **only** to integrations pursuing the
**Caliptra Subsystem Trademark**. All requirements in Part I also apply.

## RTL Configuration — Subsystem Mode

### *Caliptra Subsystem Build Configuration*

* **Checklist Item:**
  * **Requirement:** The macro `CALIPTRA_MODE_SUBSYSTEM` MUST be defined in
    as part of the product build processes. The macro `CALIPTRA_INTERNAL_TRNG`
    MUST also be defined.
  * **Evaluation Methodology:** Manufacturers MUST provide materials from build
    system or final contents of `config_defines.svh` demonstrating that
    `CALIPTRA_MODE_SUBSYSTEM` and `CALIPTRA_INTERNAL_TRNG` are defined.

### *TRNG Configuration*

* **Checklist Item:**
  * **Requirement:** The internal TRNG is mandatory in Subsystem mode.
    `CALIPTRA_INTERNAL_TRNG` MUST be defined. The TRNG self-test threshold
    registers (`CPTRA_iTRNG_ENTROPY_CONFIG0` and `CPTRA_iTRNG_ENTROPY_CONFIG1`)
    MUST be set to non-zero values to enable entropy self-testing. All requirements
    defined in the Caliptra Core Integration Specification for implementing
    Internal TRNG must be followed.
  * **Evaluation Methodology:** Manufacturers MUST demonstrate that
    `CALIPTRA_INTERNAL_TRNG` is defined and that both TRNG self-test threshold
    registers are configured to non-zero values.

## Secure Processes

### *Integrity of Hardware and ROM*

* **Checklist Item:**
  * **Requirement:** The full Caliptra Subsystem RTL MUST be from an official release
    or TAC approved modification. Changes to the RTL other than those documented in
    the Integrator RTL Modification Requirements MUST be published to GitHub to obtain
    approval for the modification. This requirement applies to the top-level wrapper
    of Caliptra Subsystem and all underlying components as defined in the Caliptra
    Subsystem Hardware Specification. For Caliptra Core and I3C core, the integrated
    code must exactly match the design from the submodule pointer that is part of the
    released Subsystem design. Caliptra Core ROM must also be consumed as-is from a
    compatible official release. Refer to the Caliptra Subsystem Integration
    Specification (section [Integration Considerations](#integration-considerations)) from the
    official release that was consumed for integration, as listed in
    [Releases](https://github.com/chipsalliance/caliptra-ss/releases).
  * **Evaluation Methodology:** Manufacturers MUST show all changes made to Subsystem
    RTL files. Manufacturers MUST show that changes to files in the Integrator RTL
    modification list are limited to the scope described in those requirements, and
    MUST show TAC approval for other changes.

## Interface Connectivity

### *AXI DMA Engine Connectivity*

* **Checklist Item:**
  * **Requirement:** The AXI DMA assist engine MUST be connected to the SoC AXI
    interconnect. AXI AxUSER signals MUST pass through unmodified to all AXI
    subordinates.
  * **Evaluation Methodology:** Manufacturers MUST provide architecture
    documentation and RTL evidence showing that the DMA engine is wired to the
    SoC interconnect and that AxUSER signals are propagated without
    modification.

### *SHA Accelerator Access Restriction (Subsystem)*

* **Checklist Item:**
  * **Requirement:** The SHA accelerator MUST be accessible only via Caliptra’s
    AXI DMA block. No SoC agent may access the SHA accelerator directly. The
    SHA accelerator enforces this restriction via AXI AxUSER checking; the
    integrator MUST configure `strap_ss_caliptra_dma_axi_user` to correctly
    identify Caliptra’s DMA transactions.
  * **Evaluation Methodology:** Manufacturers MUST provide strap configuration
    documentation and demonstrate, via RTL or architecture review, that no
    direct SoC path to the SHA accelerator exists and that AxUSER checking is
    correctly configured.

### *Subsystem Straps Configuration*

* **Checklist Item:**
  * **Requirement:** All `strap_ss_*` Subsystem-mode strap signals MUST be
    properly configured per the Caliptra Subsystem Integration Specification.
  * **Evaluation Methodology:** Manufacturers MUST provide strap configuration
    documentation showing specification-compliant values for all
    `strap_ss_*` signals.

## OCP Streaming Boot

* **Checklist Item:**
  * **Requirement:** OCP streaming boot via the I3C interface MUST be implemented
    in compliance with the OCP Recovery specification.
  * **Evaluation Methodology:** Manufacturers MUST provide documentation or test
    evidence demonstrating compliance with the OCP Recovery specification for
    the I3C streaming boot path.

## Production Debug Unlock

* **Checklist Item:**
  * **Requirement:** The Production Debug Unlock Architecture MUST be used.
    The simple JTAG security-state mechanism used in Passive Mode (Core
    Trademark) is not applicable to Subsystem integrations. Any SoC DFT
    or TAP access must be initiated through the Caliptra Subsystem Debug
    Unlock procedure.
  * **Evaluation Methodology:** Manufacturers MUST document the debug unlock
    mechanism implemented and demonstrate that it conforms to the Production
    Debug Unlock Architecture defined in the Caliptra Subsystem Integration
    Specification.

## Subsystem Fuse Map (TODO update this verbiage)

* **Checklist Item:**
  * **Requirement:** The integrator MUST implement the Caliptra Subsystem fuse
    map including all fuses defined in the Caliptra Core fuse map and (... FIXME ...).
    Refer to the fuse map section of the Caliptra Subsystem
    Integration Specification.
  * **Evaluation Methodology:** Manufacturers MUST provide fuse map
    documentation demonstrating that both the Caliptra Core fuse map and the
    Subsystem-specific fuse map are fully implemented.
