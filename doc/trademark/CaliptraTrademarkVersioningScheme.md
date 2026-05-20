# Caliptra Trademark Versioning Scheme

* Status: Draft
* Scope: Caliptra Trademark requirement documents (Policy, Audit Process, Checklist & Evaluation Methodology)
* See also: [`README.md`](README.md) (Edition Index), [`../../CaliptraTrademarkPolicy.md`](../../CaliptraTrademarkPolicy.md), [`../../CaliptraTrademarkAuditProcess.md`](../../CaliptraTrademarkAuditProcess.md), [`../../CaliptraChecklistAndEvaluationMethodology.md`](../../CaliptraChecklistAndEvaluationMethodology.md), [`../CaliptraContributingProcess.md`](../CaliptraContributingProcess.md)

## 1. Purpose

This document defines the **Caliptra Trademark Versioning Scheme**: a versioning scheme for the set of documents that an integrator's product is audited against in order to receive the Caliptra Trademark grant.

The scheme is deliberately independent of the version numbers used by Caliptra code releases (RTL, ROM, FMC, Runtime FW, Subsystem). Caliptra code components are versioned using semantic versioning as `major.minor.patch`, and not all components share the same `major.minor` at a given point in time (see the *Versioning* section of the repository [`README.md`](../../README.md)). A single ratified version of the Trademark requirements must be able to cover **all** Caliptra release lines that are extant at the time of ratification — for example, Caliptra 1.1 and Caliptra 2.1 may be covered under the same Trademark Edition even though their integration requirements differ substantially. Tying Trademark version numbers to any single component's `major.minor.patch` would make this impossible.

This document defines:

- The identifier scheme used to name Trademark Editions ([§2](#2-identifier-scheme)).
- The Git branch and tag release model that makes each ratified Edition a deterministic, citable commit ([§3](#3-release-model-branches-and-tags)).
- The Compatibility Matrix concept and the normative rules that connect an Edition to specific Caliptra release lines ([§4](#4-compatibility-matrix-and-applicability)).
- The criteria distinguishing an Edition *revision* from a *new Edition*, and the ratification process for each ([§5](#5-revisions-versus-new-editions)).
- The naming plan for Editions beyond `Z` ([§6](#6-post-z-naming-plan)).
- A disambiguation aid that contrasts Edition identifiers with Caliptra component semver ([§7](#7-disambiguation-from-caliptra-component-semver)).

## 2. Identifier Scheme

A **Trademark Edition** is identified by a single uppercase Latin letter, beginning at `A`. There is no reserved codename for the initial Edition: the first Edition is `Edition A`, and the identifier is independent of the Edition's status. After `Z`, the scheme continues with multi-letter identifiers as described in [§6](#6-post-z-naming-plan).

| Element                | Form                                              | Examples                                              |
| ---------------------- | ------------------------------------------------- | ----------------------------------------------------- |
| Edition identifier     | Uppercase Latin letter(s)                         | `A`, `B`, … `Z`, `AA`, `AB`, …                        |
| Edition branch         | `edition/<identifier>`                            | `edition/A`, `edition/B`, `edition/AA`                |
| Edition revision (tag) | `edition-<identifier>-r<N>`, `N` ≥ 1              | `edition-A-r1`, `edition-A-r2`, `edition-B-r1`        |
| Human-readable label   | `Edition <identifier> rev <N>`                    | `Edition A rev 1`, `Edition B rev 3`                  |

**Rationale.** Uppercase letters share no characters with `major.minor.patch` component versions; the `edition/` branch prefix and `edition-` tag prefix prevent collision with code-release tags such as `v1.1.0` in `caliptra-rtl` or `caliptra-1.1` in `caliptra-sw`. The `-rN` revision counter is intentionally a flat integer (not `x.y.z`) to underscore that revisions are *editorial-only* — see [§5](#5-revisions-versus-new-editions).

### 2.1. Edition Lifecycle Status

Each Edition has a lifecycle status independent of its identifier. Defined status values:

- **Preview** — Ratified but explicitly pre-release. Documents partially-complete requirements. Auditors MAY use a Preview Edition to certify integrations; the TAC retains the right to require re-audit against a later Edition if a Preview Edition is materially superseded.
- **Active** — The currently-recommended target for new audits.
- **Superseded** — A later Edition has replaced this one. Prior grants remain valid; new audits SHOULD target an Active Edition.

The status of every Edition is recorded in the [Edition Index](README.md) and in each Edition's `EditionStatus.md` on its branch.

## 3. Release Model: Branches and Tags

Trademark Editions are released as **dedicated Git branches with immutable revision tags**, modeled on the release process used by the [`caliptra-rtl`](https://github.com/chipsalliance/caliptra-rtl) repository. The `main` branch of this repository is the *living working draft* of the Trademark requirement documents; ratified Editions live on their own long-lived release branches.

### 3.1. What lives on `main`

The `main` branch carries:

- The three living working-draft Trademark documents at the repository root:
  - [`CaliptraTrademarkPolicy.md`](../../CaliptraTrademarkPolicy.md)
  - [`CaliptraTrademarkAuditProcess.md`](../../CaliptraTrademarkAuditProcess.md)
  - [`CaliptraChecklistAndEvaluationMethodology.md`](../../CaliptraChecklistAndEvaluationMethodology.md)
- This versioning scheme document and the Edition Index (`README.md`) in `doc/trademark/`.

Each working-draft document at the repository root carries a banner noting that it is a living working draft and pointing readers to the Edition Index for citable frozen versions.

The `main` branch never contains duplicate copies of the requirement documents. There are no per-Edition subdirectories on `main`.

### 3.2. What lives on an Edition branch

When the TAC ratifies a new Edition, branch `edition/<identifier>` is created from the ratification commit on `main` and is never merged back. The branch carries, in addition to the contents inherited from `main` at the branch point:

```
(top of repo on edition/<identifier>)
├── CaliptraTrademarkPolicy.md                       # Frozen at ratification
├── CaliptraTrademarkAuditProcess.md                 # Frozen at ratification
├── CaliptraChecklistAndEvaluationMethodology.md     # Frozen at ratification
└── doc/trademark/
    ├── CompatibilityMatrix.md                       # Per-Edition; see §4
    ├── StatementOfConformanceTemplate.md            # Integrator attestation template
    └── EditionStatus.md                             # Status + revision changelog
```

The frozen working-draft documents remain at the repository root on the Edition branch — they are not moved into `doc/trademark/`. Only the Edition-specific files (`CompatibilityMatrix.md`, `StatementOfConformanceTemplate.md`, `EditionStatus.md`) live under `doc/trademark/` on the branch.

### 3.3. Tags

Each ratified state of an Edition is marked by an immutable Git tag `edition-<identifier>-r<N>` applied to the appropriate commit on the Edition branch. The initial ratification of an Edition is `edition-<identifier>-r1`; subsequent revisions on the same branch increment `N` ([§5](#5-revisions-versus-new-editions)).

When an integrator cites compliance with a Trademark Edition in a Statement of Conformance, they MUST cite a specific revision tag (e.g., `edition-A-r1`), not just the Edition identifier or the branch name. The tag is the deterministic commit reference used by auditors and consumers.

### 3.4. Allocation of identifiers

Edition identifiers are assigned by the TAC at ratification in strict sequence (`A` → `B` → … → `Z` → `AA` → …). Identifiers are never reused, even if an Edition is later moved to `Superseded` status. The current "next identifier" is tracked in the [Edition Index](README.md) for transparency.

## 4. Compatibility Matrix and Applicability

Each Edition branch contains a single `doc/trademark/CompatibilityMatrix.md`. The Compatibility Matrix is the authoritative statement of which Caliptra releases an integrator may audit against under that Edition.

### 4.1. Structure

The matrix lists each covered Caliptra release line as a row keyed by its `Major.Minor` version (e.g., `Caliptra 1.1`, `Caliptra 2.0`). Each row identifies the corresponding upstream branches or tags in [`caliptra-rtl`](https://github.com/chipsalliance/caliptra-rtl), [`caliptra-sw`](https://github.com/chipsalliance/caliptra-sw), and (where applicable) [`caliptra-ss`](https://github.com/chipsalliance/caliptra-ss), and a coverage qualifier indicating which checklist sections apply (e.g., `Core-only`, `Core + Subsystem`).

### 4.2. Normative clauses

The following clauses appear in every Edition's `CompatibilityMatrix.md` and govern the relationship between an Edition and Caliptra release versions:

> **Scope of applicability.** Each row of this Compatibility Matrix identifies a Caliptra `Major.Minor` release line. Every patch release (`Major.Minor.patch`) of a listed line is automatically covered under this Edition. Mutable-firmware SVN bumps (FMC/FW security version increments) within a listed line are likewise covered. Patch releases or SVN bumps of an unlisted `Major.Minor` line are **not** covered.

> **Ineligibility.** Any Caliptra `Major.Minor` release line that is not listed in this Compatibility Matrix is **ineligible** for the Caliptra Trademark grant under this Edition. An integration based on an unlisted release line must be evaluated against a different Edition whose Compatibility Matrix lists it.

### 4.3. Why `Major.Minor` (and not `Major.Minor.patch`)

Patch releases of Caliptra components are, by the project's versioning conventions ([`README.md`](../../README.md), *Versioning*), reserved for bug fixes against an existing `Major.Minor` feature set. They do not introduce new features and therefore do not change the integration surface that the Trademark requirements evaluate. Scoping Edition applicability at the `Major.Minor` granularity keeps the matrix maintainable while ensuring that patch releases are automatically in scope without TAC action.

## 5. Revisions Versus New Editions

The scheme distinguishes two operations: a **revision** of an existing Edition (cheap, editorial-only) and a **new Edition** (TAC ratification, comprehensive review).

### 5.1. Criteria for an Edition revision (`-r<N+1>`)

A change qualifies as a revision on the existing Edition branch **if and only if** *all* of the following hold:

1. The change is editorial in nature — a typographical correction, a cross-reference fix, a clarification of ambiguous wording, or a correction to a documented unimplementability.
2. The change does **not** add, remove, or modify any normative requirement. ("Normative" means any statement using the RFC 2119 keywords used in the Checklist: `MUST`, `MUST NOT`, `SHALL`, `SHALL NOT`, `REQUIRED`, `RECOMMENDED`, `SHOULD`, `SHOULD NOT`, `MAY`, `OPTIONAL`.)
3. The change does **not** alter the Compatibility Matrix — neither adding nor removing covered `Major.Minor` lines, nor changing the upstream branches/tags enumerated for any listed line.
4. The change does **not** alter the Edition's lifecycle status. (Status transitions are tracked in `EditionStatus.md` but are not classified as revisions in this sense.)

### 5.2. Criteria triggering a new Edition

A change **must** trigger a new Edition (a new `edition/<next-identifier>` branch) if **any** of the following hold:

1. A new Caliptra `Major.Minor` release has been published since the current Edition was ratified, and the TAC wishes the Trademark scheme to cover it. (Patch releases never trigger a new Edition because they are auto-covered per [§4.2](#42-normative-clauses).)
2. A substantive requirement change is being introduced — i.e., any change that does not meet all four criteria in [§5.1](#51-criteria-for-an-edition-revision--rn1).
3. The Compatibility Matrix is being modified — adding a covered `Major.Minor` line, removing one, or changing the enumerated upstream branches/tags for an already-covered line.
4. The TAC formally supersedes the current Edition.

### 5.3. Ratification process — new revision

1. A pull request lands the editorial change on the relevant `edition/<identifier>` branch (changes may be cherry-picked from `main` if applicable).
2. The PR updates `doc/trademark/EditionStatus.md` on the branch with a changelog entry for the new revision.
3. Approval per repository governance for the trademark documents (TAC review).
4. After merge, tag `edition-<identifier>-r<N+1>` is applied to the new tip of the branch.
5. A follow-up PR against `main` updates the [Edition Index](README.md) to point to the new latest tag.

### 5.4. Ratification process — new Edition

1. An RFC issue is opened against this repository, titled `[RFC] Ratify Caliptra Trademark Edition <identifier>`, following [`doc/CaliptraContributingProcess.md`](../CaliptraContributingProcess.md). The RFC enumerates: the proposed Edition identifier (the next in sequence per [§3.4](#34-allocation-of-identifiers)), the working-draft commit SHA on `main` to be frozen, the proposed Compatibility Matrix, and the justification (which trigger from [§5.2](#52-criteria-triggering-a-new-edition) applies).
2. The TAC reviews and votes. Trademark-related governance documents (consistent with the existing trademark documents listed in [`CODEOWNERS`](../../CODEOWNERS)) require unanimous approval of TAC Voting Members.
3. Upon approval, branch `edition/<identifier>` is created from the approved commit SHA.
4. The Edition-specific files (`CompatibilityMatrix.md`, `StatementOfConformanceTemplate.md`, `EditionStatus.md`) are added on the branch.
5. Tag `edition-<identifier>-r1` is applied to the tip of the new branch.
6. A PR against `main` updates the [Edition Index](README.md) to add the new Edition row and, where applicable, moves the prior Edition's status to `Superseded`.

## 6. Post-`Z` Naming Plan

When the single-letter Edition series exhausts `Z`, the scheme continues with multi-letter identifiers in spreadsheet-column order:

```
A → B → C → … → Y → Z → AA → AB → AC → … → AZ → BA → BB → … → ZY → ZZ → AAA → AAB → …
```

- Branch form: `edition/AA`, `edition/AB`, … `edition/ZZ`, `edition/AAA`, …
- Tag form: `edition-AA-r1`, `edition-AB-r1`, … `edition-AAA-r1`, …
- Human label: `Edition AA rev 1`, … `Edition AAA rev 1`.

The step from `ZZ` to `AAA` is named explicitly here so that the scheme never has to be amended under time pressure when the series approaches that boundary. The same generalization continues thereafter (`AAA` → `AAB` → … → `ZZZ` → `AAAA`, and so on).

## 7. Disambiguation from Caliptra Component Semver

The Edition identifier is intentionally and visibly distinct from Caliptra component version strings.

| Concept                              | Example                  | Notes                                                                                  |
| ------------------------------------ | ------------------------ | -------------------------------------------------------------------------------------- |
| Caliptra RTL release                 | `v2.1.0`                 | A semver tag in [`caliptra-rtl`](https://github.com/chipsalliance/caliptra-rtl).       |
| Caliptra ROM release                 | `2.0.2`                  | A `major.minor.patch` version in [`caliptra-sw`](https://github.com/chipsalliance/caliptra-sw). |
| Caliptra FMC/FW version              | `2.1.0 (1/3)`            | `major.minor.patch (FMC_SVN/FW_SVN)` per the repository `README.md`.                   |
| Caliptra Trademark Edition (identifier) | `Edition A`           | A letter in the Latin alphabet; no integers.                                           |
| Caliptra Trademark Edition (branch)  | `edition/A`              | Git branch in this repository.                                                         |
| Caliptra Trademark Edition (revision tag) | `edition-A-r1`     | Git tag in this repository; the citable compliance reference.                          |

Integrators claiming the Caliptra Trademark MUST identify **both** (i) the Caliptra release line they integrate and the specific upstream tags used, and (ii) the Trademark Edition revision tag they were audited against. Consumers can then determine, by consulting the Edition's Compatibility Matrix, whether the integrator's Caliptra release line is actually covered under the cited Edition.
