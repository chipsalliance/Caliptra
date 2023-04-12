# Workgroup Charter for Caliptra, a CHIPS Alliance Workgroup

Adopted `[Month, Day, Year]`
This Workgroup Charter (the “Charter”) sets forth the responsibilities and
procedures for technical contribution to, and oversight of the Caliptra
Workgroup (the “Workgroup”).

## Relationship to CHIPS Alliance

This Workgroup is a part of the CHIPS Alliance Project, a Series of LF Projects,
LLC.  The CHIPS Alliance Technical Steering Committee (“TSC”) created this
Workgroup according to the terms of the CHIPS Alliance Technical Steering
Committee.  On the date noted at the top of this document, the TSC adopted this
Charter for the Workgroup.  All CHIPS Alliance governing documents and policies,
including the CHIPS Alliance Technical Charter, Intellectual Property Policy,
and any relevant Code of Conduct will apply to this Workgroup by default. Any
Charters, constitutions, or other policies specifically adopted for other CHIPS
Alliance workgroups will not apply to this Workgroup.

## Mission & Scope of the Workgroup

1. The Mission of the Workgroup is to develop and host open source projects with
   the goals indicated in the “README” file within the Workgroup’s code
   repository.

2. The scope of the Workgroup includes the IP and firmware for an integrated
   Root of Trust silicon block. The Caliptra RoT block targets datacenter-class
   SoCs like CPUs, GPUs, DPUs, TPUs. The repositories within this Workgroup
   provide the documentation, silicon logic, ROM and firmware for implementing a
   Root of Trust for Measurement (RTM) block inside an SoC. A Caliptra
   integration provides the SoC with Identity, Measured Boot and Attestation
   capabilities.


## Participants

The Workgroup technical governance consists of two types of participants:
Technical Advisory Committee members and Volunteer Developers (together, the
“Participants”).

## Technical Advisory Committee

### Role & Responsibilities

The role of the Workgroup Technical Advisory Committee (“TAC”) is to represent
the interests of the Participants in the Workgroup and provide active technical
leadership for the Workgroup.

The responsibilities of these TAC roles within the Workgroup include:
- Merging pull requests and otherwise exercising the role of “Committers” for
  the Workgroup as defined in the CHIPS Alliance Technical Charter;
- Facilitating communication and collaboration between TAC members;
- Upholding the policies outlined in this document;
- Organizing public meetings and public technical discussions;
- Sharing any necessary meeting minutes in a public GitHub repository, a public
  Wiki, or on a public website for the Workgroup within a reasonable period of
  time after the meeting;
- Responding to technical questions on GitHub;
- Setting the technical criteria for use of the Workgroup marks (if applicable);
- Determining strategy and promoting the adoption of the Workgroup technology
  through documentation, talks, or other marketing;
- Administering the [policy for the Caliptra
  trademarks](CaliptraTrademarkPolicy.md).
- Determining whether additional public, open source repositories should be
  created for the Workgroup; and
- Determining whether any Workgroup open source collaborations should be wound
  down and archived on GitHub.

All TAC members exercise the role of Committer as defined in the CHIPS Alliance
Technical Charter.

### Classes of TAC members

Due to the specific nature of the Caliptra project, there are three classes of
TAC members. All members are expected to fulfill the responsibilities
outlined above. However, the subject matter of different classes of maintainers
is scoped to an area of the Caliptra project:

- **RTL** Maintainers: these maintainers provide oversight over all
  contributions to digital logic and silicon design.
- **Firmware** Maintainers: these maintainers provide oversight over all
  contributions to immutable ROM (Read Only Memory) code, First Mutable Code
  (FMC) and runtime firmware (FW).
- **Voting** Members: Only the Voting TAC Members cast the votes for all
  decisions below that require a TAC vote. Where TAC quorum may be needed, only
  a quorum of Voting TAC Members is required. Voting TAC Members are responsible
  for membership decisions in the TAC, and trademark-related decisions.

All members of the TAC share oversight responsibilities for miscellaneous code
that does not fall in any of the categories above, and for documentation files.

## Eligibility

The initial TAC members of the Caliptra workgroup are listed in the
[MAINTAINERS](MAINTAINERS.md) file committed in the same commit as this line.

Organizations who have joined the CHIPS Alliance and signed the CHIPS Alliance
Participation Agreement and CHIPS Alliance Contributor License Agreement are
eligible to nominate developer representatives to join the TAC; upon acceptance
of an employee to the Workgroup TAC, an organization becomes a "Caliptra
Participating Organization"

At all times, a Caliptra Participating Organization should have one employee
included in the TAC for each of the three classes of TAC members: RTL, Firmware,
Voting.

Additionally, Volunteer Developers may join the TAC in their individual capacity
based on active contribution to the Workgroup open source repositories, subject
to a 2/3 approval vote by the existing Voting TAC Members, with 2/3 Voting TAC
Members participating in the vote. Such TAC membership decisions will be based
only on the technical quality of contributions made to an open source project
with Chips Alliance. The metrics for assessing technical quality are determined
by the TAC.

This charter establishes a supermajority approval structure for Volunteer
Developers seeking to join the TAC. Accordingly, to the extent a Volunteer
Developer is deemed a Contributor as defined under the CHIPS Technical charter,
the supermajority approval structure supersedes.

All TAC technical discussions will be publicly accessible, either on public
Workgroup open source repositories on GitHub, on publicly accessible mailing
lists, or on calls that may be joined by any member of the public.

Any member of the TAC may resign by submitting a pull request to
remove their name from the membership list document; the resignation will be
considered effectively immediately upon submitting the pull request. The TAC may
vote to remove a TAC member by a 2/3 vote of the Voting TAC Members, with 2/3
Voting TAC Members participating. A Caliptra Participating Organization may
remove its TAC member representative or replace its TAC member representative
with an alternative employee representative at any time.

The TAC members will be listed by name, with pseudonym or GitHub username listed
optionally, in the [MAINTAINERS](MAINTAINERS.md) document within the Workgroup
open source repository. Membership changes are reflected by pull requests
against the TAC membership list document and relevant CODEOWNERS files
([example](CODEOWNERS)). GitHub repository roles need to be updated as well.

### TAC Chair

The TAC shall elect a Chair on an annual basis based on a majority vote by the
Voting TAC Members.

The TAC may determine the date of its annual Chair elections, with additional
elections as needed if a Chair resigns or otherwise needs to be replaced.  The
TAC Chair will:
- Represent the Workgroup in CHIPS Alliance Technical Steering Committee
  meetings per the CHIPS Alliance Technical Charter;
- Represent the Workgroup in discussions with Linux Foundation legal counsel
  with respect to trademark prosecution for the Workgroup marks (if applicable),
  on behalf of all Workgroup Participants; and
- Escalate any Code of Conduct concerns to the CHIPS Alliance TSC.

A TAC Chair may resign at any time. A TAC Chair may be removed from the position
of Chair by a 2/3 vote of the Voting TAC Members, with at least 2/3 majority of
the Voting TAC Members participating in the vote.

A former TAC Chair may continue to be a Participant in the Workgroup if there is
no other reason against it, e.g., if no adverse Code of Conduct determination
has been made.

## Volunteer Developers

The Workgroup welcomes contributions from members of the open source community.
All open source contributors who have signed the CHIPS Alliance Contributor
License Agreement, or who are covered by a CHIPS Alliance Contributor License
Agreement signed by their employer, are welcome as Volunteer Developers.

Volunteer Developers can contribute to the Workgroup open source project via
pull requests on GitHub and participation in Workgroup meetings and technical
discussions. Volunteer Developers do not have voting rights. Volunteers are
encouraged to review and comment on pending pull requests to the Workgroup open
source repositories, but they cannot accept pull requests on behalf of the
Workgroup.

Not all suggested contributions will be merged by the TAC, and Volunteer
Developers will not have commit rights or edit rights for the Workgroup open
source project.

The Workgroup will recognize Volunteer Developers if individuals request to be
added to a list of Volunteer Developers, to be maintained in the CONTRIBUTORS
document in the Workgroup open source repository alongside the list of official
TAC members. It is not necessary to be included in the listed individual
Volunteer Developers in Workgroup documentation to be considered a Volunteer
Developer.

Volunteer Developers are welcome to join all meetings, mailing lists, and
discussions on GitHub. Volunteer Developers do not have any required
responsibilities to the Workgroup.

Volunteer Developers may become TAC members according to the process outlined
regarding the addition of new members to the TAC.

## Amendments

This Charter may be amended by a 2/3 vote of the Voting TAC Members with at
least a 2/3 participating majority of listed Voting TAC Members. The upcoming
vote shall be announced ahead of time with no less than one week notice. The
vote shall be conducted in a meeting with meeting minutes noting which Voting
TAC Members were present and how they voted. The minutes will be recorded in
this github repo.

TAC votes to amend the Workgroup Charter will be subject to a veto by the CHIPS
Alliance Board, to be exercised when a Charter amendment may unacceptably depart
from the purpose of the CHIPS Alliance or unreasonably increase risk for CHIPS
Alliance participants.
