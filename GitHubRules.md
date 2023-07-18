# GitHub Rules

All Caliptra source code repositories adopt the same set of parameters in their
GitHub configuration.

* Require a pull request before merging
* Require approvals
* Required number of approvals: 2 for spec and RTL, 1 for software
* Dismiss stale pull request approvals when new commits are pushed
* Allow auto-merge
* Require review from code owners
* Require conversation resolution before merging
* Restrict who can dismiss pull request reviews
* Do not allow bypassing the above settings
* Restrict who can push to matching branches: only relevant folks in
  [MAINTAINERS](MAINTAINERS.md) for `main` and `release/*` branches
* Require linear history

Will not set
* Allow force pushes
* Allow deletions
* Lock branch
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
