**Caliptra Checklist and Evaluation Methodology**

**Version 0.2**

# Contents  

[Introduction](#introduction)

[Checklist Summary](#checklist-summary)

[Checklist Areas](#checklist-areas)

[Assets](#assets)

[UDS Seed & Field Entropy](#uds-seed-&-field-entropy)

[FW Authentication Keys](#fw-authentication-keys)

[IDEVID Generation and Endorsement Flow](#idevid-generation-and-endorsement-flow)

[Obfuscation Key](#obfuscation-key)

[Fuses](#fuses)

[Interfaces](#interfaces)

[SoC Root of Trust (RoT)](#soc-root-of-trust-\(rot\))

[Specific Functionality](#specific-functionality)

[Secure Processes](#secure-processes)

[Development Process](#development-process)

[Production Process](#production-process)

# Introduction {#introduction}

The **Caliptra Checklist and Evaluation Methodology** document serves as a comprehensive guide for ensuring the secure and correct integration of the Caliptra intellectual property (IP) into a system-on-chip (SoC). Caliptra is a hardware root-of-trust (RoT) IP designed to provide foundational security services within a computing system. Proper integration of Caliptra is crucial to maintaining the overall security posture of the final product.

This document outlines detailed requirements and evaluation methodologies across various domains, including asset management, interface implementations, and secure process adherence. The primary goals are to:

* **Ensure Security Compliance:** Provide clear and testable requirements that align with industry best practices and standards, such as those from NIST and FIPS.  
    
* **Facilitate Evaluation:** Offer comprehensive evaluation methodologies that allow for consistent and thorough assessment of compliance with the checklist items.

* **Promote Clarity and Specificity:** Avoid vague language by specifying exact requirements, thereby making the checklist actionable and reducing ambiguity during the evaluation process.

* **Address Critical Security Areas:** Focus on key areas that have significant impact on the security of Caliptra integration, such as cryptographic key management, secure boot processes, and access control mechanisms.

* **Enhance Integration Efficiency:** By providing a clear roadmap of requirements, the document aims to streamline the integration process and assist manufacturers in proactively addressing security considerations.

The checklist items have been developed through a thorough analysis of:

* **Caliptra Specifications:** Reviewing the Caliptra IP documentation to extract relevant requirements and ensure alignment with the intended security features.  
    
* **Industry Standards and Best Practices:** Incorporating guidelines from recognized standards to enhance the robustness of security mechanisms.

* **Feedback and Collaboration:** Integrating input from various stakeholders, including security experts and industry professionals, to refine the checklist and address potential gaps.

* **Asset-Based Analysis:** Identifying critical assets within the Caliptra integration context and tailoring requirements to protect these assets effectively.

By adhering to the checklist and employing the specified evaluation methodologies, manufacturers and evaluators can work collaboratively to ensure that the Caliptra integration meets stringent security requirements, thereby bolstering the trustworthiness of the final product.

# Caliptra Documentation

The Caliptra Specification is maintained within the [ChipsAlliance Caliptra github](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md).  This is a live link. Each generation, the main specification will be updated and the older specifications will be maintained for reference for designs based on that specification.  For example, here is the specification for [Calitpra 1.X](https://github.com/chipsalliance/Caliptra/blob/main/doc/caliptra_1x/Caliptra.md).

The [HW specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md) and [HW integration specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraIntegrationSpecification.md) also have their own live links. For older versions of the HW, it is best to go to the same location which is tagged with that release version.

This checklist is built from these specifications with the goal to help ensure that Caliptra is integrated correctly within a design.

# Checklist Summary {#checklist-summary}

The following is a consolidated list of all requirements to ensure comprehensive coverage:

1. **Assets**  
   * UDS Seed & Field Entropy  
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

# Checklist Areas {#checklist-areas}

## Assets {#assets}

### UDS Seed & Field Entropy {#uds-seed-&-field-entropy}

#### *Generation and Provisioning*

* **Checklist Item:**  
  * **Requirement:** The UDS seed and field entropy must be generated using a cryptographically secure random number generator (CSRNG) compliant with [NIST Entropy Source Certification](https://csrc.nist.gov/projects/cryptographic-module-validation-program/entropy-validations) SP 800-90B.  
  * **Evaluation Methodology:** Manufacturers must provide documentation demonstrating compliance with applicable standards for entropy generation.   
* **Checklist Item:**  
  * **Requirement:** The confidentiality and integrity of the UDS seed and must be protected during generation, storage, and provisioning. Access to these assets must be strictly controlled, and any temporary storage must be securely zeroized after use.  
  * **Evaluation Methodology:** Manufacturers must detail the security measures employed during the handling of the UDS seed, including access controls, secure storage practices, and zeroization procedures.  
* **Checklist Item:**  
  * **Requirement**: Field Entropy should be generated on die with no exposure to outside the die.  
  * **Evaluation Methodology**: Manufacturers/auditors must verify the generation process and document any reason the UDS seed is exposed outside of the die.

#### *Access to Fuses*

* **Checklist Item:**  
  * **Requirement:** Access to the fuses containing the UDS seed and field entropy should be restricted exclusively to the mechanisms needed for loading these values into Caliptra's fuse registers. No other components or firmware should have read or write access, except for essential hardware functions like fuse sense and distribution logic.  
  * **Evaluation Methodology:** Manufacturers must provide architectural diagrams and RTL code excerpts demonstrating that only authorized hardware mechanisms can access these fuses.

### FW Authentication Keys {#fw-authentication-keys}

#### *Generation and Handling*

* **Checklist Item:**  
  * **Requirement:** Firmware authentication keys must be generated using a secure process, preferably utilizing a Hardware Security Module (HSM) certified under standards like FIPS 140-3.  
  * **Evaluation Methodology:** Manufacturers must provide documentation of the key generation process, including details about the HSM used, its certification status, and how it ensures sufficient entropy and key integrity. If non-HSM solutions are used, they must meet equivalent security requirements.

#### *Private Key Security*

* **Checklist Item:**  
  * **Requirement:** The private keys used for firmware authentication must be securely stored and handled, with access limited to authorized personnel and systems. The use of an HSM or equivalent secure storage is required.  
  * **Evaluation Methodology:** Manufacturers must describe their key management practices, including storage solutions, access controls, and procedures to prevent unauthorized access.

### IDEVID Generation and Endorsement Flow {#idevid-generation-and-endorsement-flow}

#### *CSR Handling*

* **Checklist Item:**  
  * **Requirement:**  Handling and transmission of the IDevID and any other CSRs generated by Caliptra MUST ensure that only authentic endorsement requests are signed by the CA.  
  * **Evaluation Methodology:** Manufacturers must outline the mechanisms used to protect the CSR during transmission from Caliptra to the endorsement environment, including cryptographic protections and secure channels.

#### *Certificate Provisioning*

* **Checklist Item:**  
  * **Requirement:** The IDEVID certificates, including CA certificates, must adhere to specified formats and cryptographic standards (e.g., key sizes, algorithms as per NIST guidelines). Acceptable algorithms and key strengths must meet the same security strength that Caliptra IP produces for the entire CA cert chain.  
  * **Evaluation Methodology:** Manufacturers must provide examples of the certificate chain created demonstrating compliance with the required formats and standards.

### Obfuscation Key {#obfuscation-key}

#### *Generation and Handling*

* **Checklist Item:**  
  * **Requirement:** The obfuscation key must be generated using a secure method that ensures sufficient entropy, such as an ESV certified HSM or an on-die Physical Unclonable Function (PUF) compliant with industry standards.  
  * **Evaluation Methodology:** Manufacturers must provide documentation on the obfuscation key generation method, including entropy measurements and compliance with relevant standards if applicable.  
* **Checklist Item:**  
  * **Requirement:** The obfuscation key must not be accessible (readable or modifiable) to firmware or any on-chip non-caliptra entities, including preventing oracle attacks.  
  * **Evaluation Methodology:** Manufacturers must demonstrate, through architectural documentation and security analyses, that the obfuscation key is inaccessible to firmware and other unauthorized components.

### Fuses {#fuses}

#### *Access Control*

* **Checklist Item:**  
  * **Requirement:** Fuses containing Caliptra secrets should not be readable or writable by any mutable code in the SoC. Access should be restricted to secure hardware mechanisms. Exceptions are allowed for essential hardware functions like fuse sense and distribution logic.  
  * **Evaluation Methodology:** Manufacturers must provide hardware design documentation showing access controls on fuse read/write mechanisms, ensuring only authorized hardware components can access these fuses.

#### *JTAG and Debug Interfaces*

* **Checklist Item:**  
  * **Requirement:** When JTAG or other debug interfaces are enabled, they should not allow access to Caliptra's fuses or fuse shadow registers containing secrets. This applies to both pre and post SoC reset states.  
  * **Evaluation Methodology:** Manufacturers must explain how debug interfaces are managed to prevent unauthorized access to sensitive fuses, including any hardware or firmware controls in place.

#### *Integrity Maintenance*

* **Checklist Item:**  
  * **Requirement:** The integrity of each fuse should be maintained throughout the lifespan of the device to prevent degradation or tampering that could affect security.  
  * **Evaluation Methodology:** Manufacturers must describe the techniques used to ensure fuse integrity, such as redundancy, error correction codes (ECC), or other protective measures.

#### *In-Field Programmable Fuses*

* **Checklist Item:**  
  * **Requirement:** Authorization mechanisms should be implemented for in-field programmable fuses to prevent unauthorized updates that could lead to denial-of-service or other attacks.  
  * **Evaluation Methodology:** Manufacturers must detail the authorization processes required to program fuses in the field, including cryptographic protections or authentication steps.

#### *Key Revoke Bits Handling*

* **Checklist Item:**  
  * **Requirement:** The key revocation bits for public keys must be securely managed within the SOC Manager.  
  * **Evaluation Methodology:** Manufacturers must explain how key revocation bits are set, verified, and enforced within the system.

#### *Caliptra SVN (Security Version Number) Management*

* **Checklist Item:**  
  * **Requirement:** Before updating any Caliptra SVN fuses, the SoC should verify that the firmware integrity and authenticity have been validated, and that the new SVN is greater than the current one.  
  * **Evaluation Methodology:** Manufacturers must describe the SVN update process, including checks performed to prevent unauthorized or erroneous updates.

### Interfaces {#interfaces}

#### *Mailbox Interface Compliance*

* **Checklist Item:**  
  * **Requirement:** The SoC Manager should implement the mailbox interface according to the Caliptra specification, ensuring proper handling of commands and status registers.  Using the Caliptra Library’s (RUST and C version) provided by the Caliptra WG release is recommended as a reference codebase.  
  * **Evaluation Methodology:** Manufacturers must provide evidence, such as interface specifications or test results, demonstrating compliance with the mailbox interface requirements.

#### *Secure Mailbox Access*

* **Checklist Item:**  
  * **Requirement:** Access to the mailbox must be securely managed to prevent unauthorized entities from initiating communication with Caliptra. Only authenticated and authorized components should interact with the mailbox.  
  * **Evaluation Methodology:** Manufacturers must describe access control mechanisms for the mailbox, including any authentication methods and policies enforcing proper usage.

#### *Debug Interface Management*

* **Checklist Item:**  
  * **Requirement:** The debug interfaces, including JTAG, must be securely managed to prevent unauthorized access to Caliptra internals or sensitive data.  
  * **Evaluation Methodology:** Manufacturers must explain how debug interfaces are controlled, including secure enable/disable mechanisms, and how they prevent unauthorized access to Caliptra.

#### *Interface Wires Implementation*

* **Checklist Item:**  
  * **Requirement:** All interface signals between the SoC and Caliptra, especially those related to security and debug states, must be correctly implemented to ensure proper functionality and security. This includes signals like clock, reset, power good, ready signals, and any security state indicators.  
  * **Evaluation Methodology:** Manufacturers must provide hardware schematics and documentation showing correct implementation of critical interface signals, highlighting measures taken to prevent signal tampering or misuse.

### SoC Root of Trust (RoT) {#soc-root-of-trust-(rot)}

#### *Boot and Initialization Process*

* **Checklist Item:**  
  * **Requirement:** Measurements of firmware and configuration must be submitted to Caliptra prior any execution of the firmware or usage of the configuration data. Measurements must be submitted to Caliptra by the same entity that collected the measurement (eg: SOC FMC cannot hand measurements over to SOC FW for submission to the Caliptra mailbox).   
  * **Evaluation Methodology:** Manufacturers must provide a detailed description of how measurements are communicated to Caliptra.  
* **Checklist Item:**  
  * **Requirement:** TBD, minimum set of measurements that must be taken

#### *Caliptra PA\_USER Management*

* **Checklist Item:**  
  * **Requirement:** The management of Caliptra's PA\_USER must be clearly defined and securely implemented to ensure isolation and protection of privileged operations.  
  * **Evaluation Methodology:** Manufacturers must detail how PA\_USER is mapped in hardware and the mechanisms in place to isolate privileged operations from unprivileged ones, ensuring that unprivileged users cannot modify Caliptra measurements or access privileged functions.

#### *Random Number Generator (RNG) Implementation*

* **Checklist Item:**  
  * **Requirement:** If an RNG is included in the Caliptra Wrapper, it must be securely implemented, and its design must meet applicable cryptographic standards. The source of entropy (internal or external) must be specified.  
  * **Evaluation Methodology:** Manufacturers must provide specifications of the RNG, including entropy sources, compliance with standards like NIST SP 800-90A/B/C, and any test results validating its performance.

#### *SRAM Zeroization Process*

* **Checklist Item:**  
  * **Requirement:** The SoC should implement a secure SRAM zeroization process to ensure that sensitive data is not retained in memory after use.  
  * **Evaluation Methodology:** Manufacturers must describe the zeroization process, including when it is triggered (e.g., on reset, power-down) and how it ensures that all sensitive data is thoroughly erased.

#### *External Entity Interaction*

* **Checklist Item:**  
  * **Requirement:** The pathways through which external entities interact with Caliptra must be securely implemented, ensuring that only authorized interactions are permitted, and that these interactions do not compromise Caliptra's security.  
  * **Evaluation Methodology:** Manufacturers must outline the architecture of interactions between external entities and Caliptra, emphasizing access controls, authentication mechanisms, and any intermediaries like security processors. Details on how untrusted entities are prevented from accessing Caliptra internals must be provided.

### Specific Functionality {#specific-functionality}

#### *Caliptra Mode Selection and State Handling*

* **Checklist Item:**  
  * **~~Requirement:~~**~~ The SoC **must** securely manage Caliptra's operational modes (e.g., unprovisioned, manufacturing, production), ensuring that mode transitions are properly controlled and that Caliptra's state aligns correctly with the SoC's state.~~  
  * **Requirement:** Where SoC behavior necessary to meet other requirements in this document is conditioned on SoC lifecycle state, the SoC must ensure that its own lifecycle is in a state that meets the requirements here prior to transitioning Caliptra's operational mode from unprovisioned to manufacturing or production.  
  * **Evaluation Methodology:** Manufacturers should provide a state machine diagram or equivalent documentation showing how Caliptra's mode transitions are managed and synchronized with the SoC's states. ~~This includes ensuring that when the SoC enters debug mode, Caliptra reflects this state appropriately.~~

#### *Error Handling*

* **Checklist Item:**  
  * **Requirement:** The SoC must correctly implement error handling and reporting mechanisms for interactions with Caliptra, especially for security-relevant events, without leaking sensitive information.  
  * **Evaluation Methodology:** Manufacturers must document the error handling procedures, including what information is reported, how errors are logged, and measures taken to prevent information leakage. Specific error codes and messages should be reviewed for appropriateness.

#### *Log Functionality in SoC*

* **Checklist Item:**  
  * **Requirement:** The SoC should implement logging functionality that records relevant events related to Caliptra operations, ensuring logs are tamper-evident and provide necessary information for attestation. The log does not need to be kept secure but must be tamper-evident to detect manipulation.  
  * **Evaluation Methodology:** Manufacturers must describe the logging mechanism, including how logs are structured, protected against tampering (e.g., using cryptographic hash extensions), and how they integrate with Caliptra's measurement processes.

## Secure Processes {#secure-processes}

### Development Process {#development-process}

#### *Integrity of Firmware and Hardware*

* **Checklist Item:**  
  * **Requirement:** The Caliptra RTL must match an official release. Netlists, layout, and other development collateral derived from the RTL must maintain the same  behavior as the released RTL.  
  * **Evaluation Methodology:** Manufacturers must provide evidence of hash verification against official releases. Manufacturers must provide evidence that collateral derived from the released RTL has not had its behavior modified.

#### *Caliptra FW Cryptographic Hash*

* **Checklist Item:**  
  * **Requirement:** Cryptographic hashes of the Caliptra ROM and firmware (FMC and RT) must match Caliptra reference hashes of official Caliptra releases.  
  * **Evaluation Methodology:** Demonstrations showing that the cryptographic hash of the Caliptra firmware (ROM and FW) matches a reference hash value are **required**.

#### *Testing and Verification*

* **Checklist Item:**  
  * **Requirement:** The product must undergo thorough testing and verification during development, focusing on both functional correctness and security aspects. This includes testing of specific features and security mechanisms.  
  * **Evaluation Methodology:** Manufacturers must present test plans, results, and security analyses covering critical functionalities such as:  
    * Field programmable entropy API  
    * Generation and endorsement of attestation messages  
    * CSR generation and handling  
    * DICE identity provisioning  
    * Attestation processes  
    * Debug state transitions  
    * SVN updates and enforcement  
    * Firmware updates (FMC and RT FW)

### Production Process {#production-process}

#### *Debugging Controls*

* **Checklist Item:**  
  * **Requirement:** The enabling and disabling of debugging features in production must be controlled and documented to prevent unauthorized access or leakage of sensitive information. Specific policies regarding when and how debugging can be enabled must be defined.  
  * **Evaluation Methodology:** Manufacturers must describe how debugging is managed in production, including any fuse settings, access controls, and procedures to disable debugging interfaces before deployment. Documentation should clarify whether physical presence or specific authorization is required to enable debugging.

#### *Flaw Remediation Process*

* **Checklist Item:**  
  * **Requirement:** There must be a defined process for handling reported vulnerabilities, including assessment, communication, and deployment of security updates or mitigations.  
  * **Evaluation Methodology:** Manufacturers must provide their flaw remediation policy, detailing how vulnerabilities are received (e.g., bug bounty programs), evaluated, prioritized, and how updates are securely delivered to devices in the field. Procedures for notifying stakeholders and compliance with relevant regulations should also be described.