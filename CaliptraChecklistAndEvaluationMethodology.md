**Caliptra Checklist and Evaluation Methodology**

**Version 0.2**

# Table of Contents
- [Introduction](#introduction)
- [Caliptra Documentation](#caliptra-documentation)
- [Checklist Summary](#checklist-summary)
- [Checklist Areas](#checklist-areas)
  - [Assets](#assets)
  - [Interfaces](#interfaces)
  - [SoC Root of Trust (RoT)](#soc-root-of-trust-rot)
  - [Specific Functionality](#specific-functionality)
  - [Secure Process](#secure-processes)

# Introduction

The **Caliptra Checklist and Evaluation Methodology** document serves as a comprehensive guide for ensuring the secure and correct integration of the Caliptra intellectual property (IP) into a system-on-chip (SoC). Caliptra is a hardware root-of-trust (RoT) IP designed to provide foundational security services within a computing system. Proper integration of Caliptra is crucial to maintaining the overall security posture of the final product.

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

By adhering to the checklist and employing the specified evaluation methodologies, manufacturers and evaluators can work collaboratively to ensure that the Caliptra integration meets stringent security requirements, thereby bolstering the trustworthiness of the final product.

# Caliptra Documentation

The Caliptra Specification is maintained within the [ChipsAlliance Caliptra repository](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md).  This is a live link. Each generation, the main specification will be updated and the older specifications will be maintained for reference for designs based on that specification.  For example, here is the specification for [Calitpra 1.X](https://github.com/chipsalliance/Caliptra/blob/main/doc/caliptra_1x/Caliptra.md).

The [HW specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md) and [HW integration specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraIntegrationSpecification.md) also have their own live links. For previous versions of the hardware specification, go to the location that is tagged with that release version.

This checklist is built from these specifications with the goal to help ensure that Caliptra is integrated correctly within a design.

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
   * Secure Handling of Mailbox Access  
   * Debug Interface Management  
   * Interface Wires Implementation  
3. **SoC Root of Trust (RoT)**  
   * Boot and Initialization Process Compliance  
   * Handling of Caliptra PA\_USER Management  
   * Random Number Generator (RNG) Implementation  
   * SRAM Zeroization Process  
   * Key Revocation Bits Verification  
   * External Entity Interaction with Caliptra  
4. **Specific Functionality**  
   * Caliptra Mode Selection and State Handling  
   * Error Handling Mechanisms  
   * Logging Functionality in SoC  
5. **Secure Processes**  
   * Development Process Integrity  
   * Production Process Security  
   * Flaw Remediation Process

# Checklist Areas

## Assets

### UDS Seed and Field Entropy

#### *Generation and Provisioning*

* **Checklist Item:**  
  * **Requirement:** The UDS seed and field entropy MUST be generated using a cryptographically secure random number generator (CSRNG) compliant with [NIST Entropy Source Certification](https://csrc.nist.gov/projects/cryptographic-module-validation-program/entropy-validations) SP 800-90B.  
  * **Evaluation Methodology:** Manufacturers MUST provide documentation demonstrating compliance with applicable standards for entropy generation.   
* **Checklist Item:**  
  * **Requirement:** The confidentiality and integrity of the UDS seed MUST be protected during generation, storage, and provisioning. Access to this asset must be strictly controlled, and any temporary storage MUST be sanitized after use.  
  * **Evaluation Methodology:** Manufacturers MUST detail the security measures employed during the handling of the UDS seed, including access controls, secure storage practices, and sanitization procedures.  
* **Checklist Item:**  
  * **Requirement**: Field Entropy SHOULD be generated on die, and not be exposed outside the die.  
  * **Evaluation Methodology**: Manufacturers SHOULD detail the generation process for, and document exposure of field entropy.

#### *Access to Fuses*

* **Checklist Item:**  
  * **Requirement:** Access to the fuses containing the UDS seed and field entropy SHOULD be restricted exclusively to the mechanisms needed for loading these values into Caliptra's fuse registers. No other components or firmware should have read or write access, except for essential hardware functions like fuse sense and distribution logic.  
  * **Evaluation Methodology:** Manufacturers SHOULD provide architectural diagrams and RTL code excerpts demonstrating that only authorized hardware mechanisms can access these fuses.

### FW Authentication Keys

* **Checklist Item:**  
  * **Requirement:** Firmware authentication keys MUST be generated using an [ESV](https://csrc.nist.rip/Projects/cryptographic-module-validation-program/entropy-validations/esv) certified entropy source, and key derivation functions specified by [NIST SP 800-208](https://csrc.nist.gov/pubs/sp/800/208/final) and [FIPS 186-4](https://csrc.nist.gov/pubs/fips/186-4/final).
  * **Requirement:** Firmware authentication keys MUST NOT allow unauthorized users to perform signing operations.
  * **Requirement:** Firmware authentication keys MUST be stored in a manner that prevents disclosure of private key material. The manner of storage MUST only permit keys to be exported or copied to systems that enforce the same controls on usage and disclosure of the key.
  * **Requirement:** Signing operations performed using the firmware authentication key MUST be logged.
  * **Requirement:** Firmware authentication keys SHOULD be created and stored in a Hardware Security Module (HSM).
  * **Requirement:** Firmware authentication keys SHOULD require multi-party authentication to perform signing operations.
  * **Evaluation Methodology:** Manufacturers MUST describe their key management practices, including storage solutions, access controls, and procedures to prevent unauthorized access.

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
  * **Requirement:** The obfuscation key MUST be generated using a method that ensures sufficient entropy, such as an [ESV](https://csrc.nist.rip/Projects/cryptographic-module-validation-program/entropy-validations/esv) certified entropy source or an on-die Physically Unclonable Function (PUF) that is compliant with industry standards. 
  * **Evaluation Methodology:** Manufacturers MUST provide documentation on the obfuscation key generation method, including entropy measurements and compliance with relevant standards if applicable.  
* **Checklist Item:**  
  * **Requirement:** The obfuscation key MUST NOT be accessible (readable or modifiable) to firmware or any on-chip non-Caliptra entities, including preventing oracle attacks. The RTL key MUST not be on any scanaable path. 
  * **Evaluation Methodology:** Manufacturers MUST demonstrate, through architectural documentation and security analyses, that the obfuscation key is inaccessible to firmware and other unauthorized components.

### Fuses

#### *Access Control*

* **Checklist Item:**  
  * **Requirement:** Fuses containing Caliptra secrets SHOULD NOT be readable or writable by any mutable code in the SoC. Access SHOULD be restricted to secure hardware mechanisms and essential hardware functions like fuse sense and distribution logic.
  * **Evaluation Methodology:** Manufacturers SHOULD provide hardware design documentation showing access controls on fuse read/write mechanisms, ensuring only authorized hardware components can access these fuses.

#### *JTAG and Debug Interfaces*

* **Checklist Item:**  
  * **Requirement:** When JTAG or other debug interfaces are enabled, they SHOULD NOT allow access to Caliptra's fuses or fuse shadow registers containing secrets. This applies to both pre and post SoC reset states.  
  * **Evaluation Methodology:** Manufacturers SHOULD explain how debug interfaces are managed to prevent unauthorized access to sensitive fuses, including any hardware or firmware controls in place.

#### *Integrity Maintenance*

* **Checklist Item:**  
  * **Requirement:** The integrity of each fuse SHOULD be maintained throughout the lifespan of the device to prevent degradation or tampering that could affect security.  
  * **Evaluation Methodology:** Manufacturers SHOULD describe the techniques used to ensure fuse integrity, such as redundancy, error correction codes (ECC), or other protective measures.

#### *In-Field Programmable Fuses*

* **Checklist Item:**  
  * **Requirement:** Authorization mechanisms SHOULD be implemented for in-field programmable fuses to prevent unauthorized updates that could lead to denial-of-service or other attacks.  
  * **Evaluation Methodology:** Manufacturers SHOULD document the authorization processes required to program fuses in the field, including cryptographic protections or authentication steps.

#### *Key Revoke Bits Handling*

* **Checklist Item:**  
  * **Requirement:** The key revocation bits for public keys MUST be securely managed within the SOC Manager.  
  * **Evaluation Methodology:** Manufacturers MUST explain how key revocation bits are set, verified, and enforced within the system.

#### *Caliptra SVN (Security Version Number) Management*

* **Checklist Item:**  
  * **Requirement:** Before updating any Caliptra SVN fuses, the SoC SHOULD verify that the firmware integrity and authenticity have been validated, and that the new SVN is greater than the current one.  
  * **Evaluation Methodology:** Manufacturers SHOULD describe the SVN update process, including checks performed to prevent unauthorized or erroneous updates.

## Interfaces

### *Mailbox Interface Compliance*

* **Checklist Item:**  
  * **Requirement:** The SoC Manager SHOULD implement the mailbox interface according to the Caliptra specification, ensuring proper handling of commands and status registers. Using the Caliptra Libraries (RUST and C version) provided by the Caliptra WG release is recommended as a reference codebase.  
  * **Evaluation Methodology:** Manufacturers SHOULD provide evidence, such as interface specifications or test results, demonstrating compliance with the mailbox interface requirements.

### *Secure Mailbox Access*

* **Checklist Item:**  
  * **Requirement:** Access to the mailbox MUST be securely managed to prevent unauthorized entities from initiating communication with Caliptra. Only authenticated and authorized components may interact with the mailbox.  
  * **Evaluation Methodology:** Manufacturers MUST describe access control mechanisms for the mailbox, including any authentication methods and policies enforcing proper usage.

### *Debug Interface Management*

* **Checklist Item:**  
  * **Requirement:** The debug interfaces, including JTAG, MUST be securely managed to prevent unauthorized access to Caliptra internals or sensitive data.  
  * **Evaluation Methodology:** Manufacturers MUST explain how debug interfaces are controlled, including secure enable/disable mechanisms, and how they prevent unauthorized access to Caliptra.

### *Interface Wires Implementation*

* **Checklist Item:**  
  * **Requirement:** All interface signals between the SoC and Caliptra, especially those related to security and debug states, MUST be correctly implemented to ensure proper functionality and security. This includes signals like clock, reset, power good, ready signals, and any security state indicators.  
  * **Evaluation Methodology:** Manufacturers MUST provide hardware schematics and documentation showing correct implementation of critical interface signals, highlighting measures taken to prevent signal tampering or misuse.

## SoC Root of Trust (RoT)

### *Boot and Initialization Process*

* **Checklist Item:**  
  * **Requirement:** Measurements of firmware and configuration MUST be submitted to Caliptra before execution of the firmware, or usage of the configuration data. Measurements MUST be submitted to Caliptra by the same entity that collected the measurement (e.g. SOC FMC cannot pass measurements to SOC FW for submission to the Caliptra mailbox).   
  * **Evaluation Methodology:** Manufacturers MUST provide a detailed description of how measurements are communicated to Caliptra.  
* **Checklist Item:**  
  * **Requirement:** TBD, minimum set of measurements that MUST be taken

### *Caliptra PA\_USER Management*

* **Checklist Item:**  
  * **Requirement:** The management of Caliptra's PA\_USER MUST ensure isolation and protection of privileged operations, preventing unprivileged users from forging measurements or accessing privileged functions.
  * **Evaluation Methodology:** Manufacturers MUST document how PA\_USER is mapped in hardware and the mechanisms in place to isolate privileged operations from unprivileged ones.

### *Random Number Generator (RNG) Implementation*

* **Checklist Item:**  
  * **Requirement:** If an RNG is included in the Caliptra Wrapper, it SHOULD be securely implemented, and its design SHOULD meet applicable cryptographic standards. The source of entropy (internal or external) SHOULD be specified.  
  * **Evaluation Methodology:** Manufacturers SHOULD demonstrate that the RNG, including entropy sources, is compliant with standards like [NIST SP 800-90A](https://csrc.nist.gov/pubs/sp/800/90/a/r1/final), [SP 800-90B](https://csrc.nist.gov/pubs/sp/800/90/b/final), [SP 800-90C](https://csrc.nist.gov/pubs/sp/800/90/c/4pd).

### *SRAM Zeroization Process*

* **Checklist Item:**  
  * **Requirement:** The SoC SHOULD implement a secure SRAM zeroization process to ensure that sensitive data is not retained in memory after use.  
  * **Evaluation Methodology:** Manufacturers SHOULD describe the zeroization process, including when it is triggered (e.g. on reset, power-down) and how it ensures that all sensitive data is thoroughly erased.

### *External Entity Interaction*

* **Checklist Item:**  
  * **Requirement:** The pathways through which external entities interact with Caliptra MUST be securely implemented, ensuring that only authorized interactions are permitted, and that these interactions do not compromise Caliptra's security.  
  * **Evaluation Methodology:** Manufacturers MUST outline the architecture of interactions between external entities and Caliptra, emphasizing access controls, authentication mechanisms, and any intermediaries like security processors. Details on how untrusted entities are prevented from accessing Caliptra internals must be provided.

## Specific Functionality

### *Caliptra Mode Selection and State Handling*

* **Checklist Item:**  
  * **Requirement:** Where SoC behavior necessary to meet other requirements in this document is conditioned on SoC lifecycle state, the SoC MUST ensure that its own lifecycle is in a state that meets the requirements here prior to transitioning Caliptra's operational mode from unprovisioned to manufacturing or production.  
  * **Evaluation Methodology:** Manufacturers MUST provide a state machine diagram or equivalent documentation showing how Caliptra's mode transitions are managed and synchronized with the SoC's states.

### *Error Handling*

* **Checklist Item:**  
  * **Requirement:** The SoC MUST correctly implement error handling and reporting mechanisms for interactions with Caliptra, especially for security-relevant events, without leaking sensitive information.  
  * **Evaluation Methodology:** Manufacturers MUST document the error handling procedures, including what information is reported, how errors are logged, and measures taken to prevent information leakage. Specific error codes and messages should be reviewed for appropriateness.

### *Log Functionality in SoC*

* **Checklist Item:**  
  * **Requirement:** The SoC SHOULD implement logging functionality that records relevant events related to Caliptra operations, ensuring logs are tamper-evident and provide necessary information for attestation. The log does not need to be kept secure but should be tamper-evident to detect manipulation.  
  * **Evaluation Methodology:** Manufacturers SHOULD describe the logging mechanism, including how logs are structured, how they are protected against tampering (e.g., using cryptographic hash extensions), and how they integrate with Caliptra's measurement processes.

## Secure Processes

### Development Process

#### *Integrity of Firmware and Hardware*

* **Checklist Item:**
  * **Requirement:** The Caliptra RTL MUST match an official release.
  * **Evaluation Methodology:** Manufacturers MUST demonstrate via the [provided tools](https://github.com/chipsalliance/caliptra-sw/tree/main/ci-tools/release/tools) that RTL matches an official release.
* **Checklist Item:**
  * **Requirement:** Netlists, layout, and other development collateral derived from the RTL MUST maintain the same behavior as the released RTL when Caliptra is in the [Production Non-Debug state](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md#caliptra-security-states).
  * **Evaluation Methodology:** Manufacturers MUST provide evidence that collateral derived from the released RTL has not had its behavior modified.
* **Checklist Item:**
  * **Requirement:** Cryptographic hashes of the Caliptra ROM and firmware (FMC and RT) MUST match reference hashes of official Caliptra releases.
  * **Evaluation Methodology:** Manufacturers MUST demonstrate that the SHA384 hashes of ROM and firmware match those of official releases.

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
  * **Requirement:** The enabling and disabling of debugging features in production MUST be controlled and documented to prevent unauthorized access or leakage of sensitive information. Specific policies regarding when and how debugging can be enabled must be defined.  
  * **Evaluation Methodology:** Manufacturers MUST describe how debugging is managed in production, including any fuse settings, access controls, and procedures to disable debugging interfaces before deployment. Documentation must indicate whether physical presence or specific authorization is required to enable debugging.

#### *Flaw Remediation Process*

* **Checklist Item:**  
  * **Requirement:** There MUST be a defined process for handling reported vulnerabilities, including assessment, communication, and deployment of security updates or mitigations.  
  * **Evaluation Methodology:** Manufacturers MUST provide their flaw remediation policy. This policy must describe how vulnerabilities are received (e.g., bug bounty programs), evaluated, and prioritized, and how updates are securely delivered to devices in the field. Procedures for notifying stakeholders and compliance with relevant regulations should also be described.
