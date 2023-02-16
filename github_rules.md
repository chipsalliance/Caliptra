# Github Rules

All Caliptra source code repositories adopt the same set of parameters in their
github configuration.

* Require a pull request before merging
* Require approvals
* Required number of approvals: 2
* Dismiss stale pull request approvals when new commits are pushed
* Require review from code owners
* Require approval of most recent reviewable push (whether the most recent reviewable push must be approved by someone other than the person who pushed it)
* Require conversation resolution before merging
* Restrict who can dismiss pull request reviews
* Do not allow bypassing the above settings
* Restrict who can push to matching branches: only relevant folks in [MAINTAINERS](MAINTAINERS.md) for `main` and `release/*` branches
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

