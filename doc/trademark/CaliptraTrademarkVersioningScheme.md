# Caliptra Trademark Versioning Scheme

* Status: Draft
* Scope: Caliptra Trademark requirement documents (Policy, Audit Process, Checklist & Evaluation Methodology)
* See also: [`README.md`](README.md) (Edition Index), [`../../CaliptraTrademarkPolicy.md`](../../CaliptraTrademarkPolicy.md), [`../../CaliptraTrademarkAuditProcess.md`](../../CaliptraTrademarkAuditProcess.md), [`../../CaliptraChecklistAndEvaluationMethodology.md`](../../CaliptraChecklistAndEvaluationMethodology.md), [`../CaliptraContributingProcess.md`](../CaliptraContributingProcess.md)

## 1. Purpose

This document defines the **Caliptra Trademark Versioning Scheme**: a versioning scheme for the set of documents that an integrator's product is audited against in order to receive the Caliptra Trademark license.

The scheme is deliberately independent of the version numbers used by Caliptra code releases (RTL, ROM, FMC, Runtime FW, Subsystem). Caliptra code components are versioned using semantic versioning as `major.minor.patch`, and not all components share the same `major.minor` at a given point in time (see the *Versioning* section of the repository [`README.md`](../../README.md)). A single ratified version of the Trademark requirements can cover multiple Caliptra release lines at once — for example, Caliptra 1.1 and Caliptra 2.1 may be covered under the same Trademark Edition even though their integration requirements differ substantially. The precise set of Caliptra release lines covered by any given Edition is defined by that Edition's [Compatibility Matrix](#4-compatibility-matrix-and-applicability) (not by a fuzzy notion of "all releases that exist at ratification time"); the Compatibility Matrix is itself versioned alongside the Edition and updated by ratified [Revisions](#5-revisions-versus-new-editions). Tying Trademark version numbers to any single component's `major.minor.patch` would make this multi-release coverage impossible.

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

**Rationale.** Uppercase letters share no characters with `major.minor.patch` component versions; the `edition/` branch prefix and `edition-` tag prefix prevent collision with code-release tags such as `v1.1` in `caliptra-rtl` or `caliptra-1.1` branches in `caliptra-sw`. The `-rN` revision counter is intentionally a flat integer (not `x.y.z`) to underscore that revisions never introduce substantive change to the Trademark requirements; they pin newly-released Caliptra patches into the Edition's Compatibility Matrix and apply editorial corrections — see [§5](#5-revisions-versus-new-editions).

### 2.1. Edition Lifecycle Status

Each Edition has a lifecycle status independent of its identifier. Defined status values:

- **Active** — A ratified Edition that is a valid target for new audits. Every Edition enters the **Active** status upon ratification (i.e., when its `edition/<identifier>` branch is cut and its `edition-<identifier>-r1` tag is applied) and carries the full authority of the Caliptra Trademark requirements regardless of whether later, more comprehensive Editions are anticipated.
- **Superseded** — A later Edition has replaced this one for the Caliptra `Major.Minor` release lines that the later Edition covers. Trademark licenses previously issued under a Superseded Edition remain valid; new audits against the Superseded Edition for those release lines SHOULD instead target an Active Edition that covers them. An Edition remains the authoritative target for any `Major.Minor` release line it covers that is not covered by any later Active Edition.
- **Withdrawn** — The TAC has formally revoked this Edition as a target for new audits. Trademark licenses previously issued under a Withdrawn Edition remain valid; **no new Trademark licenses may be issued on the basis of a Withdrawn Edition** after its effective withdrawal date. The transition into `Withdrawn` is performed via a revision on the Edition's own branch — see [§5.5](#55-withdrawal-of-a-ratified-edition).

The status of every Edition is recorded in the [Edition Index](README.md) on `main` and in that Edition's `EditionStatus.md` on its branch. `EditionStatus.md` on the Edition branch is the source of truth; the Edition Index on `main` mirrors it. Any status transition (Active → Superseded, or Active → Withdrawn) is therefore applied by a revision on the Edition branch (updating `EditionStatus.md`) accompanied by a corresponding PR on `main` that updates the Edition Index.

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

`edition/*` branches and `edition-*-r*` tags are protected by repository rules: branches reject force-pushes and deletion, and tags are immutable once published. See [`GitHubRules.md`](../../GitHubRules.md) for the authoritative ruleset.

### 3.4. Allocation of identifiers

Edition identifiers are assigned by the TAC at ratification in strict sequence (`A` → `B` → … → `Z` → `AA` → …). Identifiers are never reused, even if an Edition is later moved to `Superseded` status. The current "next identifier" is tracked in the [Edition Index](README.md) for transparency.

## 4. Compatibility Matrix and Applicability

Each Edition branch contains a single `doc/trademark/CompatibilityMatrix.md`. The Compatibility Matrix is the authoritative statement of which Caliptra releases an integrator may audit against under that Edition. It is binding: an integration that does not match the matrix is ineligible for the Caliptra Trademark license under this Edition (see [§4.2](#42-normative-clauses)).

### 4.1. Structure

The matrix lists every covered Caliptra release line as a row keyed by its `Major.Minor` version (e.g., `Caliptra 1.1`, `Caliptra 1.2`, `Caliptra 2.0`). Each row enumerates, for every relevant Caliptra component repository, **both** the covered `Major.Minor` version **and** the **minimum patch level** on that minor that this Edition covers. The components tracked are at minimum:

- [`caliptra-rtl`](https://github.com/chipsalliance/caliptra-rtl) — RTL release.
- [`caliptra-sw`](https://github.com/chipsalliance/caliptra-sw) — ROM, FMC, and Runtime FW releases (versioned independently within `caliptra-sw`; cite the upstream tag form, including FMC/FW SVN where applicable).
- [`caliptra-ss`](https://github.com/chipsalliance/caliptra-ss) — Subsystem release, where the row's coverage qualifier indicates Subsystem applicability.

Each row also carries a **coverage qualifier** indicating which checklist sections apply to the row (e.g., `Core-only`, `Core + Subsystem`). Patch-level pins are recorded as the upstream `Major.Minor.patch` (and, for mutable firmware, the FMC/FW SVN pair) that represents the *minimum* release an integrator may consume on that line under this Edition.

A row's patch pins MAY be updated by a subsequent revision of the same Edition — see [§5.1](#51-criteria-for-an-edition-revision--rn1).

### 4.2. Normative clauses

The following clauses appear in every Edition's `CompatibilityMatrix.md` and govern the relationship between an Edition and Caliptra release versions:

> **Scope of applicability.** Each row of this Compatibility Matrix identifies a Caliptra `Major.Minor` release line and the minimum patch level (and minimum FMC/FW SVN, where applicable) on that line covered by this Edition. An integration is eligible under this Edition only if, for every Caliptra component listed in the row, the integration consumes a release that is **at or above** the minimum pinned by this Edition's current revision and is on the **same** `Major.Minor` line as the pinned release.

> **Patch coverage is by explicit ratification, not automatic.** Patch releases of Caliptra components published *after* this Edition revision's tag was applied are **not** automatically covered by this Edition. Coverage of newly-published patch releases is established by ratifying a new revision of this Edition that raises the relevant patch pin (see [§5.1](#51-criteria-for-an-edition-revision--rn1) criterion 3). Until that revision is ratified and tagged, the last pinned patch level remains the binding floor.

> **Integrator obligation.** Integrators pursuing the Caliptra Trademark under this Edition MUST integrate at or above every minimum release pinned by this Edition's Compatibility Matrix for every component listed in their target row. A Statement of Conformance that cites this Edition but consumes an upstream release below the pinned minimum is invalid.

> **Ineligibility.** Any Caliptra `Major.Minor` release line that is not listed in this Compatibility Matrix is **ineligible** for the Caliptra Trademark license under this Edition. An integration based on an unlisted release line must be evaluated against a different Edition whose Compatibility Matrix lists that line.

### 4.3. Why `Major.Minor` granularity with explicit patch pins

Patch releases of Caliptra components are, by the project's versioning conventions ([`README.md`](../../README.md), *Versioning*), reserved for bug fixes against an existing `Major.Minor` feature set. They do not add features and so do not by themselves change the integration surface that the Trademark requirements evaluate. However, individual patch releases sometimes carry **security-relevant** fixes (errata, SVN bumps). Pinning a minimum patch level per row — and allowing that pin to be raised by a revision — lets the TAC require integrators to consume known-good patch releases without forcing a new Edition for every routine patch. This balances stability of the requirement set against the project's security posture.

## 5. Revisions Versus New Editions

The scheme distinguishes two operations: a **revision** of an existing Edition (no substantive change to requirements, but may pin newer patch releases or fix factual references) and a **new Edition** (a new branch and `-r1` tag, required when substantive changes are needed or when new `Major.Minor` Caliptra release lines must be covered).

Both operations require **unanimous approval of all TAC Voting Members** — there are no lightweight, non-unanimous changes to a ratified Edition once it has been published. The distinction between a revision and a new Edition determines *what artifact is produced* (a new tag on an existing branch vs. a new branch), not the rigor of governance applied.

### 5.1. Criteria for an Edition revision (`-r<N+1>`)

A change qualifies as a revision on the existing Edition branch **if and only if** *all* of the following hold:

1. The change does **not** add, remove, or modify any normative requirement on integrators. ("Normative" means any statement using the RFC 2119 keywords used in the Checklist: `MUST`, `MUST NOT`, `SHALL`, `SHALL NOT`, `REQUIRED`, `RECOMMENDED`, `SHOULD`, `SHOULD NOT`, `MAY`, `OPTIONAL`.)
2. The change does **not** add or remove any covered Caliptra `Major.Minor` release line from the Compatibility Matrix, and does **not** lower (relax) any existing minimum patch pin.
3. The change is one (or more) of the following editorial categories:
   - **Typographical and clarification fixes** — typos, broken cross-references, ambiguous wording made unambiguous without changing meaning, restatement of intent for readability.
   - **Factual upstream-reference corrections** — corrections to the upstream `caliptra-rtl` / `caliptra-sw` / `caliptra-ss` tag, branch, or repository references named in the Compatibility Matrix where the upstream reference itself was misstated, renamed, or relocated. These are editorial because the *intent* of the original ratification (which upstream release is in scope) is preserved; only the citation is corrected.
   - **Patch-coverage updates** — raising the minimum patch pin (or minimum FMC/FW SVN) for an already-covered `Major.Minor` line to incorporate newly-published upstream patch releases. This is the mechanism by which Editions track patch releases of Caliptra components; see [§4.2](#42-normative-clauses).
   - **Lifecycle status transitions** — updating `EditionStatus.md` to mark the Edition as `Superseded` or `Withdrawn`, with the associated metadata required by [§2.1](#21-edition-lifecycle-status) and [§5.5](#55-withdrawal-of-a-ratified-edition).
4. The Compatibility Matrix is not modified in any way other than those permitted in criterion 3.

If a change does not fit cleanly within these categories — for example, if it would alter the substance of any integration requirement, add or remove a checklist item, or change the set of Caliptra `Major.Minor` lines that the Edition covers — it MUST be ratified as a new Edition instead.

### 5.2. Criteria triggering a new Edition

A change **must** trigger a new Edition (a new `edition/<next-identifier>` branch) if **any** of the following hold:

1. A new Caliptra `Major.Minor` release has been published since the current Edition was ratified, and the TAC wishes the Trademark scheme to cover it.
2. A substantive change to the Trademark requirements is being introduced — i.e., any change that does not meet all four criteria in [§5.1](#51-criteria-for-an-edition-revision--rn1) (in particular, any change to a normative requirement on integrators).
3. The TAC formally supersedes the current Edition (e.g., as part of a coordinated rebaseline of the Trademark requirements).

Patch releases of Caliptra components do **not** trigger a new Edition; they are folded into the existing Edition by a revision per [§5.1](#51-criteria-for-an-edition-revision--rn1) criterion 3.

### 5.3. Ratification process — new revision

1. A pull request lands the editorial change(s) on the relevant `edition/<identifier>` branch. Changes may be cherry-picked from `main` if applicable.
2. The PR updates `doc/trademark/EditionStatus.md` on the branch with a changelog entry naming the new revision tag, the date, and a brief description per the categories in [§5.1](#51-criteria-for-an-edition-revision--rn1).
3. Where the revision raises a patch pin, the PR also updates `doc/trademark/CompatibilityMatrix.md` on the branch with the new pinned upstream release reference for each affected component.
4. The PR is reviewed by the trademark-document code owners (see [`CODEOWNERS`](../../CODEOWNERS)).
5. The new revision must receive **unanimous approval of all TAC Voting Members** prior to merge.
6. After merge, tag `edition-<identifier>-r<N+1>` is applied to the new tip of the branch. The branch and the tag are subject to the protection rules described in [`GitHubRules.md`](../../GitHubRules.md).
7. A follow-up PR against `main` updates the [Edition Index](README.md) to point to the new latest tag and to mirror any status change to the Edition.

### 5.4. Ratification process — new Edition

1. An RFC issue is opened against this repository, titled `[RFC] Ratify Caliptra Trademark Edition <identifier>`, following [`doc/CaliptraContributingProcess.md`](../CaliptraContributingProcess.md). The RFC enumerates: the proposed Edition identifier (the next in sequence per [§3.4](#34-allocation-of-identifiers)), the working-draft commit SHA on `main` to be frozen, the proposed Compatibility Matrix (with explicit minimum patch pins per row, per [§4.1](#41-structure)), and the justification (which trigger from [§5.2](#52-criteria-triggering-a-new-edition) applies).
2. The TAC reviews and votes. Ratification requires **unanimous approval of all TAC Voting Members**, consistent with the governance applied to the trademark documents listed in [`CODEOWNERS`](../../CODEOWNERS).
3. Upon approval, branch `edition/<identifier>` is created from the approved commit SHA and is immediately subject to the protection rules in [`GitHubRules.md`](../../GitHubRules.md).
4. The Edition-specific files (`CompatibilityMatrix.md`, `StatementOfConformanceTemplate.md`, `EditionStatus.md`) are added on the branch.
5. Tag `edition-<identifier>-r1` is applied to the tip of the new branch.
6. A PR against `main` updates the [Edition Index](README.md) to add the new Edition row. If the new Edition supersedes one or more existing Editions for any `Major.Minor` line, a coordinated revision on each affected prior Edition's branch updates its `EditionStatus.md` to `Superseded` per [§5.1](#51-criteria-for-an-edition-revision--rn1) criterion 3 (lifecycle status transition), and the Edition Index on `main` is updated to reflect those status changes.

### 5.5. Withdrawal of a ratified Edition

An Active or Superseded Edition may be **withdrawn** by the TAC. Withdrawal removes an Edition as a target for *new* audits but does not invalidate Trademark licenses previously issued under it.

Withdrawal is performed as a revision on the Edition's own branch (per [§5.1](#51-criteria-for-an-edition-revision--rn1) criterion 3 / lifecycle-status transition):

1. An RFC issue is opened, titled `[RFC] Withdraw Caliptra Trademark Edition <identifier>`. It states the rationale for withdrawal (e.g., the Edition's requirements are no longer believed sufficient to license the Caliptra Trademark on new integrations) and the proposed **effective withdrawal date** and **in-flight grace window** (see below).
2. The TAC reviews and votes. Withdrawal requires **unanimous approval of all TAC Voting Members**.
3. Upon approval, a PR lands on the Edition's branch that updates `doc/trademark/EditionStatus.md` to set status to `Withdrawn` and to record:
   - The **effective withdrawal date** — the date after which **no new Caliptra Trademark licenses may be issued** on the basis of this Edition.
   - An **in-flight grace window** — a reasonable period (typically not less than 180 days from the date the withdrawal revision is tagged) during which audits and Statements of Conformance that were already in active review against this Edition at the time the withdrawal was ratified may be completed and licensed. The grace window is intended to protect integrators whose review cycle is materially in progress; it is not a mechanism for new audits to begin against the Withdrawn Edition.
   - A pointer to the successor Edition(s), if any, that integrators should retarget against.
4. Tag `edition-<identifier>-r<N+1>` is applied to the tip of the branch.
5. A follow-up PR against `main` updates the [Edition Index](README.md) to reflect the `Withdrawn` status and the effective withdrawal date.

After the in-flight grace window expires, the Edition is **closed to all new license issuance**. Existing Trademark licenses already issued under the Edition remain valid and are not retroactively invalidated by withdrawal — but consumers should note that no new licenses may be issued on the basis of the Withdrawn Edition, and integrators preparing new products MUST target an Active Edition.

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
| Caliptra RTL release                 | `v2.1`                   | A semver tag in [`caliptra-rtl`](https://github.com/chipsalliance/caliptra-rtl) (see that repository's `HWReleaseProcess.md`). |
| Caliptra ROM release                 | `2.0.2`                  | A `major.minor.patch` version in [`caliptra-sw`](https://github.com/chipsalliance/caliptra-sw). |
| Caliptra FMC/FW version              | `2.1.0 (1/3)`            | `major.minor.patch (FMC_SVN/FW_SVN)` per the repository `README.md`.                   |
| Caliptra Trademark Edition (identifier) | `Edition A`           | A letter in the Latin alphabet; no integers.                                           |
| Caliptra Trademark Edition (branch)  | `edition/A`              | Git branch in this repository.                                                         |
| Caliptra Trademark Edition (revision tag) | `edition-A-r1`     | Git tag in this repository; the citable compliance reference.                          |

Integrators claiming the Caliptra Trademark MUST identify **both** (i) the Caliptra release line they integrate and the specific upstream tags used, and (ii) the Trademark Edition revision tag they were audited against. Consumers can then determine, by consulting the Edition's Compatibility Matrix, whether the integrator's Caliptra release line is actually covered under the cited Edition.
