# Caliptra Trademark Edition Index

This directory hosts the [Caliptra Trademark Versioning Scheme](CaliptraTrademarkVersioningScheme.md) and the index of all allocated Trademark Edition identifiers.

All working and ratified Trademark content is maintained on `main`. The mutable `doc/trademark/next_wip/` working directory contains the unratified proposal for the next Edition and cannot be used for an audit or license. Each ratified Edition is preserved permanently in `doc/trademark/edition_<identifier>/`.

> **How to cite an Edition for compliance.** Integrators cite the immutable Edition and Revision tag `edition-<identifier>-r<N>` (for example, `edition-A-r1`). A directory name, Edition identifier, or the `main` branch is not a compliance citation.

## Edition Index

| Edition | Directory on `main` | Current tag | Lifecycle status | Ratification date | Compatibility Matrix |
| --- | --- | --- | --- | --- | --- |
| `Edition A` | Not yet created | Not yet created | Not ratified; no lifecycle status | Not available | Not available |

`Edition A` is allocated, but the directory, tag, status record, and Compatibility Matrix required for ratification do not yet exist. It therefore has no ratified Trademark authority. When an Edition is ratified, this index links both its permanent directory on `main` and its current immutable tag.

**Next identifier to be allocated:** `B`. See [Section 2 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#2-identifier-scheme).

## Controlled document set

The complete controlled document set expected in `next_wip` and each Edition directory is:

- `CaliptraTrademarkPolicy.md`
- `CaliptraTrademarkAuditProcess.md`
- `CaliptraChecklistAndEvaluationMethodology.md`
- `CompatibilityMatrix.md`
- `Caliptra Conformance Program - Participation Form.pdf`
- `Caliptra Conformance Program - Terms and Conditions.pdf`
- `EditionStatus.md`

Additional controlled documents may be added when required by the Trademark program. See [Section 3.1 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#31-working-documentation).

## Lifecycle status legend

- **Active** - Ratified and available for new Trademark engagements.
- **Superseded** - A later Edition is available or preferred, but this Edition remains usable where its Compatibility Matrix and this index permit.
- **Deprecated** - Not available to an integrator that did not initiate contact with a Security Review Provider (SRP) before the effective deprecation date.

See [Section 8 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#8-lifecycle-and-applicability-of-tags) for requirements around Edition deprecation and SRP contact.

## Transition status

The directory model is not operational until `next_wip`, ratified Edition directories, this index and related links, the integrity workflow, and repository and protected-tag rules have all been migrated to the model on `main`. No Edition or Revision may be ratified under the scheme before those prerequisites are complete. See [Section 10 of the Versioning Scheme](CaliptraTrademarkVersioningScheme.md#10-transition-to-the-directory-model).

## Related documents

- [Caliptra Trademark Policy](CaliptraTrademarkPolicy.md)
- [Caliptra Trademark Audit Process](CaliptraTrademarkAuditProcess.md)
- [Caliptra Checklist and Evaluation Methodology](CaliptraChecklistAndEvaluationMethodology.md)
- [Caliptra Contributing Process](../CaliptraContributingProcess.md)
