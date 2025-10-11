# Contributing to Caliptra

Top level things to know

* Use of Caliptra requires no CLA.

* Contribution to Caliptra source requires [CHIPS
  CLA](#contributor-license-agreement)

* Contribution as a named author of Caliptra specs released to OCP requires [OCP
  paperwork](https://www.opencompute.org/contributions/how-to-contribute)

* Approval of Caliptra integration compliance is
  [handled](CaliptraTrademarkPolicy.md) by Caliptra TAC

* [License to use Caliptra trademark](CaliptraTrademarkPolicy.md) is handled by
  Linux Foundation after Caliptra TAC integration compliance approval

## Contributor License Agreement

Per the [Charter](CaliptraWGTechnicalCharter.md), contributors to Caliptra
must have signed the CHIPS CLA.

## Contributing Process

To contribute to any facet of the Caliptra Project (e.g., hardware, software, or other),
follow the [Caliptra Contributing Process](doc/CaliptraContributingProcess.md) guide.

## Guidelines for code contributions

* Changes must be made via pull request
* [Branch protection rules](GitHubRules.md) ensure pull requests are reviewed
  by project members
* [Maintainers](MAINTAINERS.md) are expected to enforce `CODEOWNERS` rights
  where necessary. Maintainers are also the sole owners of the repo's
  configuration.
* The branch protection rules include constraints to maintain a linear history
  and avoid merges in pull requests.
* Please maintain a clean commit history on the `main` branch.
  - Effort should be made to ensure Pull Requests are clean and pass required
    tests, to prevent a long series of subsequent Pull Requests with simple
    'fixup' patches.
  - By the same criteria, if a Pull Request has a number of 'fixup' patches, it
    must be Squash and Merged.
  - Whereas a Pull Request with logically separate, well defined commits, with
    articulate descriptions, can be merged without squashing.
* New code files must include the Apache license 2.0 header. Commit verification
  tools enforce this.
* With the exception of the Rust toolchain, all third-party code necessary for
  building release firmware binaries must be placed in the
  `caliptra-sw/third-party` directory
* Third party vendored repos included into Caliptra repos may not be ASL 2.0
  license. However, all vendored repos must be ASL 2.0 compliant and not
  introduce additional restrictions or encumbrances. Ask the TAC if in doubt.
* Fork the repos into your personal repo, and create pull requests from your
  personal repo. Do not pollute the main repo with your personal branches.

## Design discussion

* All design issues are discussed via GitHub issues.
* Please reference the issue in your commit where appropriate.
* Chat channels should be primarily used for short, tactical discussions
  (example, coordinate resolution of a merge conflict, coordinate update of
  settings, meeting coordinates)
* Chat channel participation, however, is restricted to developers who have
  signed the CHIPS CLA, or are affiliiated with companies that have signed the
  CHIPS CLA.

## Branch policy

* For all repos there is a single `main` branch.
* Private dev branches for organizations must integrate back to main
* TODO: upload the schematic and reference, for RTL branch policy
* `$major.8` tags must exist in `main`. At that point changes to RTL must follow
  the [RFC Process](doc/CaliptraContributingProcess.md).
* `$major.9` tags for RTL mark the beginning of bug fixes only period.
* Specific integrations should be forked off `main` into a release branch at a
  named tag. Example:
  - `release/1.2.1` forks off `main` at tag `1.2`.
  - Linear history in that branch includes tags `1.2.1.0`, `1.2.1.1` and so on
  - A new integration can branch off `release/1.2.2` at tag `1.2` as well.
  - A new integration can branch off `release/1.3.1` at tag `1.3` as well
* Branch protection rules apply to `main` and `release/*` branches.
* All commits in `release/*` branches must be found in `main` as well. Since bug
  fixes added to a `release` branch may be merged into `main` later in the
  history, the `release/` branch commit must include a `Release-Commit=$SHA`
  footer in its description. The `$SHA` points to the main branch commit ref.

A known exception here is that the first commit of Caliptra public RTL already
started at `0p8`.