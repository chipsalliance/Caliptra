![Caliptra Logo](doc/images/logo/Caliptra_logo_large.png)

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

The [Caliptra WorkGroup Technical Charter](CaliptraWGTechnicalCharter.md)
sets out the charter governing the Caliptra project and [its
marks](CaliptraTrademarkPolicy.md).

## Specifications

* [Main Caliptra specification](doc/Caliptra.md)
* [FMC](https://github.com/chipsalliance/caliptra-sw/tree/main/fmc#readme)
* [Firmware](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md)

## Security policy

For information on the Caliptra security policy, how to report a vulerability,
and published security advisories, refer to
[Caliptra security policy](https://github.com/chipsalliance/caliptra/security/policy).

### Product creator registration

Companies or individuals building products that integrate Caliptra are
encouraged to register as Caliptra product creators. Product creators will
automatically get early notification of embargoed security vulnerabilities, as
defined in the Caliptra security policy.

* **Registration process to be defined**

## Repositories

The Caliptra code base and documentation are split across five repositories:

| Repository | What | Description |
| ---------- | ---- | ----------- |
| [Primary repoository](https://github.com/chipsalliance/caliptra)  | [Issues](https://github.com/chipsalliance/caliptra/issues),      [PRs](https://github.com/chipsalliance/caliptra/pulls),      [Security advisories](https://github.com/chipsalliance/caliptra/security/advisories)      | This repoository, with admin boilerplate and docs |
| [Caliptra RTL](https://github.com/chipsalliance/caliptra-rtl)     | [Issues](https://github.com/chipsalliance/caliptra-rtl/issues),  [PRs](https://github.com/chipsalliance/caliptra-rtl/pulls),  [Security advisories](https://github.com/chipsalliance/caliptra-rtl/security/advisories)  | The primary repository with immutable RTL |
| [Caliptra Software](https://github.com/chipsalliance/caliptra-sw) | [Issues](https://github.com/chipsalliance/caliptra-sw/issues),   [PRs](https://github.com/chipsalliance/caliptra-sw/pulls),   [Security advisories](https://github.com/chipsalliance/caliptra-sw/security/advisories)   | Caliptra software (ROM, FMC, runtime firmware), and libraries/tools needed to build and test |
| [Caliptra DPE](https://github.com/chipsalliance/caliptra-dpe)     | [Issues](https://github.com/chipsalliance/caliptra-dpe/issues),  [PRs](https://github.com/chipsalliance/caliptra-dpe/pulls),  [Security advisories](https://github.com/chipsalliance/caliptra-dpe/security/advisories)  | An implementation of a TCG DICE Protection Environment profile |
| [Caliptra U-Reg](https://github.com/chipsalliance/caliptra-ureg)  | [Issues](https://github.com/chipsalliance/caliptra-ureg/issues), [PRs](https://github.com/chipsalliance/caliptra-ureg/pulls), [Security advisories](https://github.com/chipsalliance/caliptra-ureg/security/advisories) | General-purpose libraries and tools for manipulating MMIO registers from Rust |

The GitHub config parameters for all of the branches are documented in a [local
file](GitHubRules.md).

### Convenience repoository URLs

All these URLs redirect into the repoositories above.

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

## Discussion Channels

The Caliptra workgroup meets every Friday at 9am PT. Meeting invite and agenda
are posted to the [mailing list](https://lists.chipsalliance.org/g/caliptra-wg).
The [call
invite](https://teams.microsoft.com/l/meetup-join/19%3ameeting_ZTViMGQ5MDYtNGY4MS00ODY5LTg4NmQtNDE3N2QwZmVhMmNh%40thread.v2/0?context=%7b%22Tid%22%3a%2272f988bf-86f1-41af-91ab-2d7cd011db47%22%2c%22Oid%22%3a%22661ec88e-77cb-431c-935a-b377b1078af4%22%7d)
is also reachable from the [CHIPS Workgroups
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
the [Apache Source License 2.0](LICENSE). You can find out more by reading our
document on [how to contribute](CONTRIBUTING.md).
