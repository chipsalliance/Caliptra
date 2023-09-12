# Caliptra Project Security Incidence Response

## Security Communication

Security information about each release is included in the release notes. You can subscribe to the
[&lt;**TODO** announce mail list&gt;](https://lists.zephyrproject.org/g/announce) to get notification when a new release comes out.

A summary of the known security vulnerabilities can be found at &lt;**TODO** pointer to a page on Caliptra GitHub for vulnerabilities&gt;

Vulnerability notifications pre-release or during embargo periods are available to Product Creators that have registered through the Product
Creator Notification Process.

## Report a Vulnerability

We’re extremely grateful for our silicon integrators, contributors and security researchers that report vulnerabilities to the Caliptra Project
and raise its assurance bar.

All reports are thoroughly investigated by Caliptra TC members who form the Caliptra Project Security Incident Report Team (Caliptra PSIRT) and
may get assigned a CVE if appropriate.

The Caliptra project is a listed [&lt;**TODO** CVE Numbering Authority with MITRE&gt;](https://cve.mitre.org/cve/request_id.html).

Vulnerabilities to the Caliptra project may be reported via email to the Vulnerabilities mailing list:
[<u>caliptra-wg@lists.chipsalliance.org</u>](mailto:caliptra-wg@lists.chipsalliance.org).

More details of how vulnerabilities are handled can be found in the section
[&lt;**TODO** Security Incident Management&gt;](https://docs.zephyrproject.org/latest/security/security-overview.html#security-issue-management).

### When Should I Report a Vulnerability?

- You think you discovered a potential security vulnerability in Caliptra

- You are unsure how a vulnerability affects Caliptra

- You think you discovered a vulnerability in another project that Caliptra depends on

  - For projects with their own vulnerability reporting and disclosure process, please report it directly there.

### When Should I NOT Report a Vulnerability?

- You need help tuning Caliptra components for security. Use feature request

- You need help at &lt;**TODO** pointer to a page on Caliptra GitHub for vulnerabilities&gt;

- Your [<u>&lt;**TODO** pointer to Caliptra GitHub issues related&gt;</u>](https://github.com/zephyrproject-rtos/zephyr/issues/new/choose) is not
  security related.

## Security Vulnerability Response

Each report is acknowledged and analyzed by Caliptra Project Security Incident Response Team members within 7 working days. This will set off the
Security Incident Management Process outlined below.

Any vulnerability information shared with the Caliptra TC stays within the Caliptra project and will not be disseminated to other projects unless it
is necessary to get the issue fixed.

As the security issue moves from triage, to identified fix, to release planning, we will keep the reporter updated.

## Embargo Policy

The information members receive during embargo periods may be received on **TODO** Vulnerabilities-alerts.caliptra-wg@lists.chipsalliance.org.
Any information regarding embargoed vulnerabilities must not be made public, shared, nor even hinted at anywhere beyond the need-to-know
within your specific team except with the list’s explicit approval. This holds true until the public disclosure date/time that was agreed upon by
the list. Members of the list and others may not use the information for anything other than getting the issue fixed for your respective
product’s users.

Before any embargoed information from the list is shared with respective members of your team required to fix said issue, they must agree to the
same terms and only find out information on a need-to-know basis.

In the unfortunate event that a member shares the information beyond what is allowed by this policy, that member ***must*** urgently inform the
**TODO** Vulnerabilities-alerts.caliptra-wg@lists.chipsalliance.org mailing list of exactly what information leaked and to whom. A retrospective
will take place after the leak so we can assess how to not make the same mistake in the future.

If the member continues to leak information and break this policy, the member will be removed from the list.

More details of how vulnerabilities are handled can be found in our
[**TODO** Security Incident Management ](https://docs.zephyrproject.org/latest/security/security-overview.html#security-issue-management.)documentation.

## Product Creator Notification

Product creators who are not already members of the Caliptra project may be eligible to participate in the
**TODO** Vulnerabilities-alerts.caliptra-wg@lists.chipsalliance.org mail list and receive advanced notification of the vulnerabilities and Reporting
mitigations before public disclosure by applying to participate. For information on the notification process, refer to the Vulnerability and Alerts
section of the Caliptra Project documentation.

Criteria for participation includes:

1. Have a contact who will respond to emails within a week and understands how Caliptra is being used in the product.

1. Have a publicly listed product based on some release of Caliptra.

1. Have an actively monitored security email alias.

1. Accept the Caliptra Embargo Policy that is outlined above.

Removal:

1. If a member stops adhering to these criteria after joining the list then the member will be unsubscribed.

If you believe your company meets the criteria to be eligible to receive vulnerability alerts, please fill out the form at: &lt;**TODO** Product
Creators Vulnerability Alert Registry&gt;.

## Security Issue Management

Issues within this bug tracking system will transition through a number of states according to this diagram:

**TODO** Insert diagram from https://docs.zephyrproject.org/latest/security/reporting.html#security-issue-management

- **New:** This state represents new reports that have been entered directly by a reporter. When entered by the response team in response to an
email, the issue shall be transitioned directly to *Triage*.

- **Triage:** This issue is awaiting Triage by the response team. The response team will analyze the issue, determine a responsible entity, assign
it to that individual, and move the issue to the *Assigned* state. Part of triage will be to set the issue’s priority.

- **Assigned:** The issue has been assigned, and is awaiting a fix by the assignee.

- **Review:** Once there is a Caliptra pull request for the issue, the PR link will be added to a comment in the issue, and the issue moved to the
*Review* state.

- **Accepted:** Indicates that this issue has been merged into the appropriate branch within Caliptra.

- **Public:** The embargo period has ended. The issue will be made publicly visible, the associated CVE updated, and the vulnerabilities page in the
docs updated to include the detailed information.

The security advisories created are kept private, due to the sensitive nature of security reports. The issues are only visible to certain parties:

- Members of the PSIRT mailing list

- The reporter

- Others, as proposed and ratified by the Caliptra Security Subcommittee. In the general case, this will include:

  - The code owner responsible for the fix.

  - The Caliptra release owners for the relevant releases affected by this vulnerability.

The Caliptra TC shall review the reported vulnerabilities during any meeting with more than three people in attendance. During this review, they
shall determine if new issues need to be embargoed.

The guideline for embargo will be based on:

1. Severity of the issue, and

2. Exploitability of the issue.

Issues that the Caliptra TC decides do not need an embargo will be reproduced in the regular Caliptra project bug tracking system.

Security sensitive vulnerabilities shall be made public after an embargo period of at most 90 days. The intent is to allow 30 days within the
Caliptra project to fix the issues, and 60 days for external parties building products using Caliptra to be able to apply and distribute these
fixes.

Fixes to the code shall be made through pull requests (PRs) in the Caliptra project GitHub. Developers shall make an attempt to not reveal the
sensitive nature of what is being fixed, and shall not refer to CVE numbers that have been assigned to the issue. The developer instead should
merely describe what has been fixed.

The Caliptra TC will maintain information mapping embargoed CVEs to these PRs (this information is within the Github security advisories), and
produce regular reports of the state of security issues.

Each issue that is considered a security vulnerability shall be assigned a CVE number. As fixes are created, it may be necessary to allocate
additional CVE numbers, or to retire numbers that were assigned.

## Vulnerability Notification

Each Caliptra release shall contain a report of CVEs that were fixed in that release. Because of the sensitive nature of these vulnerabilities,
the release shall merely include a list of CVEs that have been fixed. After the embargo period, the vulnerabilities page shall be updated to include
additional details of these vulnerabilities. The vulnerability page shall give credit to the reporter(s) unless a reporter specifically requests
anonymity.

The Caliptra project shall maintain a vulnerability-alerts mailing list. This list will be seeded initially with a contact from each project member.
Additional parties can request to join this list by filling out the form at the
[**TODO** Vulnerability Registry](https://www.zephyrproject.org/vulnerability-registry/). These parties will be vetted by the Caliptra TAC to
determine that they have a legitimate interest in knowing about security vulnerabilities during the embargo period.

Periodically, the Caliptra TC will send information to this mailing list describing known embargoed issues and their backport status within the
project. This information is intended to allow them to determine if they need to backport these changes to any internal trees.

When issues have been triaged, this list will be informed of:

- The Caliptra Project security advisory link (GitHub).

- The CVE number assigned.

- The subsystem involved.

- The severity of the issue.

After acceptance of a PR fixing the issue (merged), in addition to the above, the list will be informed of:

- The association between the CVE number and the PR fixing it.

- Backport plans within the Caliptra project.

## Backporting of Security Vulnerabilities

Each security issue fixed within Caliptra Firmware shall be backported to the following releases:

- The current Long Term Stable (LTS) release.

- The most recent two releases.

Backports will be tracked on the security advisory.

## Need to Know

Due to the sensitive nature of security vulnerabilities, it is important to share details and fixes only with those parties that have a need to
know. The following parties will need to know details about security vulnerabilities before the embargo period ends:

- Maintainers will have access to all information within their domain area only.

- The current release manager, and the release manager for historical releases affected by the vulnerability (see backporting above).

- The Project Security Incident Response (PSIRT) team will have full access to information.

- The PSIRT is made up of representatives from Caliptra integrators & contributors.

- As needed, release managers and maintainers may be invited to attend additional security meetings to discuss vulnerabilities.