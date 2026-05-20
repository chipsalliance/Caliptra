# Caliptra Trademark Edition Index

This directory hosts the Caliptra Trademark Versioning Scheme and the index of all ratified Trademark Editions.

* [Caliptra Trademark Versioning Scheme](CaliptraTrademarkVersioningScheme.md) — defines how Trademark Editions are named, released (as Git branches and tags), and how they relate to Caliptra code releases.
* The three working-draft Trademark documents — [`CaliptraTrademarkPolicy.md`](../../CaliptraTrademarkPolicy.md), [`CaliptraTrademarkAuditProcess.md`](../../CaliptraTrademarkAuditProcess.md), and [`CaliptraChecklistAndEvaluationMethodology.md`](../../CaliptraChecklistAndEvaluationMethodology.md) — live at the repository root on the `main` branch. Frozen copies are published on a dedicated `edition/<identifier>` branch at each Edition ratification.

> **How to cite an Edition for compliance.** Integrators cite a specific revision tag of the form `edition-<identifier>-r<N>` (for example, `edition-A-r1`), not just the Edition identifier or the branch name. The revision tag is a deterministic, immutable Git reference to the exact frozen text the integrator was audited against.

## Edition Index

| Edition       | Branch                                                                                       | Latest tag        | Status                       | Ratification date | Covered Caliptra `Major.Minor` lines |
| ------------- | -------------------------------------------------------------------------------------------- | ----------------- | ---------------------------- | ----------------- | ------------------------------------ |
| `Edition A`   | [`edition/A`](https://github.com/chipsalliance/Caliptra/tree/edition/A) *(to be cut)*        | `edition-A-r1` *(to be applied)* | Planned — not yet ratified | TBD               | TBD by TAC at ratification; expected coverage: Caliptra 1.0, 1.1, 2.0, 2.1 |

**Next identifier to be allocated:** `B`. See [§3.4 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#34-allocation-of-identifiers).

## Lifecycle status legend

- **Planned** — An Edition row reserved in this index in anticipation of ratification. The branch and initial tag have not yet been created.
- **Preview** — Ratified but explicitly pre-release. Auditors MAY use a Preview Edition to certify integrations; see [§2.1 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#21-edition-lifecycle-status).
- **Active** — The currently-recommended target for new audits.
- **Superseded** — A later Edition has replaced this one. Prior grants remain valid; new audits SHOULD target an Active Edition.

## Related documents

- [Caliptra Trademark Policy](../../CaliptraTrademarkPolicy.md)
- [Caliptra Trademark Audit Process](../../CaliptraTrademarkAuditProcess.md)
- [Caliptra Checklist and Evaluation Methodology](../../CaliptraChecklistAndEvaluationMethodology.md)
- [Caliptra Contributing Process](../CaliptraContributingProcess.md) — including the RFC procedure invoked when ratifying a new Edition.
