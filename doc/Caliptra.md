![OCP Logo](./images/OCP_logo.png)

<p style="text-align: center;">Caliptra: A Datacenter System on a Chip (SoC) Root of Trust (RoT)</p>

<p style="text-align: center;">Revision 1.0</p>

<p style="text-align: center;">Version 0.7</p>

<div style="page-break-after: always"></div>

# Introduction

Caliptra[^1] was originally created as part of the Open Compute Project ([OCP](https://www.opencompute.org/)). The major revisions of the Caliptra specifications are published at OCP. The evolving source code and documentation for Caliptra are in this repository within the [CHIPS Alliance Project](https://chipsalliance.org/), a Series of LF Projects, LLC.

The objective of Caliptra is to define core RoT capabilities that must be implemented in the System on Chip (SoC) or ASIC of any device in a cloud platform. The collection of these RoT capabilities is referred to as the ***Silicon RoT Services (Silicon RoT).***

<div style="page-break-after: always"></div>


# Background

The overall security posture of silicon devices depends on establishing a core root of trust (RoT) and chain of trust. The core root of trust and chain of trust must attest to the integrity of configuration and mutable code.

Traditional RoT architectures offer many intrinsic security services and hosted security applications on a trusted execution environment (TEE). These architectures include (but are not limited to) hardware capabilities (cryptographic and microprocessor), ROM, firmware, and API infrastructure. These solutions are instantiated in discrete or integrated forms in various platform and component architectures.

Some of these solutions are either proprietary or aligned to specific parts of industry standards, consortium, or association specifications; for example, National Institutes of Standards and Technology (NIST), Open Compute Project (OCP), Trusted Computing Group (TCG), Distributed Management Task Force (DMTF), Institute of Electrical and Electronics Engineers (IEEE), etc. These solutions may be certified to conform to various standards; for example, the NIST cryptographic algorithm Validation program (CAVP).

Establishing a consistent RoT on very different hardware configurations while maintaining configuration and deployment flexibility is challenging. There is no uniform configuration across Cloud Service Providers (CSPs). For example, a system with host processors has very different firmware security measures when compared to a system without head-nodes or host processors.

The OCP Security WG specifications are making progress toward establishing the platform and peripheral security architecture [recommendations](https://docs.google.com/document/d/1-bfAF86cEKcn1guF-Qj2C2HhMM2oJ2njNGdHxZeetR0/edit#heading=h.pdkwdxyrhnco) that are necessary to attain the desired consistency in platform security orchestration.

## Silicon RoT goals

To drive agility of specification definition and to maximize applicability, the scope of Caliptra is deliberately minimalistic. This minimalist approach drives industry alignment, consistency, and faster adoption of foundational device security primitives. A well and narrowly defined specification maximizes architectural composability; reusability across CSPs, products, and vendors; and feasibility of open sourcing.

Enhancements and advanced use cases and applications are outside the scope of this specification and may be developed in the form of a roadmap for the Silicon RoT and community engagement.

Caliptra defines a design standard for a Silicon internal RoT baseline. This standard satisfies a Root of Trust for Measurement (RTM) role. The open-source implementation of Caliptra drives transparency into the RTM and measurement mechanism that anchor hardware attestation. Caliptra must boot the SoC, measure the mutable code that it loads, and measure and control mutation of non-volatile configuration bits in the SoC. Caliptra reports these measurements with signed attestations rooted in unique per-asset cryptographic entropy. As such, Caliptra serves as a Root of Trust for Identity (RTI) for the SoC.

To satisfy these Silicon RoT goals, no other capabilities are part of this specification. This scope decouples platform integrity capabilities that can be enforced and evolve independently through other platform devices or services – such as update, protection, and recovery.

Within this scope, the goals for a Caliptra 1.0 specification include:

* Definition and design of the standard silicon internal RoT baseline:
  * Reference functional specification:
    * Scope including RTM and RTI capabilities
    * Control over SoC non-volatile state, including per asset entropy
  * Reference APIs:
    * Attestation APIs
    * Internal SoC services
  * Reference implementation
  * Open source reference (including RTL and firmware reference code):
    * For implementation consistency, using open source dynamics to avoid pitfalls and common mistakes
    * For accelerated adoption, so that future products can leverage existing designs and avoid having to start the design process from scratch
    * For greater transparency, to avoid fragmentation in the implementation space
  * Firmware and RTL logical design are open, managed by consortium
* Consistency - across the industry in the internal RoT (iRoT) architecture and implementation:
  * DICE identity, measurement, and recovery
* The silicon iRoT scope includes all datacenter-focused server class SoC / ASIC (datacenter focused) devices (SSD - DC, NIC, CPU, GPU - DC):
  * Critical priority are devices with the ability to handle user plain text data
    * Top priority are CPU SoCs
    * Other examples include SmartNIC and accelerators
  * Over time, the scope includes further datacenter devices
    * SSD, HDD, BMC, DIMM

Explicitly out of scope is how silicon integration into backend work is performed such as:

* Foundry IP integration
* Physical design countermeasures
* Analog IPs
* Post manufacture test and initialization (OSAT)
* Certification

## Use cases

The Silicon RoT use cases can be supported through the adoption of specific industry standards, and association and consortium specifications. For more information, see specific documents in [References](#references).

In this version of the specification, the desired capabilities address the basics of supply chain security use cases.

### Supply chain security

* **Mutable code integrity:** The objective is to prove the device is running genuine firmware such that the device manufacturer can vouch for its authenticity and integrity, and the device owner can ensure only authorized updates are applied to the device. This flow is aligned with [Reference 9](#ref-9) and can be achieved with dual signature verification of equal imposition.
* **Configuration and lifecycle management**: The objective is to allow the platform owner to securely configure the RoT capabilities, and to enable and authorize lifecycle state transitions of the SoC.

### DICE Protection Environment

Caliptra implements the DPE API, allowing it to derive and wield a DICE identity on behalf of other elements within the SoC. Use cases for this API include serving as a signing oracle for a Security Protocol and Data Model (SPDM) responder that is executing in the SoC application processor, as well as authentication to a discrete TPM device.

# Industry standards and specifications

This specification follows the industry standards and specifications listed in [References](#references).

## NIST SP 800-193 Platform Firmware Resiliency

Per [Reference 1](#ref-1), RoT subsystems are required to fulfill three principles: *protection, detection* and *recovery*. The associated RoT services are referred to as:

* **The Root of Trust for Update (RTU)** is responsible for authenticating firmware updates and critical data changes to support platform protection capabilities.
* **The Root of Trust for Detection (RTD)** is responsible for firmware and critical data corruption detection capabilities.
* **The Root of Trust for Recovery (RTRec)** is responsible for recovery of firmware and critical data when corruption is detected, or when instructed by an administrator.

These RoT services can be hosted by a complex RoT as a whole or these services can be spread across one or more components within a platform. This determination has a basis in physical risk. Physical adversaries with reasonable skill can bypass a discrete RoT’s detection capabilities, for example, with SPI interposers.

However, an RoT embedded within a SoC or ASIC represents a much higher detection bar for a physical adversary to defeat. For this reason, Caliptra shall deliver the **Detection** (or Measurement) capability.

With the objectives of minimalistic scope for Silicon RoT and maximizing applicability and adoption of this specification, **Update** and **Recovery** are decoupled from Caliptra and are expected to be provided by an external RoT subsystem, such as a discrete RoT board element on a datacenter platform. Because a physical adversary can trivially nullify any recovery or update capabilities, no matter where implemented, decoupling represents no regression in a security posture, while enabling simplicity and applicability for the internal SoC silicon RoT.

Detection of corrupted critical code and data (configuration) requires strong end to end cryptographic integrity verification. To meet the RTD requirements, Silicon RoT shall:

* Cryptographically measure its code and configuration
* Sign these measurements with a unique attestation key
* Report measurements to a host or external entity, which can further verify the authenticity and integrity of the device (also known as *attestation*)

**Measurements** include **Code** and **Configuration**. Configuration includes invasive capabilities that impact the user service level agreement (SLA) on confidentiality; for example, the enablement of debug capabilities that grant an operator access to raw, unencrypted registers for any tenant context. In order to measure and attest configuration, the Silicon RoT must be in control of the configuration.

As an extension to controlling configuration, the Silicon RoT must control the security states (for more information, see *[Caliptra Security States](#caliptra-security-states)*). Certain security states by design grant full invasive capabilities to an external operator, for debug or field analysis.

Measurements must be uniquely bound to the device and its manufacturer at a minimum. This establishes the need for **Identity** services in the Silicon RoT, which serve as the basis for key derivation and attestation authenticity.

For further details about how Caliptra addresses NIST SP 800-193, see [Device Resilience](#device-resilience).

## Trusted Computing Group (TCG) DICE Attestation

In accordance with OCP Attestation specification [Reference 8](#ref-8), devices must have a cryptographic identity for the endorsement of attestation quotes. The RTM implementation follows TCG DICE (for information, see [Reference 4](#ref-4), [Reference 5](#ref-5), and [Reference 6](#ref-6)). One of the benefits of TCG DICE device identities is having renewable security. This renewability complements ownership transfer and circular economy. The new owner is not burdened with the identity of the previous owner, nor is the new owner burdened with trusting an irrevocable hardware identity certificate. This benefits the transferee, as their identities can be revoked through standard PKI mechanisms. DICE based certificates are fully compatible with Public Key Infrastructure (PKI), including full lifecycle management and PKI Certificate Revocation List (CRL).

Operational security during the manufacturing process is critical, to ensure the DICE entropy is securely initialized, certified, and registered. Operational security avoids any pilfering of this asset by eavesdroppers. Operational security is outside the scope of this specification.

# Threat model

The Caliptra threat model describes attacker profiles, assets and attack surfaces, and paths to these assets based on attacker profiles. Subsections provide further details.

Threat scenarios as comprehended by assets and possible attack paths are as complete as possible but focus on the worst case scenarios. Thus not every attack path to asset is captured in this threat model.

## Attacker profiles

An attacker profile is based on factors like the tools that are accessible to the attacker, the level of access to the target of evaluation, and expertise of the attacker to use these methods. These factors are described in the following tables.

*Table 1: Tools accessible to attacker*

| **Attack tools** | **Type of attack** | **Purpose and usage** |
| :--------- | :--------- | :--------- |
| Debuggers, fuzzing devices, image reverse engineering tools, and software payloads | Logical fault injection | Find logical and functional vulnerabilities and exploit those to achieve unauthorized operations. |
| Clock fault injectors, voltage fault injectors, electromagnetic fault injectors, optical fault injectors, and micro probing | Environmental fault injection | Alter the execution flow of the critical decision points, especially in the early execution. |
| Power analyzers, timing analyzers (scopes, etc.), low speed bus analyzers, and optical emission analyzers | Side channel analysis | Infer security sensitive information by analyzing various operational conditions. |
| Microscopic imaging, reverse engineering, scanning electron microscope imaging, and focused ion beam (FIB) | Chip invasive attacks| Decapsulation, depackaging, and rebonding to probe the internals of the chip. |

*Table 2: Type of access to level of access*

| **Type of access** | **Levels of access** | **Attack paths available** |
| :--------- | :--------- | :--------- |
| Physical access | Unrestricted access for physical and logical attacks. | Chip invasive attacks and chip non-invasive attacks |
| Remote access | Limited access for attacks with both privileged and unprivileged access rights. | Chip non-invasive attacks and network attacks |

*Table 3: Definition of expertise (JIL)*

|**Proficiency level**|**Definition**|**Detailed definition**|
| :--------- | :--------- | :--------- |
| **Expert** | Can use chip invasive, fault injections, side channels, and logical tools. Understands hardware and software in depth.<br>Familiar with implementation:<br> - Algorithms<br> - Protocols<br> - Hardware structures<br> - Principle and security concepts | Developer-level knowledge of algorithms, protocols, hardware structure, and principles. Understands techniques and tools for attacks. |
| **Proficient** | Can use fault injections, side channels, and logical tools. Has reasonable understanding of hardware and software. Familiar with security behavior. | Familiar with security behavior and classical attacks. |
| **Layperson** | No particular expertise. | No particular expertise. |

## Types of attacks

### Physical attacks

A physical attacker has full access to the electrical and physical components. This includes access to interfaces, connectors, and ports of the SoC/ASIC in which Caliptra is integrated without restriction.

Invasive attacks that involve depackaging or delayering of the SoC/ASIC are out-of-scope. Non-invasive attacks are in scope.

* Fault injection attacks
  * *Counter measurements - as strong recommendation*
* Power and electromagnetic analysis attacks
  * *Counter measurements - as strong recommendation*

*Table 4: Attack types*

| **Attack** |  **Description** | **Threat model scope** |
| :--------- | :--------- | :--------- |
| Electromagnetic – passive | Attacker observes the electromagnetic power spectrum and signals radiated from the product. | - Includes all attacks at all frequency ranges, including radio frequencies, infrared, optical, and ultraviolet.<br> - Excludes attacks that require removing the package lid. |
| Electromagnetic – active  | Attacker directs electromagnetic radiation at the product or portions of the product. | - Includes all attacks at all frequency ranges, including radio frequencies, infrared, optical, and ultraviolet.<br> - Excludes attacks that require removing the package lid. |
| Electric – passive    | Attacker probes the external pins of the package and observes electrical signals and characteristics including capacitance, current, and voltage signal. | - Includes both analog attacks and digital signal attacks.<br> - Excludes attacks that require removing the package lid. |
| Electric – active     | Attacker alters the electrical signal or characteristics of external pins. | - Includes both analog attacks and digital signal attacks.<br> - Excludes attacks that require removing the package lid. |
| Temperature – passive | Attacker observes the temperature of the product or portions of the product.| Excludes attacks that require removing the package lid. |
| Temperature – active  | Attacker applies external heat sources or sinks to alter the temperature of the product, possibly in a rapid fashion. | - Includes all temperature ranges (for example, pouring liquid nitrogen over the package or heating the package to above 100 C).<br> - Excludes attacks that require removing the package lid.|
| Sound - passive | Attacker observes the sounds emitted by the product. | - Includes all frequencies.<br> - Excludes attacks that require removing the package lid. |

*Table 5: Logical attacks*

| **Attack** | **Description** | **Threat model scope** |
| :--------- | :--------- | :--------- |
| Debug and register interfaces | Manipulation of externally accessible registers of Caliptra.|Includes all buses that are accessible to components external to Caliptra, including JTAG.|
| Software interfaces       | Attacker invokes software interfaces that are exposed by Caliptra to external components. | Includes all externally exposed software interfaces from both non-RoT firmware as well as interfaces accessed by external IP blocks. Includes exploiting both design and implementation flaws. For high value assets only (see next subsection), the attacker is assumed to fully control all mutable code of the SoC, including privileged Caliptra mutable code. |
|Side channel - timing|Attacker observes the elapsed time of different sensitive operations.|Includes attacks where the attacker actively stimulates the sensitive operations while timing.|
|Cryptographic analysis|Attacker observes plaintext, ciphertext, related data, or immediate values in cryptography to overcome cryptographic controls.| Includes all practical cryptanalysis attacks. Assumes NIST-unapproved algorithms provide no security (for example, SHA-1, Single DES, ChaCha20). Assumes any cryptographic algorithm that provides less than 128 bits of security (as determined by NIST SP 800-57) provides no security. Excludes quantum computer attacks. This exclusion will be removed soon. |

### Trust boundaries

The following figure shows trust boundaries for the discussion of threat modeling. SoCs based on Caliptra are expected to have Caliptra as silicon RoT, and are expected to have a platform or SoC security engine to orchestrate SoC security needs and the rest of the SoC.

Trust levels of Caliptra and the SoC security engine are not hierarchical. These two entities are responsible for different security aspects of the chip.

*Figure 1: Caliptra trust boundaries*

![Caliptra_trust_boundary](./images/Caliptra_trust_boundary.png)

### Caliptra interactions

The Caliptra Core blocks consume the Tcc and Tcw trust level components.  This boundary includes crypto accelerators, hardware key sequencer, key vault, Caliptra microcontroller, ROM, and subsystem interconnects.  The Caliptra Core provides deterministic Caliptra behavior.  The Caliptra subsystem includes the Tc, Tcw, Tse, and Trs. The Caliptra subsystem extends the trust level into the SoC subsystem and allows for customization of the SoC initialization.  For information on Caliptra Core and the Caliptra subsystem, see [Caliptra Profiles](#caliptra-profiles).

### <a id="assets"></a>Caliptra assets and threats

Assets are defined to be secrets or abilities that must be protected by an owner or user of the asset.  Ownership means that the owner has the responsibility to protect these assets and must only make them available based on a defined mechanism while protecting all other assets.

An example of when an owner must protect assets is moving from secure mode to insecure mode.  Another example is moving from one owner to another. Before moving through these transitions, the owner must ensure all assets are removed, disabled, or protected based on how the use case is defined.

*Table 6: Assets*

| Asset category | Asset      | Security property | Attack profile | Attack path | Mitigation |
| :------------- | :--------- | :---------------- | :------------- | :---------- | :--------- |
| Fuse/OTP high value secrets | UDS Seed | Confidentiality and integrity | Expert | Malicious manufacturing spoofing of UDS Seeds | UDS obfuscation/encryption with class RTL key |
| Fuse/OTP high value secrets | UDS Seed | Confidentiality and integrity | Expert | Invasive attack (fuse analysis) | Shield fuse IP |
| Fuse/OTP high value secrets | UDS Seed | Confidentiality and integrity | Expert | Boot path tampering while retrieving UDS values | UDS obfuscation/encryption with class RTL key |
| Fuse/OTP high value secrets | UDS Seed | Confidentiality and integrity | Expert | Attempting to derive die specific keys by knowing UDS | Confine unobfuscated UDS and subsequent derivations to key vault |
| Fuse/OTP high value secrets | Field entropy | Confidentiality and integrity | Expert | Malicious manufacturing spoofing on field entropy | Field entropy obfuscation and encryption with class RTL key |
| Fuse/OTP high value secrets | Field entropy | Confidentiality and integrity | Expert | Invasive attack (fuse analysis) | Shield fuse IP |
| Fuse/OTP high value secrets | Field entropy | Confidentiality and integrity | Expert | Boot path tampering while retrieving field entropy values | Field entropy obfuscation and encryption with class RTL key |
| Fuse/OTP high value secrets | Field entropy | Confidentiality and integrity | Expert | Attempting to derive die specific keys by knowing field entropy | Confine field entropy and subsequent derivations to key vault |
| Fuse/OTP high value secrets | FW authentication keys | Integrity | Proficient | Glitching | 1. Redundant decision making on critical code execution<br>2. Error check before consuming values from fuses<br>3. Environmental monitoring and protection |
| Fuse/OTP high value secrets | Versioning information from fuses | Integrity | Proficient | Glitching | Environmental monitoring and protection |
| Fuse/OTP high value secrets | IDEVID CERT chain | Integrity | Proficient | Glitching | 1. Environmental monitoring and protection<br>2. Error check before consuming values from fuse in various ways |
| Die unique assets | UDS (802.1AR Unique Device Secret) | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Die unique assets | CDI<sub>n</sub> (DICE compound device identifier for Layer n) | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Die unique assets | IDevID<sub>Priv</sub> | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Die unique assets | LDevID<sub>Priv</sub> | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Die unique assets | Obfuscation key | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Die unique assets | AliasFMC_Key<sub>Priv</sub> | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Die unique assets | AliasRT_Key<sub>Priv</sub> | Confidentiality and integrity | Proficient | 1. Software reading actual secrets<br>2. Side channel attack to infer secret | 1. Secrets locked in key vault, not readable by software<br>2. SCA protections |
| Root of trust execution | ROM FW | Integrity | Proficient | Glitching | 1. Redundant decision making on critical code execution<br>2. Environmental monitoring and protection |
| Root of trust execution | Execution unauthorized runtime FW | Authenticity and integrity | Proficient | Modify boot media | Authenticity and integrity check using PKI DSA upon power on |
| Root of trust execution | Execution unauthorized runtime FW | Authenticity and integrity | Proficient | Arbitrary payload pushed into execution | Authenticity and integrity check using PKI DSA during software updates and power on |
| Root of trust execution | Rollback Attack | Versioning | Proficient | 1. Modify boot media to host older versions<br>2. Bypass version check during boot | 1. Authenticity and integrity check using PKI DSA upon power on<br>2. Failproof, audited boot code implementation responsible for loading images |
| Root of trust execution | Control flow | Integrity and confidentiality if applicable | Proficient | 1. Return and jump addresses manipulation<br>2. Return values and errors tampering <br>3. Stack overflow <br>4. Buffer overflows <br>5. Privilege escalations and hijacking | 1. Various control flow integrity measures<br> 2. Secure coding practices and auditing implementation |
| Boot measurements protected by Caliptra | Boot measurements that Caliptra gathers, stores, and reports | Integrity | Expert | 1. Manipulate measurements AiTM while in transit to Caliptra <br>2. SoC sends manipulated measurements to Caliptra |  |
| Caliptra inputs | Security state | Integrity | Proficient | Glitching | Environmental monitoring and protection |
| Caliptra inputs | Mode selection (Boot Media Integrated and dependent selections) | Integrity | Proficient | Glitching | Environmental monitoring and protection |
| Caliptra inputs | PAUSER attribute | Integrity | Proficient | Glitching | Environmental monitoring and protection |
| Caliptra inputs | JTAG debug | Integrity | Proficient | 1. Attempt to manipulate RoT execution via JTAG to flows that are not plan-of-record<br>2. Attempt to retrieve device secrets via JTAG when product is field-deployed<br>3. Attempt to retrieve device secrets via JTAG while the product is being developed and debugged | Implement security mode management within Caliptra |

# High level architecture

The following figure shows the basic high-level blocks of the Caliptra subsystem.

*Figure 2: Caliptra high level blocks*

![](./images/Caliptra_HW_diagram.png)

See the [HW Section](#hardware-section) for a detailed discussion.

## Caliptra profiles

Caliptra supports two physical modes of instantiation, the Caliptra Core and the Caliptra subsystem.  Within Caliptra Core there are two modes of integration with different security postures and firmware loading techniques.

1. Boot Media Integrated (BMI) profile: Caliptra loads its firmware directly from SPI boot media. SoC boot cannot proceed through any other boot media.
2. Boot Media Dependent (BMD) profile: Caliptra receives its firmware from SoC actors with access to the boot media.

In both profiles, Caliptra is among the first uncore microcontrollers taken out of reset by the power-on reset logic. The difference is in the Trusted Computing Base (TCB) for integrity of the Core RTM. In the BMI profile, this TCB is the Caliptra Core. In the BMD profile, this TCB additionally includes the immutable element of the SoC ROM. The BMD profile trades increased TCB for lower integration cost. The BMD profile does not put Caliptra firmware in the performance-critical or recovery-critical code paths of the SoC boot process.

Caliptra 1.0 only supports the BMD profile.

### <a id="bmi"></a>Caliptra Core - Boot Media Integrated (BMI)

In the BMI profile, Caliptra unilaterally starts the firmware chain-of-trust. The boot process is as follows:

1. Hardware executes SoC power-on reset logic. This logic starts the execution of Caliptra ROM.
2. Caliptra ROM fetches the Caliptra firmware from SPI boot media.
3. Caliptra ROM authenticates, measures, loads, and executes Caliptra firmware. Refer to [Error Reporting and Handling](#error-reporting-and-handling) for details regarding FMC verification failures.
4. Caliptra firmware copies the SoC First Mutable Code (FMC) into the Caliptra mailbox and measures it.
5. Caliptra firmware signals to SoC ROM to continue the boot process by fetching the firmware from Caliptra's mailbox.
6. SoC FMC continues the boot process, forming a boot firmware chain-of-trust: each firmware fetches, authenticates, measures, and executes the next firmware needed to establish the device operating environment. Each firmware deposits the next firmware's measurements into Caliptra prior to execution.
7. Caliptra firmware presents attestation APIs using the deposited measurements.

*Figure 3: Boot Media Integrated boot flow*

![](./images/BMI_Boot_flow.png)

In the BMI profile, the Caliptra TCB for integrity of Core RTM is the Caliptra Core.  The verification of measurement includes:

1. The SoC design ingests firmware through Caliptra.
2. Caliptra IP, Caliptra ROM, and Caliptra Firmware.

### <a id="bmd"></a>Caliptra Core - Boot Media Dependent (BMD)

In the BMD profile, Caliptra coordinates the start of the firmware chain-of-trust with the immutable component of the SoC ROM. After the Caliptra ROM completes initialization, it provides a "stash measurement" API and callback signals for the SoC ROM to proceed with the boot process. Caliptra ROM supports stashing of at most eight measurements prior to the boot of Caliptra firmware. The SoC then may choose to boot Caliptra firmware. Any security-sensitive code or configuration loaded by the SoC prior to Caliptra firmware boot must be stashed within Caliptra. If the SoC exceeds Caliptra ROM's measurement stash capacity, attestation must be disabled until next cold reset. The boot process is as follows:

1. Hardware executes SoC power-on reset logic. This logic starts the execution of SoC ROM and Caliptra ROM.
2. SoC ROM waits for the ready_for_fw signal from Caliptra ROM.
3. SoC ROM fetches the FMC.
    1. If the FMC is Caliptra firmware:
        1. SoC ROM loads the Caliptra firmware into the Caliptra mailbox and issues the Caliptra "firmware load" command.
        2. Caliptra ROM authenticates, measures, and starts the Caliptra firmware.
    2. If the FMC is not Caliptra firmware:
        1. SoC ROM authenticates and measures that firmware as the SoC FMC, and issues the Caliptra "stash measurement" command prior to executing SoC FMC.
4. SoC ROM executes SoC FMC.
5. As in #6 from the BMI flow, SoC FMC continues the boot process, forming a boot firmware chain-of-trust: each firmware fetches, authenticates, measures, and executes the next firmware needed to establish the device operating environment. Each firmware deposits the next firmware's measurements into Caliptra prior to execution. The exception is Caliptra's firmware: SoC firmware delegates the measurement and execution of Caliptra's firmware to Caliptra ROM.
6. Upon eventual initialization, Caliptra firmware presents attestation APIs using the deposited measurements.

See [Error Reporting and Handling](#error-reporting-and-handling) for details about Caliptra and SoC firmware load and verification error handling.

*Figure 4: Boot Media Dependent boot flow*

![](./images/BMD_Boot_flow.png)

## Caliptra security subsystem

To enable a transparent and reusable security subsystem, the Caliptra specification includes a full security subsystem solution. This solution is a combination of fully open source digital logic and licensable analog components that are technology dependent, such as TRNG analog sources or technology dependent fuse controllers.

* SoC Controller has configurable SRAMs to allow per SoC firmware customization.
* SoC reference ROM allows for configurable initialization.
* Resource handling logic (RHL) brings up subsystem components such as PUF, PLL, Fuse controller, \[P-\]TRNG. etc. RHL processes requests from Caliptra to the outside components (for example, P-TRNG request input to Caliptra’s internal TRNG).
* Some of the analog components are licensable IPs that are used to build the subsystem (for example, PUF, and PLL).

*Figure 5: Caliptra security subsystem*

![](./images/Caliptra_HW_Block_diagram.png)

The Caliptra subsystem offers a complete RoT subsystem, with open source programmable components for customization of SoC boot flows.

## Identity

Caliptra must provide its runtime code with a cryptographic identity in accordance with the TCG DICE specification. This identity must be rooted in ROM, and provides an attestation over the security state of the RTM as well as the code that the RTM booted.

*Figure 6: DICE Cert/Key generation*

![](./images/Caliptra_cert_creation.png)

### UDS

A combination of mask ROM and HW macros must implement the DICE key derivation and power-on latch, hiding the UDS and only making the CDI-derived signing key visible to firmware.

The Caliptra UDS is stored in fuses, and is encrypted at rest by an obfuscation secret[^2] known only to the Caliptra ROM. Once read by Caliptra ROM at boot, the UDS is then used to derive the IDevID identity.

### IDevID key

Caliptra's IDevID key is a hardware identity generated by Caliptra ROM during manufacturing. This key must be solely wielded by Caliptra ROM, and shall never be exposed externally at any phase of the Caliptra lifecycle. IDevID is used to endorse LDevID. The IDevID certificate is endorsed by the vendor’s provisioning CA (pCA) that is implemented via a HSM appliance connected to High Volume Manufacturing (HVM) flows (see provisioning CA in [Reference 8](#ref-8)).

See [Provisioning IDevID During Manufacturing](#provisioning-idevid-during-manufacturing) for further details on IDevID provisioning.

### LDevID key

Caliptra shall support field-programmable entropy, which factors into the device's LDevID identity.  The LDevID identity is endorsed by IDevID and in turn endorses the FMC alias key.

Caliptra's field-programmable entropy shall consist of four 32-byte slots. All slots are used to derive LDevID. An owner may decide to program as few or as many slots as they wish. Upon programming new entropy, on the next reset the device begins wielding its fresh LDevID. Owners need to validate the new LDevID by using IDevID.

### Commentary: threat analysis
An ideal IDevID has the following properties:
* Cannot be altered by entities besides Caliptra in manufacturing security state.
* Cannot be impersonated by entities that are not a Caliptra instatiation for that device class.
* Cannot be cloned to additional devices of the same class.
* Private component cannot be extracted from Caliptra.

Caliptra 1.0 alone does not fully address these properties. For example, a person-in-the-middle supply chain adversary could impersonate Caliptra by submitting its own IDevID Certificate Signing Request (CSR) to the pCA. Vendors should threat model the IDevID generation and endorsement flows for their SoC. Threat actors to consider are the following:
* Components involved in UDS injection flows: can they inject the same obfuscated UDS to multiple devices, or to devices of different classes? Can they wield the obfuscation key to leak the UDS?
* Components servicing the connectivity between the Caliptra instantiation and the HSM applicance performing IDevID endorsement: can they alter or impersonate Caliptra's IDevID CSR?
* Physical attackers: see [Physical Attack Countermeasures](#physical-attack-countermeasures).

Vendors have incentives to mitigate these threats. The vendor identity chain secures RMA and confidential computing workflows.

Ultimately though, IDevID is not renewable. Renewable security, often referred to as trusted computing base recovery, is a base design principle in Caliptra. Therefore, it is a design goal to reduce the operational dependency on IDevID. Field entropy and LDevID satisfy this need.

Field entropy is a limited resource, consisting of only four 32-byte slots of one-time programmable fuses. It is not generally expected that a second-hand purchaser can program all or even any of these slots. Caliptra's DICE identity remains usable even after all field entropy slots are programmed, so this feature does not preclude a circular economy. Field entropy is a feature primarily designed for users who purchase new parts.

Field entropy and LDevID are intended to hedge against attackers with the following abilities:

* Can obtain UDS before the part first arrives at the owner's facility.
* Can wield that stolen UDS to impersonate the part after it is deployed within the owner's facility. The attacker can derive and wield IDevID to mint an attacker-controlled DICE hierarchy; for example, LDevID, FMC alias key, or Runtime firmware alias key.
* Cannot fully impersonate the part during initial onboarding within the owner's facility.
* Cannot extract field entropy after initial onboarding.

During initial onboarding, the owner is expected to instruct the device to program field entropy. Upon device reset, this results in a fresh LDevID. Attackers that have previously obtained UDS are not able to derive this LDevID. The owner is expected to register the new LDevID and subsequently validate all future DICE keys for the device against that LDevID.

When registering LDevID during device onboarding, the owner is expected to rely on IDevID as an authenticity signal over LDevID. It is assumed that the attacker has obtained UDS at this point, and therefore can themselves wield IDevID. Therefore, the authenticity signal granted by IDevID cannot be the only signal used to determine LDevID's trustworthiness. The owner's device onboarding flow must be resistant to remote person-in-the-middle attackers that may attempt to use a previously exfiltrated UDS to register a forged LDevID.

After an owner registers a device's LDevID as part of their device onboarding flow, and unless the device again passes through the owner's device onboarding flow, the owner should not trust IDevID to endorse any other LDevIDs.

This approach does not defend against supply-chain attackers that obtain fuse data for devices that enter the supply chain *after* their field entropy has been programmed, such as during RMA flows. The LDevID certificate also does not support revocation because there is no generic Caliptra OCSP service. Owners should either maintain an allowlist of LDevID certificates or revoke any of the upstream certificate authorities.

Owners are not required to program field entropy. Caliptra generates LDevID from the value of the field entropy fuses, which could be all zeroes or ones. Caliptra LDevID derivation descends from UDS so that LDevID properties are no worse than IDevID. Field entropy is expected to be stored in fuses to achieve an equivalent physical attack barrier to UDS.

It is the responsibility of the owner or the user to identify the certificate they wish to trust, and to potentially endorse with their own certificate authority: pCA, IDevID, LDevID, or Alias<sub>FMC</sub>.

### FMC alias key

The LDevID CDI is mixed with a hash of FMC, as well as the security state of the device, via a FIPS-compliant HMAC, to produce CDI<sub>FMC</sub>. ROM uses CDI<sub>FMC</sub> to derive the Alias<sub>FMC</sub> keypair. ROM wields LDevID to issue a certificate for Alias. The Alias<sub>FMC</sub> certificate includes measurements of the security state and FMC. ROM makes CDI<sub>FMC</sub>, Alias<sub>FMC</sub>, and its certificate, available to FMC.

FMC wields Alias<sub>FMC</sub> to issue a CSR for Alias<sub>FMC</sub>. FMC then mixes CDI<sub>FMC</sub> with a hash of runtime firmware to produce CD<sub>RT</sub>. FMC uses CDI<sub>RT</sub> to derive the Alias<sub>RT</sub> alias keypair. FMC wields Alias<sub>FMC</sub> to issue a certificate for Alias<sub>RT</sub>. This alias certificate includes measurements of runtime firmware. FMC makes CDI<sub>RT</sub>, Alias<sub>RT</sub>, and its certificate, available to application firmware, while withholding CDI<sub>FMC</sub> and Alias<sub>FMC</sub>.

For owner certification flows, Caliptra only emits a CSR for Alias<sub>FMC</sub>.

### Security state

Devices may support features like debug unlock or JTAG. These features, when enabled, significantly alter the security state of the device. The configuration of these features shall be captured in the device's DICE identity. The security state shall be captured as an input to the FMC's CDI, and represented within the FMC's alias certificate.

### Owner authorization

Caliptra firmware shall be signed by the vendor. In addition, this firmware may also be signed by the owner when ownership control is enforced. If a second signature is present for ownership authorization, Caliptra must extract the owner's public key from the firmware image during cold boot, and latch the owner key into Caliptra's RAM for the remainder of its uptime[^3]. Caliptra then uses both the vendor key and owner key to verify hitless firmware updates.

Caliptra shall attest to the value of the owner key, enabling external verifiers to ensure that the correct owner key was provisioned into the device. To perform this attestation, Caliptra includes the owner key as an input to the FMC's CDI (as part of "other attributes" from Figure 6 above), and represents it within the FMC's alias certificate.

The SoC may support a fuse bank for representing the hash of the owner's public key. If the SoC reports this value to Caliptra, Caliptra refuses to boot firmware unless the firmware was dual-signed by the key reported by SoC ROM's fuse registers.

The owner key, when represented in fuses or in the FMC's alias certificate, is a SHA-384 hash of a structure that contains a list of owner public keys. This supports key rotation.

## Provisioning IDevID during manufacturing

![](./images/Caliptra_manuf_flow1.png)

*Figure 7: Device manufacturing identity flow*

1. High Volume Manufacturing (HVM) programs NIST compliant UDS into fuses using SoC-specific fuse programming flow. Note that this UDS goes through an obfuscation function within Caliptra IP.
2. SoC drives the security state, which indicates that it's a manufacturing flow. See [Caliptra Security States](#caliptra-security-states) for encodings.
3. SoC (using a GPIO pin or SoC ROM) drives BootFSMBrk (this is also used for debug cases). This can be driven at any time before cptra\_rst\_b is deasserted.
4. SoC follows the boot flow as defined in Caliptra IP HW boot flow to assert cptra\_pwrgood and deassert cptra\_rst\_b, followed by writing to the fuse registers.
5. HVM, through JTAG or using the Caliptra SoC interface, writes to “CPTRA\_DBG\_MANUF\_SERVICE\_REG”, requesting a CSR (see the [Caliptra ROM specification](https://github.com/chipsalliance/caliptra-sw/blob/main/rom/dev/README.md) for bit definitions).
6. HVM, through JTAG or using the Caliptra SoC interface, writes to “CPTRA\_BOOTFSM\_GO” to allow Caliptra’s internal BootFSM to continue to bring up microcontroller out of reset.
7. ROM looks at the manufacturing state encoding, “CPTRA\_DBG\_MANUF\_SERVICE\_REG”, and populates the Caliptra internal SRAM \[the mailbox SRAM hardware structure is reused\] with the CSR and CSR envelope signature. It then writes to the Caliptra internal register to indicate the CSR is valid (see the [Caliptra ROM specification](https://github.com/chipsalliance/caliptra-sw/blob/main/rom/dev/README.md) and [Identity](#identity) sections in this document on the ROM steps to generate the CSR).
8. HVM, through JTAG or using the SoC interface, polls for “requested service\[s\]” bit\[s\] available in “CPTRA\_BOOT\_STATUS” register.
9. HVM, through JTAG, reads mbox\_status\[3:0\] to check if the data is ready to be read (DATA\_READY encoding).
10. HVM must write a bit in CPTRA\_DBG\_MANUF\_SERVICE\_REG over JTAG, indicating that it completed reading the CSR.
11. Caliptra IP HW opens the Caliptra Mailbox for SoC usages, such as FW loading (if required in some HVM flows). Until this write operation is complete, the SoC does not get a grant/lock of the APB-exposed mailbox interface.

## Certificate format

Device identity certificates follow the X.509 v3 format described in RFC 5280.  The values in the X.509 certificate follow the DICE TCBInfo fields, as defined in [Reference 5](#ref-5). The owner public key is extended into VendorInfo, with the security operational state reflecting the flags of DICE TCBInfo.  Additional fields may be extended into VendorInfo.

## Caliptra security states

![](./images/Caliptra_security_states.png)

*Figure 8: Caliptra security states*

**Definitions**

* **Non-Debug:** Caliptra JTAG is not open for microcontroller and HW debug.
* **Debug:** Caliptra JTAG is open for microcontroller and HW debug.
* **Unprovisioned:** Blank/unprogrammed fuse part.
* **Manufacturing:** Device is in the manufacturing flow where HVM Caliptra fuses are programmed.
* **Production:** All of Caliptra’s HVM fuses are programmed.

**Notes:**

* Caliptra’s security state is determined by the SoC’s security state and the SoC device lifecycle state.
* Caliptra’s state is considered a mode of operation.
  * Caliptra security state is defined by the uppermost bit of the encoding below; 1=DebugLocked and 0=DebugUnlocked.
  * Lower 2 bits are mapped to device lifecycle (unprovisioned, manufacturing, production).
* SoC’s security state may also be influenced by its own device lifecycle. A HW state machine must drive the SoC security state.
* Caliptra’s security state determines Caliptra’s debug state and the state of its security assets.
* In general, if Caliptra is in an insecure state, all keys and assets are ‘zeroized’. Zeroized may mean switching to all 0s, 1s, or debug keys based on the key. See [Caliptra Assets](#assets) for information.

*Table 7: Security states*

|Security state, device lifecycle state [2:0]| State                         | Definition                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              | State transition requirement                                                |
|------------------------------------------------|-------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------- |
| 000b                                           | DebugUnlocked and unprovisioned | This is Caliptra’s default state; it is used for development and early Caliptra bring up. This state is not used to provision the Caliptra assets. In this state:<br> - UDS and all other identity critical assets shall not be programmed in fuses. Un-programmed fuse bits shall be read as 0s (zero). The debug UDS shall be obfuscated and de-obfuscated using the debug obfuscation key.<br> - Obfuscation key: The debug obfuscation key shall be used.<br> - Caliptra JTAG is unlocked and allows microcontroller debug.<br> - Caliptra JTAG can access IP internal registers through FW.                                                                                                                                                                                                                                                    | Unprovisioned to any other state requires a cold boot cycle of Caliptra and SoC. |
| 100b                                           | DebugLocked and manufacturing   | Caliptra is commanded to enter this state during the secure HVM process. In this state:<br> - UDS and other identity critical assets shall be programmed into fuses. They are written into Caliptra fuse registers, similar to the ‘Secure’ state.<br> - All security assets shall be in production mode (production UDS and obfuscation shall be used).<br> - Caliptra JTAG shall be locked; microcontroller debug shall be disabled.<br> - Caliptra microcontroller can be interrupted through JTAG mailbox.                                                                                                                                                                                                                                                                                                                                   | Manufacturing -> insecure state transition is possible without power cycle and Caliptra clears all of the security critical assets and registers before JTAG is opened.  Manufacturing -> secured state is possible ONLY with a power cycle. See [Provisioning During Manufacturing](#provisioning-idevid-during-manufacturing) for details. |
| 101b                                           | DebugLocked and production      | All security assets are in production mode. In this state:<br> - Production UDS and obfuscation key shall be used.<br> - CPU execution shall be enabled.<br> - All ‘backdoor’ functionality shall be disabled (for example, developer functions and functionality that could reveal sensitive information or result in escalation of privileges).<br> - Debug functions shall be disabled. Caliptra JTAG is locked – microcontroller debug shall be disabled. Caliptra microcontroller shall not be interruptible through JTAG mailbox.<br> - DFT functions shall be disabled.                                                                                                                                                                                                                                                                        | DebugLocked -> debug unlocked possible without power cycle and Caliptra clears all of the security critical assets and registers before JTAG is opened. |
| 001b                                           | DebugUnlocked and production    | This state is used when debugging of Caliptra is required. When in this state: UDS and other identity critical assets are programmed into fuses. They may not have been written into Caliptra fuse registers if the insecure state entered before Caliptra is out of reset. If the insecure state transition happened after fuses are written to Caliptra, they are cleared when the security state transitions from secure/manufacturing -> insecure.<br> Caliptra state: All security assets are in debug mode (UDS and obfuscation key are in production state).<br> - UDS: Reverts to a ‘well-known’ debug value.<br> - Obfuscation key: Switched to debug key.<br> - Key Vault is also cleared.<br> - Caliptra JTAG is unlocked and allows microcontroller debug.<br> - Caliptra JTAG can access IP internal registers through FW or directly. | Debug unlocked -> debug locked is possible ONLY with a power cycle.            |

**Notes:**
* End-of-life state is owned by SoC. In end-of-life device lifecycle state, Caliptra shall not not be brought out of reset.
* Other encodings are reserved and always assumed to be in a secure state.

Each of these security states may be mapped to different SoC level debug and security states. SoC’s requirement is that if the SoC enters a debug state, then Caliptra must also be in an unsecured state where all assets are cleared.

## Service surface

The service surface of Caliptra has multiple vectors. All use cases are control plane services, useful to power on a system or start a task. Supporting line rate high performance IO cryptography or any other data path capability is not required.

* **Logic IOs:** Required to indicate status of the IP, availability of a message through APB, and to enable or disable certain debug capabilities (like JTAG enable or disable).
* **Command mailbox**: Caliptra shall offer services to other parts of the SoC. The APIs are documented in the [Caliptra Runtime specification](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md) and summarized below:
  * **Loading firmware**: Caliptra firmware is loaded via the mailbox at cold boot. In addition, Caliptra firmware can be loaded at runtime to support hitless or impactless updates.
  * **DICE-as-a-Service**: Caliptra shall expose the TCG DICE Protection Environment iRoT Profile API, allowing Caliptra to derive and wield a DICE identity on behalf of other elements within the SoC. For example, Caliptra can sign messages for an SPDM responder.
  * **Measurement Vault**: Caliptra shall support stashing of measurements for the code and configuration of the SoC. Caliptra can provide these measurements via PCR Quote API or via DPE.
  * **FW Authentication**: Caliptra supports ECDSA verification for SoC firmware beyond its own. The SHA384 block exposes a HW API for hashing firmware. The runtime firmware exposes an ECDSA verification API that uses the hash computed by the SHA384 block.

## Device resilience

As noted earlier, Caliptra plays a role in maintaining the resilience posture of the SoC as defined by NIST SP 800-193 Platform Firmware Resiliency Guidelines (see [Reference 1](#ref-1)). As the Silicon RTM, Caliptra is either responsible for, or participates in, various protection and detection requirements described in the NIST publication.

The following table describes the NIST SP 800-193 requirements that Caliptra shall meet, either on its own or in conjunction with other components within the SoC or platform. Requirements not listed are assumed to be not covered and out-of-scope for Caliptra. In particular, most requirements related to firmware update and recovery are out-of-scope and must be handled by other components of the system.

*Table 8: NIST SP 800-193 requirements*

| NIST SP 800-193 Chapter | Requirement | Caliptra responsibility |
| :---------------------- | :---------- | :---------------------- |
| 4.1.1 | All security mechanisms and functions shall be founded to Roots of Trust (RoT). | Caliptra forms the basis for all trust in the SoC starting from execution of its immutable ROM. See the [Secure Boot Flow](#secure-boot-flow) section. |
| 4.1.1 | If Chains of Trust (CoT) are used, RoT shall serve as the anchor for the CoT. | All other firmware shall be authenticated and executed as part of a Chain of Trust extended from the Caliptra ROM. See the [Secure Boot Flow](#secure-boot-flow) section. |
| 4.1.1 | All RoTs and CoTs shall either be immutable or protected using mechanisms that ensure all RoTs and CoTs remain in a state of integrity. | All other firmware is authenticated and executed as part of a Chain of Trust extended from the Caliptra ROM. See the [Secure Boot Flow](#secure-boot-flow) section. |
| 4.1.1 | All elements of the CoT for update, detection, and recovery in non-volatile storage shall be implemented in platform firmware. | Caliptra forms the basis for RTM (or detection). All other silicon RoT capabilities are extended by additional firmware loaded in the SoC and anchored by Caliptra. |
| 4.1.1 | The functions of the RoTs or CoTs shall be resistant to any tampering attempted by software running under, or as part of, the operating system on the host processor. | Caliptra shall run on a dedicated microcontroller, isolated physically from access by other components in the system. |
| 4.1.1 | Information transferred from the software on the host processor to the platform firmware shall be treated as untrusted. | Caliptra shall verify the authenticity of its firmware using an approved digital signature verification mechanism. |
| 4.1.1 | CoTs may be extended to include elements that are not from non-volatile storage. Before use, those elements shall be cryptographically verified by an earlier element of the CoT. | Caliptra shall verify the authenticity of its firmware using an approved digital signature verification mechanism. Caliptra shall also measure the SoC security processor FMC code before it is verified and executed by the SoC. |
| 4.1.2 | If the key store is updateable, then the key store shall be updated using an authenticated update mechanism, absent unambiguous physical presence through a secure local update. | Hashes for the keys used to authenticate Caliptra FW are programmed into fuses during manufacturing. If a key is deemed to be compromised, that key may be revoked and the next key used instead. |
| 4.1.3 | Each platform device that implements a detection capability shall rely on either a Root of Trust for Detection (RTD), or a Chain of Trust for Detection (CTD). The CTD is anchored by an RTD for its detection. | Caliptra forms the basis for all trust in the SoC starting from execution of its immutable ROM. All other firmware shall be authenticated and executed as part of a CoT extended from the Caliptra ROM. See the [Secure Boot Flow](#secure-boot-flow) section. |
| 4.1.3 | The RTD or CTD shall include or have access to information necessary to detect corruption of firmware code and critical data. | Caliptra relies on hashes of authorized keys stored in fuses. Those hashes are then checked against public keys found in firmware headers to authenticate Caliptra’s runtime firmware. Caliptra relies on redundancy in the fuses to protect the key and configuration data. |
| 4.2.3 | If critical platform firmware code in non-volatile memory is copied into RAM to be executed (for performance, or for other reasons) then the firmware program in RAM shall be protected from modification by software or shall complete its function before software starts. | Caliptra shall run on a dedicated microcontroller, isolated physically from access by other components in the system. |
| 4.2.3 | If critical platform firmware uses RAM for temporary data storage, then this memory shall be protected from software running on the platform until the data’s use is complete. | Caliptra shall run on a dedicated microcontroller, isolated physically from access by other components in the system. |
| 4.2.3 | Software shall not be able to interfere with the intended function of critical platform firmware. For example, by denying execution, modifying the processor mode, or polluting caches. | Caliptra shall run on a dedicated microcontroller, isolated physically from access by other components in the system. In addition, the Caliptra subsystem begins execution before other firmware is allowed to run. |
| 4.2.4 | Critical data shall be modifiable only through the device itself or defined interfaces provided by device firmware. Examples of defined interfaces include proprietary or public application programming interfaces (APIs) used by the device’s firmware, or standards-based interfaces. Symbiont devices may rely on their host devices to meet this requirement. | Caliptra receives firmware and configuration input only via defined interfaces within the SoC. See the [Mailbox](#mailbox) section. |
| 4.2.1.3 | The authenticated update mechanism shall be capable of preventing unauthorized updates of the device firmware to an earlier authentic version that has a security weakness or would enable updates to a version with a known security weakness. | Caliptra supports a mechanism for detecting and preventing execution of a prior firmware image that is no longer authorized. See the [Anti-rollback Support](#anti-rollback-support) section. |
| 4.3.1 | A successful attack that corrupts the active critical data or the firmware image, or subverts their protection mechanisms, shall not in and of itself result in a successful attack on the RTD or the information necessary to detect corruption of the firmware image. | Caliptra shall verify the signature of any firmware it loads during each boot. If the signature verification fails, Caliptra shall notify the SoC that firmware recovery must be performed. See the [Error Reporting and Handling](#error-reporting-and-handling) section. |
| 4.3.1 | Verify integrity, using an approved digital signature algorithm or cryptographic hash, of device firmware code prior to execution of code outside the RTD. | Caliptra shall perform digital signature verification of its FMC code, as well as that of the SoC security processor FMC, before they are allowed to execute. |
| 4.3.1 | If firmware corruption is detected, the RTD or CTD should be capable of starting a recovery process to restore the device firmware code back to an authentic version. | Caliptra shall notify the SoC via the Mailbox interface to initiate the recovery process. |
| 4.3.1 | The detection mechanism should be capable of creating notifications of firmware corruption. | Caliptra shall notify the SoC via the Mailbox interface to initiate the recovery process. |
| 4.3.1 | The detection mechanism should be capable of logging events when firmware corruption is detected. | It is the responsibility of the SoC to log any corruption events upon notification by Caliptra. |
| 4.3.2 | The RTD or CTD shall perform integrity checks on the critical data prior to use. Integrity checks may take the form, for example, of validating the data against known valid values or verifying the hash of the data storage. | Caliptra relies on redundant fuses to store its configuration data, which is owned and passed to Caliptra through the Mailbox. |
| 4.3.2 | The RTD or CTD should be capable of creating notifications of data corruption. | See the [Error Reporting and Handling](#error-reporting-and-handling) section. |
| 4.3.2 | The detection mechanism should be capable of logging events when data corruption is detected. | It is the responsibility of the SoC to log any corruption events upon notification by Caliptra. |

## Secure boot flow

Caliptra shall follow and implement the secure boot guidelines as described in [Reference 3](#ref-3).

For the detailed flow, see the [HW Section](#hardware-section).

## Hitless update

A ‘hitless’ (aka ‘impactless’) update occurs when an update is applied to Caliptra’s executing firmware without requiring a SoC or machine reboot. A hitless update allows Caliptra FW[^4] to remain up to date with FW security and/or functional patches while preventing or reducing machine downtime. Hitless update shall take effect immediately upon application (post-cryptographic verification). Updates to the machine’s persistent storage are still required because they ensure that Caliptra reboots to the latest FW if the system requires a restart or reboot.

Caliptra contains multiple hardware isolated registers for Platform Configuration Registers (PCR). These PCRs serve as volatile storage for concise cryptographic measurement of security state, including Caliptra’s own firmware.

Journey measurements matter because hitless updates are a challenge for devices that only capture their current firmware version and state. This is particularly true when the previous state may have impacted the current state of dependent components within the SoC. For example, a device might move from firmware version A to firmware version B without assuming a clean start to flush state. Vulnerabilities in firmware version A might impact version B.  Preserving a device boot measurement and currently running measurement can highlight differences, but preserving these measurements does not distinguish between transitional states, such as when intermediate updates have the potential to expose the device to vulnerabilities. For example, a device may move from firmware version A, to B, and then to C without a restart, whereas another device of the same type might transition from A to C without transitioning through B. If tracking only the boot and current firmware version, should a vulnerability be found in version B, it is impossible to identify which devices transitioned through B compared to devices that transitioned from A to C directly.

To capture all firmware and configuration changes, Caliptra tracks and attests to both current measurements and cumulative measurement PCR banks. The current measurement is a snapshot of the currently running firmware and configuration. This provides easy reference for the current version. If the current and cumulative measurements are different, it can safely be assumed that the device has undergone some update. The cumulative measurement captures all of the firmware and state transitions from a clean cold boot to the current version. The cumulative measurement must be accompanied by a log structure that describes the path from boot to current measurement using hash extensions. A verifier can understand a device’s path to its current state by replaying log entries to reconstruct the cumulative measurement.

The log and cumulative measurement mechanism is similar to that used in TPM. In this model, Caliptra only needs to securely manage the measurements; the log does not need to be secured or maintained by Caliptra or the SoC. The construction of measurements through cryptographic hash extensions means that the log must provide the exact order and evidence needed to reconstruct the measurement. As such, the log is tamper evident by design and does not need to be kept secure.

Caliptra contains 32 384-bit PCR banks that are extendable by the SHA engine, and readable by Caliptra firmware.  The usage of the PCR banks is as follows:

*Table 9: PCR bank usage*

|**PCR number**|**Type**|**Extend control**|**Description**|
| - | - | - | - |
|PCR0|Current|ROM|Holds Caliptra’s FMC measurement and ROM policy configuration.|
|PCR1|Cumulative|ROM|Holds journey of Caliptra’s FMC measurement and ROM policy configuration.|
|PCR2|Current|FMC|Holds Caliptra's runtime firmware and firmware manifest measurements.|
|PCR3|Cumulative|FMC|Holds journey of Caliptra's runtime firmware and firmware manifest measurements.|
|PCR4 to PCR30|-|RT|Holds measurements extended by EXTEND_PCR commands (serviced by RT).|
|PCR31|Cumulative|ROM|Holds measurements extended by STASH_MEASUREMENTS commands (serviced by both ROM and RT).|

### Attestation of Caliptra's update journey

Upon every cold boot and hitless update, Caliptra ROM extends Caliptra's FMC measurement and ROM policy configuration into PCR0 (current) and PCR1 (cumulative).  Upon every cold boot and hitless update, Caliptra FMC extends Caliptra's runtime firmware and firmware manifest measurements into PCR2 (current) and PCR3 (cumulative). The current measurement of the FMC, ROM policy configuration, RT, and FW manifest are used to derive a CDI and an alias key given to runtime firmware. FMC places runtime firmware's measurements into runtime firmware's alias key certificate, and signs that certificate with FMC's alias key.

When runtime firmware boots following a hitless update, it will use the following pieces of data for building the DPE nodes and certificate chain:

* Its CDI, derived by FMC
* Its alias key, generated by FMC
* Its alias certificate, signed by FMC
* Its journey measurements in PCR3, extended by FMC
* SRAM state, established by the prior runtime firmware image

SRAM state consists of measurements captured by prior runtime firmware images, and does not contain secrets or executable data[^5]. Therefore, the trustworthiness of runtime firmware is reflected in the measurements captured by FMC and is evident in the runtime firmware alias certificate.

Caliptra firmware will attest to PCR3 by including it as an input in all DPE leaf key derivations and as evidence in all DPE leaf key certificates.

#### Commentary: recovery from a bad hitless update

Suppose the following Caliptra firmware images exist:

* Version A: presumed-good
* Version B: known-bad
* Version C: presumed-good

A remote verifier wishes to confirm that a given Caliptra device has not run version B since cold boot. The remote verifier can challenge the SoC with a freshness nonce; higher-layer software passes that freshness nonce as a request to Caliptra's DPE for signing. The remote verifier receives the following pieces of evidence:

1. An endorsement over LDevID, which may take a number of forms, including:
    1. Caliptra's vendor-signed certificate over IDevID, and an IDevID-signed certificate over LDevID.
    2. An owner-signed certificate over IDevID, and an IDevID-signed certificate over LDevID.
    3. An owner-signed certificate over LDevID.
2. An LDevID-signed certificate over Alias<sub>FMC</sub>, which includes FMC's measurements as captured by ROM.
3. An Alias<sub>FMC</sub>-signed certificate over Alias<sub>RT</sub>, which includes runtime firmware's measurements as captured by FMC.
4. An Alias<sub>RT</sub>-signed certificate over a leaf DPE key, which includes PCR3 as read by runtime firmware, along with other measurements previously stashed in SRAM.
5. A log structure[^6] that represents the measurements that have been extended into PCR3.
6. A leaf-DPE-signed blob[^7] containing the freshness nonce.

The remote verifier evaluates (1) according to ownership policies to determine whether the Caliptra device is trustworthy, before proceeding to verify the rest of the attestation response.

Thus satisfied in the trustworthiness of the Caliptra device, the remote verifier can then evaluate the trustworthiness of FMC by inspecting the measurements in (2), Alias<sub>FMC</sub>'s certificate. The verifier can reject the attestation if those measurements do not conform to a known-good value.

Thus satisfied in the trustworthiness of FMC, the remote verifier can then evaluate the trustworthiness of runtime firmware by inspecting the measurements in (3), Alias<sub>RT</sub>'s certificate. If version A or C is running, then the PCR3 measurement present in (4), the leaf DPE key certificate, is presumed to be an honest reflection of the hardware register as read by runtime firmware. The verifier can reject the attestation if Alias<sub>RT</sub>'s certificate indicates that version B is currently running.

Thus satisfied that version B is not currently running and that PCR3 is an accurate reflection of the hardware register, the remote verifier can then compare the log in (5) to PCR3 in (4) to confirm its authenticity, then walk the log to confirm that FMC never launched version B since cold-boot. If version B did run, that firmware could have maliciously modified DPE measurements stashed in SRAM, but could not have modified the contents of PCR3 to erase the evidence that version B ran at all, and could not have influenced the behavior of firmware versions A or C to prevent them from accurately reporting the contents of PCR3.

Thus satisfied that version B has not run since power-on, the verifier can also optionally inspect other measurements in (4) to evaluate the journey of other SoC components, whose measurements were previously stored within Caliptra's SRAM.

Finally, the verifier can confirm freshness by comparing the nonce in (6) to the one emitted in the original challenge. Because DPE only allows a derived leaf key to be used if the measurements present in its leaf certificate are a reflection of the current state, the fact that the freshness nonce was signed by DPE is evidence that the measurements in (4) are fresh.

#### Commentary: maintaining sealed secrets across a power cycle

Caliptra does not seal secrets directly. However, Caliptra does implement DPE, which allows secrets to be sealed to an external sealer such as a TPM, with a policy that only allows those secrets to be unsealed if Caliptra allows the host to wield a particular leaf DPE key. This leaf DPE key is permuted based on the hitless update journey of the various components whose measurements are stored within Caliptra.

This poses a challenge for maintaining sealed secrets across a power cycle. Suppose the SoC cold booted CPU microcode A, then hitlessly updated to B, and then to C. The measurements stored within Caliptra's SRAM will represent the \[A->B->C\] update journey, and DPE's leaf key is derived based on this journey.

Let us assume that upon each hitless update, the firmware update is also written to persistent storage, such that on the next cold boot the new firmware will run. Thus, on the next boot, the SoC's microcode update journey is simply \[C\]. This is a different journey than \[A->B->C\], and so DPE's leaf key will differ. The old secret sealed to the old DPE leaf key is no longer accessible to the SoC.

To anticipate this eventuality, before a power cycle, the SoC can instruct DPE to predict what the DPE leaf public key will be if the microcode journey is simply \[C\], using DPE's simulation context. The SoC can then reseal secrets to the external sealer with a policy that can be satisfied if the computed public key is used.

Note: as all DPE leaf keys are derived using Caliptra runtime firmware's CDI, a DPE simulation context cannot predict the leaf key that would be available if a different Caliptra firmware image were to boot (because one Caliptra firmware image does not have access to a different image's CDI). Therefore, if a different Caliptra firmware image is staged to persistent storage, Caliptra must first be hitlessly updated to that image before a simulation context can be used to predict public keys that will be available to that image on the next cold boot.

### Attestation of SoC update journey

Caliptra shall also attest to the journeys of SoC components. A SoC component's journey may change independently of other components. For example, SoC components may implement partial resets or hitless updates that cause the component's firmware or configuration to reload.

Caliptra shall maintain a reboot counter for each component. Caliptra shall increment the reboot counter and update the journey measurement for calls that indicate that the component's state changed. Caliptra shall attest the journey measurement and report the counter value on-demand. The verifier is assumed to have knowledge of update events at an associated reboot counter (via an event log) but not have knowledge of reset events. The verifier can compute the journey measurement via multiplicatively extending the current measurement by the reset counter. For example:

1. Upon cold boot, SoC component boots firmware A. Reboot counter is 0. The tuple of (0,A) is in the event log.
2. SoC component is partial reset once. Reboot counter is 1.
3. SoC component is hitlessly updated to firmware B. Reboot counter is 2. The tuple of (2,B) is in the event log.
4. SoC component is partial reset twice. Reboot counter is 4.

The corresponding journey measurement computation is the chained extension of \[A->A->B->B->B\]. The verifier can ascertain this through the two event log entries.

## Anti-rollback support

Caliptra shall provide fuse banks (refer to *Table 12: Caliptra Fuse Map*) that are used for storing monotonic counters to provide anti-rollback enforcement for Caliptra mutable firmware. Each distinctly signed boot stage shall be associated with its own anti-rollback fuse field. Together with the vendor, Caliptra allows owners to enforce strong anti-rollback requirements, in addition to supporting rollback to a previous firmware version. This is a critical capability for hyper scalar owners.

Every mutable Caliptra boot layer shall include a SVN value in the signed header. If a layer's signed SVN value is less than the current counter value for that layer's fuse bank, Caliptra shall refuse to boot that layer, regardless of whether the signature is valid.

Each signed boot layer shall also include a MIN\_SVN value in the signed header. Upon successful validation of a signed boot layer, if the layer's signed MIN\_SVN value is greater than the current counter value for that layer's fuse bank, Caliptra shall increment that fuse bank counter until it equals MIN\_SVN.

Vendors shall issue security critical fixes requiring anti-rollback protection in sets of two signed firmware:

* Version number (X+1), which carries the security fix, with an incremented SVN and an unchanged MIN\_SVN, as compared to version (X).
* Version number (X+2), identical to (X+1), except its MIN\_SVN value has been incremented.

Owners may upgrade their fleet in two stages: first from (X) to (X+1), and then from (X+1) to (X+2).

If an owner does not require the ability to roll back during qualification, they can choose to perform a single upgrade of their fleet, from (X) to (X+2), skipping over the intermediate (X+1).

Each of Caliptra's internal anti-rollback fuse banks shall support a minimum counter value of 64. This feature is expected to be used sparingly.

If a given firmware image's SVN is less than its MIN\_SVN value, that image shall be considered invalid.

Alternatively, platform vendors may prefer to manage firmware storage and rollback protection in a different manner, such as through a dedicated Platform RoT. In such cases, the vendor may wish to disable anti-rollback support from Caliptra entirely. This disable support is available via an OTP/fuse setting.

**Informative comment: Example**

The following is an example of how the anti-rollback mechanism may be used to revoke a signed image while supporting rollback to the prior image. Assuming Caliptra is in the following state:

* Currently running firmware version: 4.2
* Caliptra firmware's signed SVN value: 1
* Caliptra firmware's signed MIN\_SVN value: 1
* Caliptra's firmware anti-rollback fuse bank counter value: 1

A vulnerability is discovered in firmware version 4.2. The vendor issues a fix in firmware version 4.3. However, owners may still wish to roll back to firmware version 4.2, while version 4.3 is being qualified in their fleet. Updating to firmware version 4.3 places Caliptra in the following state:

* Currently running firmware version: 4.3
* Caliptra firmware's signed SVN value: 2
* Caliptra firmware's signed MIN\_SVN value: 1
* Caliptra's firmware anti-rollback fuse bank counter value: 1

In this state, since the anti-rollback fuse bank counter is not yet incremented, Caliptra still allows the firmware to roll back to version 4.2.

After firmware version 4.3 is fully qualified, the owner wishes to revoke version 4.2. The vendor issues a follow-up firmware version 4.4, which places Caliptra in the following state:

* Currently running firmware version: 4.4
* Caliptra firmware's signed SVN value: 2
* Caliptra firmware's signed MIN\_SVN value: 2
* Caliptra's firmware anti-rollback fuse bank counter value: 2

Upon validating firmware version 4.4, Caliptra notes that that firmware's signed MIN\_SVN value is 2, and increments its internal fuse bank counter to match. After a chip receives firmware version 4.4, it is no longer able to roll back to version 4.2. However, it *will* continue to be able to roll back to version 4.3.

## Physical attack countermeasures

Caliptra shall implement countermeasures designed to deter both glitching (also referred to fault-injection (FI)) and side-channel attacks (simple power analysis (SPA) and differential power analysis (DPA)).

The Caliptra threat model guides the priority of which physical countermeasures are based on a specific physical implementation.

From the top, an adversary in the supply chain has essentially unlimited time to glitch the chip and make it reveal any private key material or symmetric secrets. [One Glitch To Rule Them All](https://arxiv.org/abs/2108.04575) is one example with recency bias. The most critical countermeasures must prevent non-destructive extraction of those secrets. Otherwise, an adversary who succeeds can silently impersonate production-serving assets at a later time.

Randomly generated per-part entropy is subject to physical inspection attacks in the supply chain as well. The fuses that store the UDS entropy shall be protected to a degree that forces an attacker to perform a destructive operation to read their values. Decapping and fibbing attacks should at least penetrate enough layers and metal shielding to render the part useless, if not being outright impossible to carry out. Entropy tied to a damaged asset typically requires injection of counterfeit devices in the supply chain, which is a very powerful adversary model.

Another way to obtain access to secret entropy with “unlimited supply chain time” is to observe side channels while the SoC is executing. Because Caliptra is expected to be a <1 mm<sup>2</sup> fraction of a large SoC, side-channel mitigation is required only against extremely resourceful attackers that can wade through and discern a large number of confounding signals and power profiles. With that priority in mind, DPA and DMA attacks should be mitigated via decoy value generation.

Any private key material or symmetric key material embedded in the RTL (and therefore “global”) must be treated as having low value, reaching zero value in a number of quarters. A supply chain attacker can destructively obtain the key material, and loss of one part is not going to trigger any alarms.

Mitigation against SCA is not trivial and may be implemented in a variety of ways. [Reference 7](#ref-7) provides a comprehensive overview of methods and techniques used in various SCA as well as recommendations for countermeasures against such attacks (including feasibility and applicability). Additionally, there are academic papers available from NIST and other resources that discuss SCA and their countermeasures.

## Compliance and certification requirements

Due to the identity service surface offered to other SoC subsystems, Caliptra may fall under the Target of Evaluation (ToE) of an application that wishes to attain a specific compliance level for business reasons.

It is important to highlight that it’s not necessary for the RTM itself to unilaterally attain (for example, FIPS 140-3 L3). It is only relevant when the RTM is included in the “bag” that wants to obtain a compliance certification. For example, it is relevant when a cloud provider wants to FIPS-certify PCIe link encryption in transit rooted to an ASIC identity emanating from a Caliptra instance.

See [Reference 8](#ref-8) for requirements related to keys, entropy, random bits, cryptographic modules, and algorithms.

### Known Answer Test (KAT) support

To certify a cryptographic module, pre-operational self-tests must be performed when the system is booted. Implementing KATs is required for FIPS certification. However, regardless of FIPS certification, it is considered a security best practice to ensure that the supported cryptographic algorithms are functioning properly to guarantee correct security posture.

KAT execution is described as two types:

* Pre-operational Self-Test (POST)
* Conditional Algorithm Self-Test (CAST)

A detailed description of the POST and CAST KATs can be found at csrc.nist.gov.

*Table 10: KAT failure mitigations*

|KAT type|If fails|
| - | - |
|POST|Failure of a POST KAT (for example, ECDSA) shall result in Caliptra ***boot failure***. A reset may or may not result in successful POST completion.|
|CAST|Failure of a CAST KAT shall cause Caliptra to fail any operation that has a dependency on the associated cryptographic algorithm.|

*Table 11: POST/CAST usage*

| **Crypto algorithm** | **Caliptra Boot ROM** | **Caliptra FMC** | **Caliptra Runtime FW**
| -------------------- | --------------------- | ---------------- | -----------------------
| ECDSA[^8]            | Yes                   | Yes              | Yes
| AES                  | Yes                   | No               | No
| SHA[^9]              | Yes                   | Yes              | Yes
| DRBG                 | No                    | No               | No
| HMAC                 | Yes (CDI generation)  | No               | No
| KDF                  | Yes                   | Yes              | No

As shown in *Table 11: POST/CAST usage*, since the cryptographic algorithms required by the Caliptra Boot ROM are considered POSTs, and those same algorithms are used by Caliptra FMC and FW, there is no requirement that FMC and Runtime FW implement CASTs for those algorithms.

## FW Signing/Verification algorithms

Caliptra firmware is composed of multiple layers: an FMC and an application firmware image. Each layer is signed individually by ECDSA P384 keys.

Each layer is signed by a vendor-controlled key. In addition, each layer may also be signed by an owner-controlled key. The image header contains both the owner public key and the signature using that key.

During boot, Caliptra ROM shall verify the vendor signature over FMC before allowing that FMC to run.

See the [Owner authorization](#owner-authorization) section for how the owner key is used.

Caliptra's FW signature generation and verification shall follow the requirements described in [Reference 3](#ref-3).

### Post-Quantum Cryptography (PQC) requirements

As NIST publishes new standards with PQC resilience, algorithms applicable to Caliptra will be described in this document.

### Key rotation

Firmware signing key rotation shall follow the requirements described in [Reference 3](#ref-3).

# Hardware

The following figure describes the Caliptra Core.

*Figure 9: Caliptra Core block diagram*

![](./images/Caliptra_HW_diagram.png)

* SRAM requirements:
  * 128 KiB of ICCM0
  * 128 KiB for Mailbox as a staged SRAM (for FW staging of impactless updates to do authentication checks on the FW before moving to ICCM)
  * 128 KiB for DCCM and 32 KiB for ROM
* Cryptography requirements:
  * SHA256 SHA384, SHA512
  * ECC Secp384r1 w/ HMAC-DRBG - Key Generation, Sign and Verification
  * HMAC SHA384
  * AES256-ECB, CBC, GCM
* Chips Alliance is used for RISC-V.
* APB is the choice for the SoC-facing interface.
* JTAG is exported at the IP interface.
* TRNG is the digital logic and algorithms that are required for random number generation. It requires a physical entropy source input. See the Caliptra IP specification and integration specification for more information.
  * For SoCs that want to use their own legacy TRNG, Caliptra provides a HW API to push the random number on the request/response handshake. See the Caliptra IP specification and integration specification for more information.

The following figure describes the Caliptra IP HW boot flow.

*Figure 10: Hardware boot flow*

![](./images/Caliptra_boot_flow2.png)

1. As part of the SoC boot flow, SoC may have other infrastructure and entities that boot. That part of the flow is outside the scope of this document. If SoC chooses to bypass Caliptra, then it should have a capability to bypass Caliptra entirely through its proprietary flow. This may be needed for initial power-on and other early validation.
2. Cptra\_pwrgood is asserted to the Caliptra IP block.
3. Cptra\_rst\_b is deasserted to the Caliptra IP block. See the integration specification for guidelines on the minimum number of cycles between these two signals.
4. Caliptra IP now evaluates the strap settings driven through various interface wires (for example, BMD vs BMI mode, the security or debug state of the SoC, etc.).
5. If SoC is in a debug mode, then security assets are cleared or switched to debug mode.
6. Caliptra IP asserts Ready\_For\_Fuse wire to the SoC.
7. The SoC populates the fuse registers, the internal TRNG configuration registers, and the ROM WDT cycle count, then sets the CPTRA\_FUSE\_WR\_DONE bit. Note that Caliptra HW drops writes to any registers that cannot be changed unless there is a power cycle (for example, UDS). So SoC is free to write all the registers.
8. Caliptra IP deasserts Ready\_for\_Fuse wire as soon as the fuse write done register is written.
9. Caliptra IP moves security critical assets in fuse registers (for example, UDS) to the key vault.

## Boot Media Dependent flows

### Caliptra FW push flow

*Figure 11: FW push flow*

![](./images/Caliptra_boot_flow3.png)

1. After the Caliptra microcontroller is out of reset, ROM starts executing and triggers the crypto block to run the UDS decrypt flow.
2. Caliptra ROM enables the mailbox. (Until this point, any accidental or non-accidental writes that target the mailbox are dropped by the hardware.)
3. Caliptra ROM asserts READY\_FOR\_FW wire. This is done by writing an internal register. This register is also visible to read on the APB interface. SoC can choose to poll on this bit instead of using the wire (it is the SoC integration choice).
4. SoC follows the mailbox protocol and pushes Caliptra FW into the mailbox.
5. Caliptra’s mailbox HW  asserts an interrupt to the microcontroller after the GO is written, per mailbox protocol. See [Mailbox](#mailbox) for specifics.
6. After Caliptra’s FW is authenticated and loaded into ICCM, microcontroller asserts READY\_FOR\_RTFLOWS wire. See the [Caliptra ROM specification](https://github.com/chipsalliance/caliptra-sw/blob/main/rom/dev/README.md) for specific information on security flows that occur within this step (for example, DICE).

## Boot Media Integrated

### Caliptra FW load flow

*Figure 12: FW load flow*

![](./images/Caliptra_boot_flow4.png)

1. After the Caliptra microcontroller is out of reset, ROM starts executing and triggers the crypto block to run the UDS decrypt flow.
2. Caliptra ROM uses the internal SPI peripheral to read from the platform's persistent storage and load the FW. Note that SPI is operating in basic functional single-IO mode and at 20 MHz frequency.
3. After Caliptra’s FW is authenticated and loaded into ICCM, microcontroller asserts READY\_FOR\_RTFLOWS wire. See the [Caliptra ROM specification](https://github.com/chipsalliance/caliptra-sw/blob/main/rom/dev/README.md) for specific information about security flows that happen within this step (for example, DICE).

### <a id="reset-flow"></a>CPU warm reset or PCIe hot reset flow →  Caliptra IP reset

*Figure 13: Hardware reset flow*

![](./images/Caliptra_boot_flow5.png)

**Note:** Since Caliptra IP may be placed in an ACPI S5 domain of the device, there may be devices where Caliptra IP may not go through reset on a device hot reset or CPU warm reset. But the flow shows what happens when such a reset happens.

1. Caliptra IP’s reset is asserted by the SoC.
2. Caliptra’s internal BootFSM resets the microcontroller and then resets all of the logic (including the SoC-facing APB interface). Only registers or flops that are sitting on powergood are left with the same value. Note that SRAMs do not have a reset.
3. Caliptra IP’s reset is deasserted by the SoC.
4. At this point, the HW boot flow is the same as the cold boot flow. SoC is required to configure the internal TRNG and ROM WDT and then set CPTRA\_FUSE\_WR\_DONE. This causes Caliptra IP to deassert the Ready\_for\_Fuse wire.
5. Caliptra’s ROM reads an internal register to differentiate between warm, cold, and impactless flow. If it's a warm reset flow, then it skips DICE key generation and FW load flows (because keys were already derived and FW is already present in ICCM). This is an important reset time optimization for devices that need to meet the hot reset specification time.

Because warm reset is a pin input to Caliptra, Caliptra may not be idle when a warm reset occurs. If a warm reset occurs while Caliptra ROM, FMC, or RT initialization code is executing, Caliptra may be inoperable until a subsequent cold reset. If a warm reset occurs while Caliptra runtime is servicing a request, Caliptra shall remain operable but may refuse to wield production assets for subsequent requests.

**Note:** The cold reset flow is not explicitly mentioned but it is the same as the cold boot flow because Caliptra IP has no state through a cold reset.

## Mailbox

The Caliptra Mailbox is a 128 KiB buffer that is used to exchange data between the SoC and the Caliptra microcontroller.

The SoC communicates with the mailbox over an APB interface. This allows the SoC to identify the device that is using the interface. This ensures that the mailbox, control registers, and fuses are read or written only by the appropriate device.

When a mailbox is populated by SoC, an interrupt to the FW occurs. This indicates that a command is available in the mailbox. The microcontroller is responsible for reading from and responding to the command.

When a mailbox is populated by the microcontroller, Caliptra sends a wire indication to the SoC that a command is available in the mailbox as well as updating the MAILBOX STATUS register. The SoC is responsible for reading from and responding to the command.

Mailboxes are generic data passing structures, and the Caliptra hardware only enforces the protocol for writing to and reading from the mailbox. How the command and data are interpreted by the FW and SoC are not enforced in Caliptra.

### Sender protocol

**Sending data to the mailbox:**

1. Requester queries the mailbox by reading the LOCK control register.
    1. If LOCK returns 0, LOCK is granted and is set to 1.
    2. If LOCK returns 1, MBOX is locked for another device.
2. Requester writes the command to the COMMAND register.
3. Requester writes the data length in bytes to the DLEN register.
4. Requester writes data packets to the MBOX DATAIN register.
5. Requester writes to the EXECUTE register.
6. Requester reads the STATUS register until a value other than CMD\_BUSY is detected. This is also indicated by a dedicated wire that asserts when STATUS is changed. STATUS can return:
    1. DATA\_READY – Indicates the return data is in the mailbox for the requested command.
    2. CMD\_COMPLETE – Indicates the successful completion of the requested command.
    3. CMD\_FAILURE – Indicates the requested command failed.
    4. CMD\_BUSY – Indicates the requested command is still in progress.
7. If response data is expected and the requester reads a STATUS of DATA\_READY:
    1. Requester reads from the DLEN register to ascertain the size of the response data.
    2. Requester reads data from the DATAOUT register until DLEN bytes are read.
8. After reading the response data, if any, requester writes 0 to the EXECUTE register to clear LOCK.

**Notes on behavior:**
After LOCK is granted, the mailbox is locked until that device has concluded its operation. The mailbox is responsible only for accepting writes from the device that requested and locked the mailbox.

*Figure 14: Mailbox sender flow*

![](./images/Caliptra_mbox_state.png)

### Receiver protocol

Upon receiving an indication that the mailbox is populated, the appropriate device can read the mailbox. This is indicated by a dedicated wire that is asserted when Caliptra populates the mailbox for SoC consumption.

**Receiving data from the mailbox:**

1. Receiver reads the COMMAND register.
2. Receiver reads the DLEN register.
3. Receiver reads the MBOX DATAOUT register.
    1. Continues reading MBOX DATAOUT register until DLEN bytes are read.
4. If response data is required:
    1. Receiver writes the size of the response data to the DLEN register.
    2. Receiver writes to the DATAIN register until DLEN bytes are written.
    3. **Note:** Response data is only supported for Caliptra, to SoC-initiated commands. SoC cannot provide response data for Caliptra-initiated commands.
5. Receiver writes to the STATUS register.
    1. If response data was provided, STATUS should be written to DATA\_READY.
    2. Otherwise, STATUS should be written to CMD\_COMPLETE (or CMD\_FAILURE).

*Figure 15: Mailbox receiver flow*

![](./images/Caliptra_mbox_sequence.png)

### User attributes

The PAUSER field of the APB interface is used to encode device attributes for the requester that is utilizing the SoC interface. These values can be used for:

* Ensuring the device that was granted the LOCK is the one that accesses the MBOX, DLEN, COMMAND, and STATUS registers.
* Prioritizing who is next granted the LOCK.

### Mailbox commands

The Caliptra mailbox commands are specified in the [Caliptra runtime firmware specification](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#maibox-commands).


## Caliptra firmware image format

The Caliptra firmware image format is specified in the [Caliptra ROM specification](https://github.com/chipsalliance/caliptra-sw/blob/main/rom/dev/README.md#8-firmware-image-bundle).

### Hash calculation HW API

Caliptra provides a HW API to do a SHA384 hash calculation. The SoC can access the accelerator through this hardware API and stream data to be hashed over the APB interface. The hash is captured into a register for SoC to use or Caliptra FW to be used for the Signature Authentication API.

### JTAG/TAP debug

*Figure 16: Debug flow*

![](./images/Caliptra_boot_flow6.png)

1. SoC drives the security state indicating that it is a debug flow. See [Caliptra security states](#caliptra-security-states) for encodings.
2. SoC (using a GPIO pin or SoC ROM) drives BootFSMBrk (this is also used for debug cases). This can be driven at any time before cptra\_rst\_b is deasserted.
3. SoC follows the boot flow as defined in Caliptra IP HW boot flow to assert cptra\_pwrgood and deassert cptra\_rst\_b, followed by writing to the fuse registers.
4. HVM, through JTAG or through the Caliptra SoC interface, writes to “CPTRA\_DBG\_MANUF\_SERVICE\_REG”, requesting the appropriate debug service (see the ROM/Runtime specifications for bit definitions).
5. HVM, through JTAG, can also inject microcontroller TAP commands at this point following the [VeeR Specification](https://github.com/chipsalliance/Cores-VeeR-EL2).
6. HVM, through JTAG or through the Caliptra SoC interface, writes to “CPTRA\_BOOTFSM\_GO” to allow Caliptra’s internal BootFSM to continue to bring up microcontroller out of reset.
7. Microcontroller executes the appropriate debug service.
8. Specific SoC interface registers (MBOX\_DLEN, MBOX\_DOUT, MBOX\_STATUS, CPTRA\_BOOT\_STATUS, CPTRA\_HW\_ERRROR\_ENC, CPTRA\_FW\_ERRROR\_ENC, BOOTFSM\_GO, CPTRA\_DBG\_MANUF\_SERVICE\_REG) are accessible over the JTAG interface in debug (or manufacturing mode). The following are the JTAG register addresses for these registers:
    1. DMI\_REG\_MBOX\_DLEN = 7'h50; (Read-only)
    2. DMI\_REG\_MBOX\_DOUT = 7'h51; (Read-only)
    3. DMI\_REG\_MBOX\_STATUS = 7'h52; (Read-only)
    4. DMI\_REG\_BOOT\_STATUS = 7'h53; (Read-only)
    5. DMI\_REG\_CPTRA\_HW\_ERRROR\_ENC = 7'h54; (Read-only)
    6. DMI\_REG\_CPTRA\_FW\_ERROR\_ENC = 7'h55; (Read-only)
    7. DMI\_REG\_CPTRA\_DBG\_MANUF\_SERVICE\_REG = 7'h60; (Read-Write)
    8. DMI\_REG\_BOOTFSM\_GO = 7'h61; (Read-Write)
    9. Note: These are injected as TAP register read/write commands as defined in the [VeeR Specification](https://github.com/chipsalliance/Cores-VeeR-EL2).

**Notes:**

1. The security state is latched at cptra\_rst\_b deassertion. If the security state is unlocked at this time, only TAP is opened.
2. Changing the security state at a random time: cptra\_rst\_b deassertion does not unlock Caliptra JTAG.
3. Changing the security state at a random time after cptra\_rst\_b: deassertion flushes out all internal Caliptra secrets, assets, key vault, and crypto intermediate state. The same is true for scan\_mode assertion.
4. Scan mode assertion does not automatically open Caliptra JTAG.

### Architectural registers

These registers are accessible over APB to be read according to the register access permissions. For more information, see the register reference manual at https://ereg.caliptra.org.

### Fuse requirements

Fuse registers are programmable whenever IP goes through reset (after cptra\_rst\_b asserts and de-asserts) and before the fuse registers are locked from writes. If the lock was set, the writes are dropped. The lock is sticky across a warm reset.

To ensure that the security claims of Caliptra are achieved, specific fuse protection capabilities must be supported:

* Fuses that hold Caliptra secrets shall not be readable by any mutable code in the SoC. The intent is to provide defense-in-depth for the UDS.
  * For SoCs that intend to achieve FIPS 140-3 CMVP certification with Caliptra, SoC shall implement a HW state machine for copying the uds_seed, field_entropy, and key_manifest_pk_hash fuses from the fuse controller into Caliptra's fuse shadow registers. Only the fuse controller, this state machine, and Caliptra shall be able to access these fuse values. The intent is to not include the SoC ROM as part of the cryptographic module boundary.
* For the production lifecycle state, if JTAG is enabled pre or post SoC reset, then Caliptra's dedicated fuses shall not be accessible (shall not be readable, shall not be writable) by Caliptra or other SoC IP. This restriction shall be applicable to Caliptra's fuse shadow registers as well (see [Physical Attack Countermeasures](#physical-attack-countermeasures)).
* SoC should ensure that the integrity of each fuse is maintained through the life of the part. The integrity of the fuses can be maintained by fuse redundancy, ECC, or other means determined sufficient by the SoC.

#### Fuse programming

All fuse based cryptographic keying material and seeds (for example, UDS Seed) shall be generated (on-chip or off-chip) per requirements described in [Reference 8](#ref-8).

SoC shall support in-field programmable fusing. [Fuse Map](#fuse-map) shows which fuses are expected to be in-field programmable. SoCs shall implement authorization for in-field programmable fusing to mitigate denial-of-service attacks. Authorization design is outside the scope of this specification.

SoC shall support a field entropy programming API. The API shall support retrieving an input value from an external interface. It should cryptographically mix that value with the output of an on-die TRNG to generate the field entropy value. The API implementation shall burn the field entropy value into the first available field entropy fuse slot (or fail if no slots are available). Caliptra is expected to be in any security state. The device owner is expected to call this API in a “clean room environment” to minimize risk of attack on the programming process.

#### Fuse zeroing

Caliptra assumes that the unfused value in fuses is '0' and the fused value is '1'. With this context, zeroization refers to destroying a secret value by fusing it to all ones.

For SoCs that intend to achieve FIPS 140-3 CMVP certification with Caliptra:
* SoC shall implement zeroization for uds_seed and field_entropy such that the fuse rows holding these secrets contain all ones.
* SoC shall expose and document an API for a tester to invoke zeroization.
* SoC shall indicate that zeroization has occurred by statically asserting GENERIC_INPUT_WIRE[0] to Caliptra.
* SoC shall set Caliptra’s security state to DebugUnlock by ORing it with the zeroization status signal.
* SoC shall expose Caliptra architectural registers as API for a tester to read.
* SoC shall ensure authorization for this API to guard against denial-of-service attacks. The authorization design is left to the vendor.

#### Fuse map
The following table describes Caliptra's fuse map:

*Table 12: Caliptra Fuse Map*

| **Name**                        | **Size (bits)** | **ACL**         | **Fuse programming time**                       | **Description** |
| ------------------------------- | --------------- | --------------- | ----------------------------------------------- | --------------- |
| UDS Seed (obfuscated)           | 384             | ROM             | SoC manufacturing                               | DICE Unique Device Secret Seed. This seed is unique per device. The seed is scrambled using an obfuscation function. |
| Field Entropy (obfuscated)      | 256             | ROM             | Device owner in-field programmable | Field-programmable by the owner, used to hedge against UDS disclosure in the supply chain. |
| KEY MANIFEST PK HASH            | 384             | ROM FMC RUNTIME | SoC manufacturing                               | SHA-384 hash of hashes of the Key Manifest Signing the ECC P-384 Public Keys. |
| KEY MANIFEST PK HASH MASK       | 4               | ROM FMC RUNTIME | In-field programmable                           | One-hot encoded list of revoked Key Manifest PK Hash. |
| OWNER PK HASH                   | 384             | ROM FMC RUNTIME | In-field programmable                           | SHA-384 hash of hashes of the Owner Key ECC P-384 Public Keys. |
| OWNER KEY MANIFEST PK HASH MASK | 4               | ROM FMC RUNTIME | In-field programmable                           | One-hot encoded list of revoked Owner Key Manifest PK Hash. |
| FMC KEY MANIFEST SVN            | 32              | ROM FMC RUNTIME | In-field programmable                           | FMC security version number. |
| RUNTIME SVN                     | 128             | ROM FMC RUNTIME | In-field programmable                           | Runtime firmware security version number. |
| ANTI-ROLLBACK DISABLE           | 1               | ROM FMC RUNTIME | SoC manufacturing or in-field programmable      | Disables anti-rollback support from Caliptra. (For example, if a Platform RoT is managing FW storage and anti-rollback protection external to the SoC.) |
| IDEVID CERT IDEVID ATTR.        | 768             | ROM FMC RUNTIME | SoC manufacturing                               | Manufacturer IEEE IDEVID Certificate Generation Attributes. See the ROM specification for details. |
| IDEVID MANUF HSM IDENTIFIER     | 128             | ROM FMC RUNTIME | SoC manufacturing                               | Manufacturer IDEVID Manufacturer’s HSM identifier (this is used to find the certificate chain from the boot media). See the ROM specification for details. |
| Life Cycle Fuses                | 2               | ROM FMC RUNTIME | SoC manufacturing                               | **Caliptra Boot Media Integrated mode usage only**. SoCs that build with a Boot Media Dependent profile don’t have to account for these fuses.<br> - ‘00 - Unprovisioned or manufacturing<br> - ‘01 - Production ‘10 - UNDEF<br> - ‘11 - End Of Life<br> **Reset:** Can only be reset on powergood. |
| LMS VERIFY                      | 1               | ROM             | In-field programmable                           | - 0 - Verify Caliptra firmware images with ECDSA-only.<br> - 1 - Verify Caliptra firmware images with both ECDSA and LMS.
| LMS REVOCATION                  | 32              | ROM             | In-field programmable                           | Bits for revoking LMS public keys in the key manifest.

# Error reporting and handling

This section describes Caliptra error reporting and handling.

*Table 13: Hardware and firmware error types*

| | Fatal errors | Non-fatal errors |
| :- | - | - |
| Hardware | - ICCM, DCCM SRAM ECC<br> - Second watchdog (WD) timer expiry. The first timer expiry triggers an NMI to firmware to correct the issue and clear the interrupt status bit. If the WD expires again, then it is escalated to a FATAL error. | - Mailbox SRAM ECC (except initial firmware load)<br> - Mailbox incorrect protocol or commands. For example, incorrect access ordering or access without Lock. |
| Firmware | - Boot-time firmware authentication failures<br> - Firmware triggered FATAL errors. Examples: ICCM or DCCM have misaligned access (potentially in the except subroutine); AHB access hangs, triggered through WD timer expiry; AHB access outside of the decoding range; and stack overflow errors. For more information, see the table below. | - Mailbox API failures<br> - First WD timer expiry<br> - Cryptography processing errors |

**Fatal errors**

* Fatal errors log the FATAL ERROR reasons into an architectural register that is RW from the external world. This register must be sticky (as in, reset is on powergood).
* This register may be cleared at any time via register write (W1C).
* Caliptra signals fatal errors using a cptra\_error\_fatal wire.
  * SoCs should connect this into their SoC error handling logic. Upon detection of a FATAL ERROR in Caliptra, SoC shall treat any outstanding commands with Caliptra as failed, and SoC may recover by performing a Caliptra reset using the signal `cptra_rst_b`.
  * This signal prevents forward progress of the boot process if measurement submission to Caliptra fails. If SoC detects a Caliptra fatal error while the SoC is in steady state, then there is no obligation for the SoC to immediately address that error. If rebooting the SoC for such failures is deemed unacceptable to uptime, the SoC should implement the ability to trigger a Caliptra warm reset independently of the SoC, and may use this mechanism to recover.
  * Error mask registers (writable only by Caliptra microcontroller) may be used to prevent error signal assertion per-event. Mask registers only impact interrupts when they are set prior to the error occurrence.
  * cptra\_error\_fatal remains asserted until Caliptra is reset. Note that, although the HW FATAL ERROR register fields may be cleared at any time, a reset is still required to clear the interrupt.
* When a fatal error occurs, all volatile assets that are stored in key vault are cleared.

**Non-fatal errors**

* Non-fatal errors log the NON-FATAL ERROR reasons into an architectural register that is RW from the external world. This register must be sticky (as in, reset is on powergood).
* This register may be cleared at any time via register write (W1C).
* Caliptra signals non-fatal errors using a cptra\_error\_non\_fatal wire.
* Caliptra reset via `cptra_rst_b`, or a write to clear the NON-FATAL ERROR register, cause the interrupt to deassert.
* It is optional for SoCs to include this signal in their logic.

**Firmware errors**

*Table 14: Firmware errors and remedies*

| Condition | When error occurs | Remediation |
| :-------- | :---------------- | :---------- |
| SoC FMC verification failure due to invalid digital signature or invalid anti-rollback value) | During boot, as described in [Boot Media Integrated](#bmi), [Boot Media Dependent](#bmd), [Secure Boot Flow](#secure-boot-flow) |  |
| Caliptra FMC invalid | During boot, as described in [Boot Media Integrated](#bmi), [Boot Media Dependent](#bmd), [Secure Boot Flow](#secure-boot-flow) |  |
| Caliptra runtime firmware invalid | During boot, as described in [Boot Media Integrated](#bmi), [Boot Media Dependent](#bmd), [Secure Boot Flow](#secure-boot-flow) |  |
| Fuse programming errors |  |  |

# Terminology

The following acronyms and abbreviations are used throughout this document.

| Abbreviation | Description |
|:-------------|:------------|
| <a id="bmc"></a>**BMC**       | Baseboard Management Controller                |
| <a id="CA"></a>**CA**         | Certification Authority                        |
| <a id="CDI"></a>**CDI**       | Compound Device Identifier                     |
| <a id="CPU"></a>**CPU**       | Central Processing Unit                        |
| <a id="CRL"></a>**CRL**       | Certificate Revocation List                    |
| <a id="CSR"></a>**CSR**       | Certificate Signing Request                    |
| <a id="CSP"></a>**CSP**       | Cloud Service Provider                         |
| <a id="DICE"></a>**DICE**     | Device Identifier Composition Engine           |
| <a id="DRBG"></a>**DRBG**     | Deterministic Random Bit Generator             |
| <a id="ECDSA"></a>**ECDSA**   | Elliptic Curve Digital Signature Algorithm     |
| <a id="FMC"></a>**FMC**       | First Mutable Code                             |
| <a id="GPU"></a>**GPU**       | Graphics Processing Unit                       |
| <a id="IDevId"></a>**IDevId** | Initial Device Identifier                      |
| <a id="iRoT"></a>**iRoT**     | Internal Root of Trust                         |
| <a id="KAT"></a>**KAT**       | Known Answer Test                              |
| <a id="LDevId"></a>**LDevId** | Locally Significant Device Identifier          |
| <a id="NIC"></a>**NIC**       | Network Interface Card                         |
| <a id="NIST"></a>**NIST**     | National Institute of Standards and Technology |
| <a id="OCP"></a>**OCP**       | Open Compute Project                           |
| <a id="OTP"></a>**OTP**       | One-time programmable                          |
| <a id="PKI"></a>**PKI**       | Public Key infrastructure                      |
| <a id="PTRNG"></a>**P-TRNG**  | Parallel True Random Number Generator          |
| <a id="PUF"></a>**PUF**       | Physically unclonable function                 |
| <a id="RoT"></a>**RoT**       | Root of Trust                                  |
| <a id="RTI"></a>**RTI**       | RoT for Identity                               |
| <a id="RTM"></a>**RTM**       | RoT for Measurement                            |
| <a id="RTR"></a>**RTR**       | RoT for Reporting                              |
| <a id="SoC"></a>**SoC**       | System on Chip                                 |
| <a id="SPDM"></a>**SPDM**     | Security Protocol and Data Model               |
| <a id="SSD"></a>**SSD**       | Solid State Drive                              |
| <a id="TCB"></a>**TCB**       | Trusted Computing Base                         |
| <a id="TCG"></a>**TCG**       | Trusted Computing Group                        |
| <a id="TEE"></a>**TEE**       | Trusted Execution Environment                  |
| <a id="TRNG"></a>**TRNG**     | True Random Number Generator                   |

# References

1. <a id="ref-1"></a>NIST Special Publication 800-193 Platform Firmware Resiliency Guidelines
2. <a id="ref-2"></a>Global Platform Technology Root of Trust Definitions and Requirements Version 1.1 Public
3. <a id="ref-3"></a>[Open Compute Project Secure Boot Specification](https://www.opencompute.org/documents/secure-boot-2-pdf)
4. <a id="ref-4"></a>TCG DICE Layering Architecture Version 1.0 Revision 0.19 July 23, 2020
5. <a id="ref-5"></a>TCG DICE Attestation Architecture Version 1.00 Revision 0.23 March 1, 2021
6. <a id="ref-6"></a>TCG Hardware Requirements for a Device Identifier Composition Engine Family “2.0” Level
7. <a id="ref-7"></a>[Side-Channel Attacks: Ten Years After Its Publication and the Impacts on Cryptographic Module Security Testing](https://csrc.nist.gov/csrc/media/events/physical-security-testing-workshop/documents/papers/physecpaper19.pdf)
8. <a id="ref-8"></a>[Attestation of System Components v1.0 Requirements and Recommendations](https://www.opencompute.org/documents/attestation-v1-0-20201104-pdf)
9. <a id="ref-9"></a>OCP Security WG: Ownership Transfer

# Acknowledgments

The Caliptra Workgroup acknowledges the following individuals for their contributions to this specification.

**CONTRIBUTORS**

* Andrés Lagar-Cavilla (Google)
* Anjana Parthasarathy (Microsoft)
* Bharat Pillilli (Microsoft)
* Bryan Kelly (Microsoft)
* Ishwar Agarwal (Microsoft)
* James Zhang (NVIDIA)
* Jeff Andersen (Google)
* John Traver (AMD)
* Jordan Hand (Google)
* Kor Nielsen (Google)
* Louis Ferraro (AMD)
* Marius Schilder (Google)
* Nathan Nadarajah (AMD)
* Paul Chou (NVIDIA)
* Piotr Kwidzinski (AMD)
* Prabhu Jayana (AMD)
* Rob Strong (AMD)
* Sudhir Mathane (AMD)
* Varun Sampath (NVIDIA)
* Vishal Soni (Microsoft)
* Steven Bellock (NVIDIA)

# Footnotes

[^1]: Caliptra is Spanish for “root cap” and describes the deepest part of the root.

[^2]: This obfuscation secret may be a chip-class secret, or a chip-unique PUF, with the latter preferred.

[^3]: This memory should only be volatile in a power loss event. See details in [HW Section](#reset-flow).

[^4]: When a hitless update occurs, and then following reset, Caliptra shall execute the updated firmware and shall maintain the measurements that it collected during boot. Caliptra shall support the reporting of these measurements with signed attestations. Hitless update of Caliptra’s FMC shall not be supported. Hitless update requires creating a new DICE identity, which would require access to IDevID and LDevID. Retention of IDevID and LDevID (privkeys) during post-boot introduce a security vulnerability.

[^5]: Upon boot, firmware defensively treats existing SRAM contents as potentially malicious, emplaced by prior firmware with a vulnerability.

[^6]: The format of this log is outside the scope of this specification.

[^7]: The format of this blob is outside the scope of this specification.

[^8]: ECDSA is used for firmware verification and SPDM (signing).

[^9]: SHA is used with ECDSA and HMAC, and is also used to generate measurements.
