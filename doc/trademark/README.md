# Caliptra Trademark Edition Index

This directory hosts the Caliptra Trademark Versioning Scheme and the index of all ratified Trademark Editions.

* [Caliptra Trademark Versioning Scheme](CaliptraTrademarkVersioningScheme.md) — defines how Trademark Editions are named, released (as Git branches and tags), and how they relate to Caliptra code releases.
* The three working-draft Trademark documents — [`CaliptraTrademarkPolicy.md`](../../CaliptraTrademarkPolicy.md), [`CaliptraTrademarkAuditProcess.md`](../../CaliptraTrademarkAuditProcess.md), and [`CaliptraChecklistAndEvaluationMethodology.md`](../../CaliptraChecklistAndEvaluationMethodology.md) — live at the repository root on the `main` branch. Frozen copies are published on a dedicated `edition/<identifier>` branch at each Edition ratification.

> **How to cite an Edition for compliance.** Integrators cite a specific revision tag of the form `edition-<identifier>-r<N>` (for example, `edition-A-r1`), not just the Edition identifier or the branch name. The revision tag is a deterministic, immutable Git reference to the exact frozen text the integrator was audited against.

## Edition Index

| Edition       | Branch                                                                                       | Latest tag        | Status                       | Ratification date | In-scope Caliptra `Major.Minor` lines |
| ------------- | -------------------------------------------------------------------------------------------- | ----------------- | ---------------------------- | ----------------- | ------------------------------------- |
| `Edition A`   | [`edition/A`](https://github.com/chipsalliance/Caliptra/tree/edition/A) *(to be cut)*        | `edition-A-r1` *(to be applied)* | Planned — not yet ratified | TBD               | TBD by TAC at ratification; expected applicability: Caliptra 1.0, 1.1, 1.2, 2.0, 2.1 (each row's minimum patch level pinned in the Edition's `CompatibilityMatrix.md` per [§4.1](CaliptraTrademarkVersioningScheme.md#41-structure)) |

**Next identifier to be allocated:** `B`. See [§3.4 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#34-allocation-of-identifiers).

## Lifecycle status legend

- **Planned** — An Edition row reserved in this index in anticipation of ratification. The branch and initial tag have not yet been created. A Planned Edition does not confer any Trademark authority.
- **Active** — A ratified Edition that is a valid target for new audits. An Edition enters the Active status on ratification and carries the full authority of the Caliptra Trademark requirements; see [§2.1 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#21-edition-lifecycle-status).
- **Superseded** — A later Edition has replaced this one for the Caliptra `Major.Minor` release lines that the later Edition is applicable to. Prior Trademark licenses remain valid; new audits SHOULD target an Active Edition that is applicable to the integrator's release line.
- **Withdrawn** — The TAC has formally revoked this Edition as a target for new audits as of the effective withdrawal date recorded on the Edition branch. Trademark licenses previously issued under a Withdrawn Edition remain valid; no new licenses may be issued on the basis of a Withdrawn Edition after the effective date. See [§5.5 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#55-withdrawal-of-a-ratified-edition).

## Related documents

- [Caliptra Trademark Policy](../../CaliptraTrademarkPolicy.md)
- [Caliptra Trademark Audit Process](../../CaliptraTrademarkAuditProcess.md)
- [Caliptra Checklist and Evaluation Methodology](../../CaliptraChecklistAndEvaluationMethodology.md)
- [Caliptra Contributing Process](../CaliptraContributingProcess.md) — including the RFC procedure invoked when ratifying a new Edition.
