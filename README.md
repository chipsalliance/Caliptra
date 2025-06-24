![Caliptra Logo](https://chipsalliance.github.io/Caliptra/doc/images/logo/Caliptra_logo_large.png)

# Caliptra

Caliptra consists of IP and firmware for an integrated Root of Trust block.

Caliptra targets datacenter-class SoCs like CPUs, GPUs, DPUs, TPUs. It is the
specification, silicon logic, ROM and firmware for implementing a Root of Trust
for Measurement (RTM) block inside an SoC. A Caliptra integration provides the
SoC with Identity, Measured Boot and Attestation capabilities.

## Organizations

Caliptra is a project originally incepted at the Open Compute Project
([OCP](https://www.opencompute.org/)).  The major revisions of the Caliptra
specifications are published at OCP. The evolving source code and documentation
for Caliptra live in this repository within the [CHIPS Alliance
Project](https://chipsalliance.org/), a Series of LF Projects, LLC.

## Governance

The [Caliptra WorkGroup Technical Charter](https://github.com/chipsalliance/Caliptra/blob/main/CaliptraWGTechnicalCharter.md)
sets out the charter governing the Caliptra project.

## Trademark

* [Caliptra Trademark Policy](https://github.com/chipsalliance/Caliptra/blob/main/CaliptraTrademarkPolicy.md)
* [Caliptra Trademark Process definition](https://github.com/chipsalliance/Caliptra/blob/main/CaliptraTrademarkAuditProcess.md)
* [Caliptra Trademark Checklist and Evaluation Methodology](https://github.com/chipsalliance/Caliptra/blob/main/CaliptraChecklistAndEvaluationMethodology.md)

## Specifications

### Caliptra 1.x:
  * [Main Caliptra specification 1.x](https://github.com/chipsalliance/Caliptra/blob/main/doc/caliptra_1x/Caliptra.md)
  * [Caliptra Core Hardware Specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraHardwareSpecification.md)
  * [Caliptra Core Hardware Integration
    Specification](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraIntegrationSpecification.md)
  * [ROM 1.x](https://github.com/chipsalliance/caliptra-sw/blob/main/rom/dev/README.md)
  * [FMC](https://github.com/chipsalliance/caliptra-sw/blob/main/fmc/README.md)
  * [Runtime](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md)

### Caliptra 2.x:
  * [Main Caliptra specification 2.0 - Version 1.0](https://github.com/chipsalliance/Caliptra/blob/main/doc/caliptra_20/Caliptra.md)
  * [Caliptra Subsystem Hardware Specification - Version 0.5](https://github.com/chipsalliance/caliptra-ss/blob/main/docs/Caliptra%202.0%20Subsystem%20Specification%201.pdf)
  * **Note:** Hardware integration specs will be following the RTL Freezes & Releases timelines
  * [ROM 2.x - WIP](https://github.com/chipsalliance/caliptra-sw/blob/main-2.x/rom/dev/README.md)
  * [FMC 2.x - WIP](https://github.com/chipsalliance/caliptra-sw/blob/main-2.x/fmc/README.md)
  * [Runtime 2.x - WIP](https://github.com/chipsalliance/caliptra-sw/blob/main-2.x/runtime/README.md)
  * [MCU Firmware and SDK specification - WIP](https://chipsalliance.github.io/caliptra-mcu-sw/)

## Versioning

Caliptra is released in independently versioned components: RTL, ROM, FMC and Runtime FW. They are all represented by 3 values: major.minor.patch (such as 1.0.2). The first 2 values, major.minor, correspond to a set of features caliptra supports. The patch value is incremented as new releases are made with bug fixes.

Not all components necessarily need to be of the same major.minor version to be compatible. Details are below:

### Caliptra 1.0
Compatible Configurations:
| RTL | ROM | Runtime FMC/FW |
| --- | --- | --- |
| 1.0.x | 1.0.x | 1.0.x |

### Caliptra 1.1

Additional Features
  - ECC HW performance enhancements*
  - LMS HW acceleration*
  - New Runtime commands
    - [LMS_SIGNATURE_VERIFY](https://github.com/chipsalliance/caliptra-sw/blob/caliptra-1.1/runtime/README.md#lms_signature_verify)
    - [ADD_SUBJECT_ALT_NAME](https://github.com/chipsalliance/caliptra-sw/blob/caliptra-1.1/runtime/README.md#add_subject_alt_name)
    - [CERTIFY_KEY_EXTENDED](https://github.com/chipsalliance/caliptra-sw/blob/caliptra-1.1/runtime/README.md#certify_key_extended)
  - Expanded PL0 contexts to 16

\* Requires 1.1 RTL

Compatible Configurations:
| RTL | ROM | Runtime FMC/FW |
| --- | --- | --- |
| 1.1.x | 1.1.x | 1.1.x |
| 1.0.x | 1.0.x | 1.1.x |


### Caliptra 1.2

Additional Features
  - [Manifest-based Authorization](https://github.com/chipsalliance/caliptra-sw/blob/main/auth-manifest/README.md)
    - [SET_AUTH_MANIFEST](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#set_auth_manifest)
    - [AUTHORIZE_AND_STASH](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#authorize_and_stash)
  - Deferred retrieval of IDEV CSR**
    - [GET_IDEVID_CSR](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#get_idevid_csr)
  - Self-signed FMC Alias CSR
    - [GET_FMC_ALIAS_CSR](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#get_fmc_alias_csr)
  - DPE export of CDI
    - [SIGN_WITH_EXPORTED_ECDSA](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#sign_with_exported_ecdsa)
    - [REVOKE_EXPORTED_CDI_HANDLE](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#revoke_exported_cdi_handle)
  - DPE max cert size increased to 6kB

\*\* Requires 1.2 ROM

Compatible Configurations:
| RTL | ROM | Runtime FMC/FW |
| --- | --- | --- |
| 1.1.x | 1.2.x | 1.2.x |
| 1.1.x | 1.1.x | 1.2.x |
| 1.0.x | 1.0.x | 1.2.x |

### Caliptra 2.0

Additional Features
  - Support ML-DSA Caliptra FW Signature
  - Support OCP Recovery
  - Support [Caliptra Sub-System](https://github.com/chipsalliance/caliptra-ss/)
  - IDevID CSR HMAC Signing
  - Crypto Offload Mailbox Services

Compatible Configurations:

| RTL | ROM | Runtime FMC/FW |
| --- | --- | --- |
| 2.0.x | 2.0.x | 2.0.x |

## Test Dashboards

* [Caliptra Software CI dashboard](https://chipsalliance.github.io/caliptra-sw/)
  -- includes ROM
* [Caliptra CPU DV coverage
  dashboard](https://chipsalliance.github.io/Cores-VeeR-EL2/html/main/coverage_dashboard/all/index.html)

## Repositories

The Caliptra code base and documentation are split across several repositories:

| Repository | Areas of interest | Description |
| ---------- | ---- | ----------- |
| [Primary repository](https://github.com/chipsalliance/caliptra)  | [Issues](https://github.com/chipsalliance/caliptra/issues),      [PRs](https://github.com/chipsalliance/caliptra/pulls),      [Security advisories](https://github.com/chipsalliance/caliptra/security/advisories)      | This repository, with admin boilerplate and docs |
| [Adams Bridge RTL](https://github.com/chipsalliance/adams-bridge)  | [Issues](https://github.com/chipsalliance/adams-bridge/issues),      [PRs](https://github.com/chipsalliance/adams-bridge/pulls),      [Security advisories](https://github.com/chipsalliance/adams-bridge/security/advisories)      | The primary repository with Adams Bridge Post-Quantum Cryptography hardware accelerator |
| [Caliptra RTL](https://github.com/chipsalliance/caliptra-rtl)     | [Issues](https://github.com/chipsalliance/caliptra-rtl/issues),  [PRs](https://github.com/chipsalliance/caliptra-rtl/pulls),  [Security advisories](https://github.com/chipsalliance/caliptra-rtl/security/advisories)  | The primary repository with immutable RTL |
| [Caliptra Software 1.x](https://github.com/chipsalliance/caliptra-sw) | [Issues](https://github.com/chipsalliance/caliptra-sw/issues),   [PRs](https://github.com/chipsalliance/caliptra-sw/pulls),   [Security advisories](https://github.com/chipsalliance/caliptra-sw/security/advisories)   | Caliptra software (ROM, FMC, runtime firmware), and libraries/tools needed to build and test |
| [Caliptra Software 2.x](https://github.com/chipsalliance/caliptra-sw/tree/main-2.x) | [Issues](https://github.com/chipsalliance/caliptra-sw/issues),   [PRs](https://github.com/chipsalliance/caliptra-sw/pulls),   [Security advisories](https://github.com/chipsalliance/caliptra-sw/security/advisories)   | Caliptra software (ROM, FMC, runtime firmware), and libraries/tools needed to build and test |
| [Caliptra DPE](https://github.com/chipsalliance/caliptra-dpe)     | [Issues](https://github.com/chipsalliance/caliptra-dpe/issues),  [PRs](https://github.com/chipsalliance/caliptra-dpe/pulls),  [Security advisories](https://github.com/chipsalliance/caliptra-dpe/security/advisories)  | An implementation of a TCG DICE Protection Environment profile |
| [Caliptra U-Reg](https://github.com/chipsalliance/caliptra-ureg)  | [Issues](https://github.com/chipsalliance/caliptra-ureg/issues), [PRs](https://github.com/chipsalliance/caliptra-ureg/pulls), [Security advisories](https://github.com/chipsalliance/caliptra-ureg/security/advisories) | General-purpose libraries and tools for manipulating MMIO registers from Rust |
| [Caliptra Subsystem](https://github.com/chipsalliance/caliptra-ss)| [Issues](https://github.com/chipsalliance/caliptra-ss/issues), [PRs](https://github.com/chipsalliance/caliptra-ss/pulls), [Security advisories](https://github.com/chipsalliance/caliptra-ss/security/advisories) | Caliptra Subsystem including Manufacturer Control Unit (MCU) and peripherals |
| [Caliptra MCU Software](https://github.com/chipsalliance/caliptra-mcu-sw)| [Issues](https://github.com/chipsalliance/caliptra-mcu-sw/issues), [PRs](https://github.com/chipsalliance/caliptra-mcu-sw/pulls), [Security advisories](https://github.com/chipsalliance/caliptra-mcu-sw/security/advisories) | Caliptra MCU Firmware and SDK and specification |
| [I3C Core](https://github.com/chipsalliance/i3c-core/)            | [Issues](https://github.com/chipsalliance/i3c-core/issues), [PRs](https://github.com/chipsalliance/i3c-core//pulls), [Security advisories](https://github.com/chipsalliance/i3c-core/security/advisories) | I3C target core developed for Caliptra |

The GitHub config parameters for all of the branches are documented in a [local
file](https://github.com/chipsalliance/Caliptra/blob/main/GitHubRules.md).

### Convenience repository URLs

All these URLs redirect into the repositories above.

* [repo.caliptra.io](http://repo.caliptra.io)
* [spec.caliptra.io](http://spec.caliptra.io)
* [sw.caliptra.io](http://sw.caliptra.io)
* [fw.caliptra.io](http://fw.caliptra.io)
* [hw.caliptra.io](http://hw.caliptra.io)
* [rtl.caliptra.io](http://rtl.caliptra.io)
* [dpe.caliptra.io](http://dpe.caliptra.io)
* [ureg.caliptra.io](http://ureg.caliptra.io)
* [ireg\[s\].caliptra.io](http://iregs.caliptra.io)
* [ereg\[s\].caliptra.io](http://eregs.caliptra.io)

## Security policy

For information on the Caliptra security policy, how to report a vulnerability,
and published security advisories, refer to
[Caliptra security policy](https://github.com/chipsalliance/caliptra/security/policy).

## Discussion Channels

The Caliptra workgroup meets every Thursday at 1pm PT. Meeting invite and agenda
are posted to the [mailing list](https://lists.chipsalliance.org/g/caliptra-wg).
The [call
invite](https://teams.microsoft.com/l/meetup-join/19%3ameeting_MmQwYTE4YzQtOWJkMy00YzcyLTgxMDUtYTQ2Zjk2ZjhkMzk5%40thread.v2/0?context=%7b%22Tid%22%3a%2272f988bf-86f1-41af-91ab-2d7cd011db47%22%2c%22Oid%22%3a%22661ec88e-77cb-431c-935a-b377b1078af4%22%7d) is also reachable from the [CHIPS Workgroups
page](https://www.chipsalliance.org/workgroups/).

A [Slack channel](https://join.slack.com/t/caliptraworkspace/signup)
is used for interactive discussions. Keep in mind development activity is focused on
GitHub issues and Pull Request reviews, rarely on the Slack channel. If you have
issues joining please contact the mailing list.

Please sign the [CHIPS CLA](https://github.com/chipsalliance/tsc/tree/main/cla)
(as an individual or your
[company](https://github.com/chipsalliance/tsc/blob/main/cla/CLA-status.yml) if
affiliated) before participating in these channels.

## License

All code written for Caliptra and found in these repositories is licensed under
the [Apache Source License 2.0](https://github.com/chipsalliance/Caliptra/blob/main/LICENSE). You can find out more by reading our
document on [how to contribute](https://github.com/chipsalliance/Caliptra/blob/main/CONTRIBUTING.md).
