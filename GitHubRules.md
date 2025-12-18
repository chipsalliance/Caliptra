# GitHub Rules

All Caliptra source code repositories adopt the same set of parameters in their
GitHub configuration.

* Require a pull request before merging
* Require approvals
* Required number of approvals: 2 for spec and RTL, 1 for software
* Dismiss stale pull request approvals when new commits are pushed
* Require review from code owners
* Require conversation resolution before merging
* Restrict who can dismiss pull request reviews
* Require linear history
* Disallow "merge commits"
* Do not allow bypassing the above settings
* Restrict who can push to matching branches: only relevant folks in
  [MAINTAINERS](MAINTAINERS.md) for `main` and `release/*` branches
* For caliptra-rtl Repository
  * "Restrict creation" is used with a pattern match to prevent creation
    of reserved branch names
  * "Lock branch" is used with a pattern match for reserved branch names
  * Disallow auto-merge
* For other Repositories
  * Allow auto-merge
* Set "Actions" / "General" / "Fork pull request workflows from
  outside collborators" to "Require approval for all outside collaborators"

Will not set
* Allow force pushes
* Allow deletions
* Lock branch (exception: reserved branch names)
* Allow specified actors to bypass required pull requests

Will not set _yet_
* Require deployments to succeed before merging
* Require merge queue
* Require status checks to pass before merging
* Require signed commits

Membership
* The [GitHub Caliptra
  group](https://github.com/orgs/chipsalliance/teams/caliptra/members) will be
  added to all repos
* Repo [MAINTAINERS](MAINTAINERS.md) will be listed with the Maintain role
* TAC Voting Members will be listed with the Admin role
