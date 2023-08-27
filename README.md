![Caliptra Logo](doc/images/Caliptra_Logo_large.png)

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

The [Caliptra WorkGroup Technical Charter](Caliptra_WG_Technical_Charter.md)
sets out the charter governing the Caliptra project.

## Specifications

- [Main Caliptra specification](doc/Caliptra.md)

## Repositories

The Caliptra code base and documentation are split across five repositories:

| Repo | What |
| ---- | ---- |
| [Primary Repo](https://github.com/chipsalliance/caliptra)        | This repo, with admin boilerplate and docs |
| [Caliptra RTL](https://github.com/chipsalliance/caliptra-rtl)    | The primary repository with immutable RTL |
| [Caliptra SW](https://github.com/chipsalliance/caliptra-sw)      | Caliptra software (ROM, FMC, runtime firmware), and libraries/tools needed to build and test |
| [Caliptra U-Reg](https://github.com/chipsalliance/caliptra-ureg) | General-purpose libraries and tools for manipulating MMIO registers from Rust |
| [Caliptra DPE](https://github.com/chipsalliance/caliptra-dpe)    | An implementation of a TCG DICE Protection Environment profile |

The github config parameters for all the branches are documented in a [local
file](github_rules.md)

## License

All Code written for Caliptra and found in these repositories is licensed under
the [Apache Source License 2.0](LICENSE).
