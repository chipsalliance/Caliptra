# Contributing to Caliptra

## Contributor License Agreement

Per the [Charter](Caliptra_WG_Technical_Charter.md), contributors to Caliptra
must have signed the CHIPS CLA.

## Guidelines for code contributions

* Changes must be made via pull request
* [Branch protection rules](github_rules.md) ensure pull requests are reviewed
  by project members
* [Maintainers](MAINTAINERS.md) are expected to enforce `CODEOWNERS` rights
  where necessary. Maintainers are also the sole owners of the repo's
  configuration.
* The branch protection rules include constraints to maintain a linear history
  and avoid merges in pull requests.
* Please keep a clean commit history, and no long series
  of "fixup" patches. Use GitHub's "Squash and merge" option if necessary.
* New code files must include the Apache license 2.0 header. Commit verification
  tools enforce this.
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
  CCB rules below
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
started at `0p8`

## CCB Issues

RTL design changes or additions after a `$major.5` tag must be bound to a GitHub
issue, and the issue must include this questionnaire in its description.

(Bug fixes do not need this step)

* Is the RTL change due to a Spec change? (Yes/No)
* Is the Spec change approved? (Yes/No)
* Is the spec updated? (Yes/No)
* Is the change needed in the `p8` or `$major.0` milestone?
  - Note: What item qualifies as P1/MVP item is set by Caliptra Arch WG leads
* Does it have silicon area impact? (Area size/No)
* Does it have timing impact? (Breakdown/No)
* If the change impacts ROM/FMC/RT, did the FW reps approve the change already? (Yes/No)
* Why should the change be intercepted in `$major`?
* Can the change be handled outside of Caliptra?
* If there is a schedule impact to a `p8` or `$major.0` milestone, is it
  approved by voting leads? (Yes/No)
* If change completed (implies schedule impact is zero):
  - Lint passing (Yes/No)
  - Gate count delta (Count/No)
  - Tests written for testing the change (Link to commit/No)
* Existing smoke tests passing? – Yes/No
