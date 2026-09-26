# Caliptra Trademark Versioning Scheme

* Status: Draft
* Scope: Caliptra Trademark requirement documents (Policy, Audit Process, Checklist and Evaluation Methodology, Compatibility Matrix, and related controlled edition documents)
* See also: [`README.md`](README.md) (Edition Index), [`../CaliptraContributingProcess.md`](../CaliptraContributingProcess.md)

## 1. Purpose

This document defines the Caliptra Trademark Versioning Scheme: the mechanism used to develop, ratify, revise, cite, and deprecate the set of documents against which an integrator's product is audited to receive a Caliptra Trademark license.

All working and ratified Trademark documentation is maintained on the `main` branch. A mutable working directory contains the proposed requirements for the next Edition, and each ratified Edition is preserved in a dedicated directory on `main`. Immutable Git tags identify the exact commit for every ratified Edition and Revision.

The Trademark Edition identifier is independent of Caliptra code release versions. Caliptra code components use `major.minor.patch` versions and may advance independently. Each Trademark Edition therefore contains a [Compatibility Matrix LINK FIXME](FIXME) that explicitly defines which Caliptra code releases may be evaluated under that Edition.

> **No implicit license.** Listing a Caliptra release in an Edition's Compatibility Matrix does not license the Caliptra Trademark to a product, vendor, or integration. It establishes only that an integrator may pursue a license under that Edition by completing its audit process. A license is issued only after successful completion of the audit and issuance of the required Statement of Conformance.

This document defines:

- The Edition and Revision identifier scheme.
- The `main`-branch directory model for working and ratified documentation.
- The ratification process for a new Edition.
- The limited process for revising a ratified Edition.
- The GitHub workflow requirements that protect ratified Edition directories.
- The Compatibility Matrix rules connecting Editions to Caliptra code releases.
- The deprecation and tagging rules that determine whether an Edition and Revision may be used for a future product.

## 2. Identifier Scheme

A Trademark Edition is identified by an uppercase Latin letter beginning at `A`.

Each ratified state of an Edition also has a positive integer Revision. Revision numbering begins at `1` and increases consecutively.

| Element | Form | Examples |
| --- | --- | --- |
| Edition identifier | Uppercase Latin letter(s) | `A`, `B`, `Z` |
| Working directory | `doc/trademark/next_wip/` | `doc/trademark/next_wip/` |
| Ratified Edition directory | `doc/trademark/edition_<identifier>/` | `doc/trademark/edition_A/`, `doc/trademark/edition_M/` |
| Edition and Revision tag | `edition-<identifier>-r<N>` | `edition-A-r1`, `edition-A-r2` |
| Human-readable version | `Edition <identifier>, Revision <N>` | `Edition A, Revision 1` |

The working directory is named `next_wip`. The name makes clear that its contents are work in progress, have not been ratified, and cannot be used as the basis for a Trademark audit or license.

Edition identifiers are allocated by the TAC in strict sequence and are never reused. The Edition Index in [`README.md`](README.md) records every allocated identifier and the next identifier available for ratification.

## 3. Main-Branch Directory Model

### 3.1. Working documentation

All documentation proposed for the next Trademark Edition is actively maintained in:

```
doc/trademark/next_wip/
```

At minimum, `next_wip` contains:

```
doc/trademark/next_wip/
|-- CaliptraTrademarkPolicy.md
|-- CaliptraTrademarkAuditProcess.md
|-- CaliptraChecklistAndEvaluationMethodology.md
|-- CompatibilityMatrix.md
|-- Caliptra Conformance Program - Participation Form.pdf
|-- Caliptra Conformance Program - Terms and Conditions.pdf
`-- EditionStatus.md
```

Additional controlled documents may be added when required by the Trademark program. The Edition Index MUST identify the complete set of controlled documents expected in an Edition.

The contents of `next_wip` are mutable working documents. They SHOULD identify themselves as a working draft and MUST NOT present an Edition identifier or Revision as ratified. Changes to `next_wip` follow the normal contribution and approval process for Trademark documentation.

### 3.2. Ratified Edition documentation

Every ratified Edition is stored permanently on `main` in:

```
doc/trademark/edition_<identifier>/
```

For example, Edition A is stored in `doc/trademark/edition_A/`. The directory contains the complete, self-contained set of controlled Trademark documents for that Edition, including its Compatibility Matrix and status record.

Ratified Edition directories are not general working areas. After creation, their contents are locked against further edits except through the Revision process in [Section 6](#6-revision-process).

### 3.3. Document version metadata and changelog

Every controlled document in a ratified Edition directory MUST display the same:

- Edition identifier.
- Revision number.
- ratification or revision date.
- Git tag.

Each document MUST also contain a changelog entry for the current Edition and Revision. For the initial ratification, document titles and existing version fields are updated to identify `Edition <identifier>, Revision 1`. Any pre-ratification document changes may be retained below that entry for provenance, but it MUST be clearly distinguished from the ratified Edition changelog.

The Edition identifier in every document MUST match the containing `edition_<identifier>` directory. The Revision number MUST be identical across every controlled document in that directory.

## 4. New Edition Ratification

A new Edition is required when:

1. A substantive Trademark requirement is added, removed, or changed.
2. A new Caliptra `major.minor` release line is made eligible for the Trademark program.
3. The TAC determines that the program should be rebaselined as a new Edition.

A new Caliptra patch release within a `major.minor` line already covered by an Edition does not by itself require a new Edition. It may be added by an Edition Revision under [Section 6](#6-revision-process).

### 4.1. Ratification pull request

After unanimous approval by all TAC Voting Members, one pull request against `main` creates the new `doc/trademark/edition_<identifier>/` directory. That pull request MUST atomically:
TODO: Define an RFC requirement for new Editions? If so, the atomic pull request to establish that edition should already be available (at least in draft form) to go along with RFC.

1. Copy the complete controlled document set from `doc/trademark/next_wip/` into `doc/trademark/edition_<identifier>/`.
2. Update the Edition identifier and Revision number in every copied document to `Edition <identifier>, Revision 1`.
3. Add a corresponding `Revision 1` entry to the changelog in every copied document.
4. Define the Edition's Compatibility Matrix in that directory, including every Caliptra code release eligible for evaluation under the Edition.
5. Set the Edition status and ratification date in `EditionStatus.md`.
6. Update the Edition Index on `main`.
7. Pass the Trademark Edition integrity workflow described in [Section 7](#7-github-workflow-enforcement).

The Edition directory MUST NOT be assembled over multiple pull requests. Until this pull request is merged and its commit is tagged, the proposed Edition has no ratified Trademark authority.

### 4.2. New Edition tag

The commit produced by merging the ratification pull request MUST be tagged:

```
edition-<identifier>-r1
```

The tag is the immutable, citable reference for the initial revision of the Edition. The Edition Index MUST link to both the Edition directory on `main` and its current tag.

## 5. Compatibility Matrix

Each ratified `edition_<identifier>` directory contains its own `CompatibilityMatrix.md`. That file is the authoritative statement of which Caliptra code releases an integrator may use when pursuing a Trademark under that Edition.

The matrix MUST:

- Identify each eligible Caliptra `major.minor` release line.
- Identify explicit applicable patch releases or a closed patch constraint for every relevant Caliptra component. Wildcards and open-ended ranges that would admit an unpublished future patch are prohibited.
- Record the applicable ROM, FMC, Runtime Firmware, and mutable firmware SVN values where relevant.
- Identify whether the entry applies to Caliptra Core, Caliptra Subsystem, or both.
- State the Edition identifier and Revision consistently with every other controlled document in the directory.

Compatibility is established only by an explicit entry in the matrix. A later patch release is not automatically eligible merely because an earlier patch on the same `major.minor` line is listed.

A Revision MAY explicitly add eligible patch releases only within a `major.minor` line already present in that Edition. It MAY also correct a factual error without changing the release intended by the prior ratification. A Revision MUST NOT delete a previously eligible release, relax a constraint, or otherwise expand compatibility implicitly. Adding a different Caliptra `major.minor` line requires a new Edition.

## 6. Revision Process

A Revision is the only permitted modification to an existing `edition_<identifier>` directory. Every Revision, including a final deprecation Revision, requires unanimous approval by all TAC Voting Members.

### 6.1. Permitted Revision content

A Revision MAY:

- Correct typographical errors, broken references, or ambiguous wording without changing a normative requirement.
- Correct factual references to upstream repositories or release artifacts without changing the release intended by the prior ratification.
- Explicitly add Compatibility Matrix entries for eligible patch releases within an already-covered Caliptra `major.minor` line, or correct a factual error without changing the release intended by the prior ratification.
- Update lifecycle information other than a deprecation date.
- Establish a deprecation date only through the final deprecation Revision described in [Section 6.3](#63-final-deprecation-revision); that date cannot later be changed.

A Revision MUST NOT:

- Add, remove, or substantively change a normative requirement.
- Add an eligible Caliptra `major.minor` release line.
- Remove a controlled document required for the Edition.
- Change the Edition identifier.
- reuse, skip, or decrement a Revision number.

Any change outside the permitted categories requires a new Edition.

### 6.2. Atomic Revision pull request

A new Revision MUST be defined atomically in one pull request against `main`. For an Edition currently at Revision `N`, that pull request MUST:

1. Change the Revision number in every controlled document in the Edition directory from `N` to exactly `N+1`.
2. Add a matching `N+1` changelog entry to every controlled document.
3. Keep the Edition identifier and new Revision number consistent across all controlled documents.
4. Include all editorial corrections and all Compatibility Matrix patch-release updates belonging to that Revision.
5. Update `EditionStatus.md` and the Edition Index as applicable.
6. Pass the Trademark Edition integrity workflow.

A Revision MUST NOT be split across multiple pull requests. A pull request MUST NOT define more than one Revision of an Edition.

After merge, the resulting commit MUST be tagged:

```
edition-<identifier>-r<N+1>
```

### 6.3. Final deprecation Revision

A Revision may establish a deprecation date for an Edition. That Revision is the final permitted Revision of the Edition.
TODO: Define an RFC requirement for deprecation? If so, the atomic pull request to deprecate should already be available (at least in draft form) to go along with RFC.

The final deprecation Revision MUST record:

- The effective deprecation date.
- The final Edition and Revision tag.
- Any transition or grace-period rules for engagements already initiated with a Security Review Provider (SRP).
- A successor Edition, if one exists.

After the final deprecation Revision is merged and tagged, the GitHub workflow MUST reject every subsequent change within that `edition_<identifier>` directory. No later patch-release compatibility entries, editorial corrections, status changes, or other Revisions may be made to that Edition.

## 7. GitHub Workflow Enforcement

The repository MUST define a required GitHub workflow, for example `.github/workflows/trademark-edition-integrity.yml`, that evaluates every pull request affecting `doc/trademark/edition_*`.

The workflow MUST enforce the following rules:

1. `next_wip` remains mutable and is not treated as a ratified Edition.
2. A newly created `edition_<identifier>` directory starts at Revision `1`, contains the same complete controlled document set as `next_wip`, and uses the directory's identifier in every document. Differences from `next_wip` are limited to ratification metadata, version histories, status, and finalized compatibility data. TODO: Allow exceptions to the same-fileset requirement on the first few Editions (which are retroactively defined)?
3. For an existing `edition_<identifier>` directory, any content change is accepted only as a Revision.
4. The proposed Revision is greater than the current Revision and is exactly consecutive: `N+1`.
5. Every controlled document in the directory reports the same Edition identifier and Revision.
6. Every controlled document is updated atomically with the new Revision metadata and a matching changelog entry.
7. Compatibility Matrix changes in a Revision explicitly add eligible patch releases only within `major.minor` lines already covered by that Edition, or make permitted factual corrections; they do not delete eligible releases, relax constraints, or implicitly expand compatibility.
8. A new `major.minor` compatibility entry is accepted only in a newly created Edition directory.
9. No controlled document is deleted from a ratified Edition.
10. An Edition whose current tagged Revision establishes a deprecation date cannot be changed.
11. A pull request changes at most one ratified Edition directory and defines at most one new Edition or Revision.
12. Any pull request creating or modifying a ratified `edition_<identifier>` must also appropriately update the Edition Index (add a new row or modify the existing Edition row).

The workflow is a required status check for pull requests to `main`. Repository rules MUST prevent merging a pull request that fails this check.

The workflow validates repository content but does not replace unanimous approval by all TAC Voting Members or code-owner approval. Repository rules MUST protect tags matching `edition-*-r*` against movement, deletion, and reuse. An automated post-merge control, or an equivalently mandatory repository control, MUST create the corresponding tag for every merged Edition or Revision commit and verify that the tag identifies that commit. The Edition or Revision is not ratified until that verification succeeds.

## 8. Lifecycle and Applicability of Tags

A Security Review Provider (SRP) is the approved third-party laboratory that performs the evaluation described by the [`CaliptraTrademarkAuditProcess.md`](CaliptraTrademarkAuditProcess.md). Contact with an SRP is initiated only when the integrator sends a documented request to begin an evaluation and the SRP acknowledges that request in writing. The initiation date is the date of the written acknowledgment; informal or unacknowledged outreach does not qualify.
TODO: Define strict bounds on first engagement with SRP/Edition selection -> actual implementation and TM application? Or leave this up to per-edition STATUS document

An Edition may have the following lifecycle states:

- **Active** - Ratified and available for new Trademark engagements.
- **Superseded** - A later Edition is available or preferred, but this Edition remains usable where its Compatibility Matrix and the Edition Index permit.
- **Deprecated** - Not available for an integrator that has not initiated contact with an SRP before the effective deprecation date.

Every commit merged through a pull request that defines a new Edition or Revision MUST receive the corresponding immutable `edition-<identifier>-r<N>` tag. Tags MUST NOT be moved, deleted, or reused.

A tagged Edition and Revision remains an applicable basis for establishing a Caliptra Trademark in a future product if:

1. The product's Caliptra code releases satisfy that Revision's Compatibility Matrix.
2. The Edition was not deprecated before the integrator initiated contact with an SRP.
3. The integrator completes the audit and licensing process required by that Edition.

If an integrator initiates contact with an SRP before an Edition's effective deprecation date, the final deprecation Revision governs whether and for how long that in-progress engagement may continue. An integrator initiating contact on or after the effective deprecation date MUST use a non-deprecated Edition applicable to its Caliptra code releases.

Integrators, SRPs, and Statements of Conformance MUST cite a specific Edition and Revision tag, not only a directory name, an Edition identifier, or the `main` branch.

## 9. Disambiguation from Caliptra Code Versions

| Concept | Example | Meaning |
| --- | --- | --- |
| Caliptra RTL release | `v2.0.2` | Code release version in `caliptra-rtl` |
| Caliptra firmware release | `2.1.0 (1/3)` | Code version and FMC/FW SVN values |
| Trademark working directory | `next_wip` | Mutable proposal for a future Edition |
| Trademark Edition directory | `edition_A` | Ratified Edition documentation maintained on `main` |
| Trademark Edition and Revision | `Edition A, Revision 2` | Human-readable Trademark document version |
| Trademark tag | `edition-A-r2` | Immutable commit used for audit and citation |

An integrator claiming the Caliptra Trademark MUST identify both the exact Caliptra code releases integrated into the product and the Trademark Edition and Revision tag used for the audit.

## 10. Transition to the Directory Model

This scheme is not operational until `next_wip`, the ratified Edition directories, the Edition Index and related links, the integrity workflow, and the repository and protected-tag rules have been migrated to this model on `main`. References elsewhere in the repository to root-level working documents, per-Edition branches, or tags based on Edition branch tips describe the obsolete proposed branch model and MUST be updated as part of that migration. No Edition or Revision may be ratified under this scheme until these prerequisites are in place.
