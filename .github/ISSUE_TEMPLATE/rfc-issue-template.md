---
name: Caliptra Project RFC Issue Template
about: Template for Caliptra contributors to file an RFC proposing changes that impact the Caliptra project.
title: "[RFC] {RFC title here}"
labels: RFC
assignees: ''

---

# [edit] Title for contribution proposal

[edit] Abstract

## Scope

[edit] What parts of the project will be affected.

Affected repositories (check all that apply):

* [ ] [Caliptra](https://github.com/chipsalliance/Caliptra) (specifications, documentation, project process)
* [ ] [caliptra-rtl](https://github.com/chipsalliance/caliptra-rtl) (Caliptra core RTL)
* [ ] [caliptra-ss](https://github.com/chipsalliance/caliptra-ss) (Caliptra subsystem RTL)
* [ ] [caliptra-sw](https://github.com/chipsalliance/caliptra-sw) (Caliptra core ROM, firmware, and libraries)
* [ ] [caliptra-mcu-sw](https://github.com/chipsalliance/caliptra-mcu-sw) (Caliptra subsystem MCU ROM and firmware)
* [ ] Other: [edit]

Expected impacts (write "N/A" where not applicable):

* [edit] Overview of anticipated changes to specifications or other documentation (e.g. impacts to Trademark Compliance, specifications, repo structures, etc)
* [edit] Overview of changes to security posture per FIPS 140-3
* [edit] Expected impact to interfaces and compatibility (e.g. registers, mailbox commands, APIs, integration requirements, backward compatibility with prior releases)
* [edit] Expected impact to resource consumption (e.g. silicon area, ROM/SRAM/fuse usage, firmware code size)
* [edit] Expected impact to performance (e.g. boot time, command latency, timing closure, CDC/RDC)

## Rationale

[edit] The motivation and justification for the change, including why it is important to include in a specific Caliptra release version.

## Implementation Tradeoffs

[edit] Details of various implementations being considered. Explain why the proposed change can not be handled outside of Caliptra.

[optional - if available] Links to any development work already completed and accompanying test results.

## Implementation Timeline

[edit] A realistic estimate for completion. May include multiple milestones if a large change requires many Pull Requests (or Pull Requests across multiple repositories).

[edit] Which MAJOR.MINOR release is this intended for inclusion?

## [required for RTL/ROM/firmware changes] Test Plan

[edit] To ensure quality, certifiability, maintainability.

### Test infrastructure

[edit] Describe new or modified test infrastructure needed to validate the change (e.g. testbenches, emulators/models, test harnesses, FPGA flows).

### Test suite

| Test Title    | Repository   | Test Environment | Description                | Randomization | Pass Metrics |
| :------------ | :----------- | :--------------- | :------------------------- | :------------ | :----------- |
| [edit] Test 1 | caliptra-rtl | caliptra_top_tb  | new test for testing tests | a,b,c         | x,y,z        |

## Maintenance

[edit] The individual or team responsible as the point of contact for this feature now and in the future. Contributors must provide a plan for ongoing maintenance.
