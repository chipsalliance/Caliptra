# GitHub Rules

## Repository Settings
All Caliptra source code repositories adopt the same set of parameters in their
GitHub configuration.

* Require a pull request before merging
* Require approvals
* Required number of approvals: 2 for spec and RTL, 1 for software
* Dismiss stale pull request approvals when new commits are pushed
* Require review from code owners
* Require conversation resolution before merging
* Restrict who can dismiss pull request reviews
* Require status checks to pass before merging
* Require linear history
* Disallow "merge commits"
* Do not allow bypassing the above settings
* Restrict who can push to matching branches: only relevant folks in
  [MAINTAINERS](MAINTAINERS.md) for `main` and `release/*` branches
* For caliptra-rtl repository
  * "Restrict creation" is used with a pattern match to prevent creation
    of reserved branch names
  * "Lock branch" is used with a pattern match for reserved branch names
  * Disallow auto-merge
* For other repositories
  * Allow auto-merge
* Set "Actions" / "General" / "Fork pull request workflows from
  outside collborators" to "Require approval for all outside collaborators"

Will not set
* Allow force pushes
* Allow deletions
* Lock branch (exception: reserved branch names are locked)
* Allow specified actors to bypass required pull requests

Will not set _yet_
* Require deployments to succeed before merging
* Require merge queue
* Require signed commits

Membership
* The [GitHub Caliptra
  group](https://github.com/orgs/chipsalliance/teams/caliptra/members) will be
  added to all repos
* Repo [MAINTAINERS](MAINTAINERS.md) will be listed with the Maintain role
* TAC Voting Members will be listed with the Admin role

## Issue Management
Repository owners are responsible for triaging existing/open issues on each of the Caliptra public repositories. Triaging of issues includes assignment of:
* Issue type
* Issue timeline/milestones
* Issue assignee (owner)
Assignees will be responsible for following up with requested information, debug, or code/documentation changes as appropriate.

### Labels
When used to flag a version to which an issue applies, labels may be either `Future` or `<major>.<minor>`. Until an issue is scheduled for a known/identified release, all pending issues are scheduled as `Future`. Otherwise, the version label uses the format `<major>.<minor>` (for example, `1.3`). A label of an already-released version means that the issue applies to updates that will be included in patches to that release.

Labels used:
- `RFC`: See [Caliptra Contributing Process](doc/CaliptraContributingProcess.md)
- `Future`
- `<major>.<minor>` (for example, `1.0`, `1.1`, `2.0`)
- `documentation`
- `validation`

### Types
The following issue types are defined for all Caliptra repositories:
* Task
* Bug
* Feature
* Errata

During issue triage, an owner chooses the appropriate issue type based on the request. Issues that are simply requesting explanation or clarification of concepts will not be assigned any "type", as the conversation on the issue is sufficient for resolution.

The "Bug" type is only assigned once Caliptra representatives have determined that the proposed problem is indeed a design flaw, as opposed to a misunderstanding of the code or specified Caliptra behavior. If a documentation error is deemed sufficiently egregious or misleading such that it may cause integrators to produce an incorrect design, the issue will be tagged as a Bug type, even if there is no corresponding flaw in the provided source code.

The "Feature" type is assigned for issues that propose new features to documentation or to source code. Note that community members who are proposing new features (that are not yet approved) must submit the issue using the RFC template, in adherance with the process defined in the [Caliptra Contributing Process](doc/CaliptraContributingProcess.md).

Other issues that require some follow up by consortium representatives are classified with the "Task" type, which indicates that some action is necessary to improve the repository but without the severity of a Bug or the scope of a Feature. For example, updates to documentation to add clarity, or improvements to build scripts or test cases may be classified as Task types.

The final type, "Errata" is described in more detail in the following section.

### Errata

Errata are filed as GitHub issues to provide public documentation of defects that impact released versions. The methodology for tracking Errata is:
* File an issue in the affected repository with type `Errata`.
* Apply one or more version labels (`<major>.<minor>`) for all releases impacted by the Errata.
* Errata are not automatically scheduled to be fixed in patch releases. Patch fixes may be considered case-by-case based on impact (or if another change already necessitates a patch release).
* If a fix is planned for `main`, open a separate issue of type `Bug`, label it `Future`, and link it to the original Errata issue.
  * Close the Bug issue when the fix is merged to `main`.

If an Errata will be fixed in a patch release:

1. File a new issue of type `Bug`.
2. Link the Bug issue to the original Errata issue.
3. Label the Bug issue with the applicable version number (`<major>.<minor>`).
4. Merge the fix into the appropriate patch branch, then close the Bug issue as completed.
5. Remove the corresponding version label from the Errata issue.

Errata issues remain open until the issue is fixed for all affected versions (i.e., until all version labels have been removed).
