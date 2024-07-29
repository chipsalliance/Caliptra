# HW Release process

## Nightly

1. When the **HW Release Workflow** is triggered, the **RTL Submodule Pointer Update** flow is called
2. The **nightly-verilator** smoke test regression test will be executed against the HEAD of the **main** branch
    -  If the test passes a **release collateral** archive will be generated and pushed as a Github Artifact
    -  Repo tag will be added as well in the form "release_v#yyyy#mm#dd_#n"

## RTL Submodule Pointer Update

1. The RTL submodule pointer is compared against the **HEAD of main** of the **caliptra RTL** repo
    - In case they both point to the same **SHA commit** the rest of the flow is skipped 
2. A new commit will update the RTL submodule pointer to point to the HEAD of the main branch, and update the registers RDL
3. A new **nightly release** branch will be created from the HEAD of the **main** branch in the **caliptra-sw** repo
   - Naming of the branch will indicate it is a nightly release and will have a target point release date (ci_rtl_#yyyy#mm#dd_#n)
4. The branch will trigger all the CI tests required to submit a PR
5. Upon succesful completion of the CI tests, the branch will be merged and deleted

## Major Releases

1. Before finalizing an RTL release, the hardware team will follow the procedure described in [CaliptraReleaseChecklist.md](https://github.com/chipsalliance/caliptra-rtl/blob/main/docs/CaliptraReleaseChecklist.md).
  - Upon finalizing all release checklist items, the hardware team will generate a release tag on the RTL **main** branch, using the following naming convention: `v<major>.<minor>`.
  - When the checklist items are completed, the RTL team will create a new branch following the naming convention `patch_v<major>.<minor>`. This branch will exactly match the contents of the major release tag. Any future fixes that must be applied as patches to this release version will be committed to the `patch_v<major>.<minor>` branch. Branch **main** will continue to receive updated code for the subsequent planned release, and is not guaranteed to contain a valid release except as tagged.
2. The software team will follow the [submodule update steps](#RTL-Submodule-Pointer-Update) to create a `hw/<major>.<minor>/rtl` RTL submodule pointer to consume the code from branch `patch_v<major>.<minor>` and associate that submodule with the release.
3. The **caliptra-sw** repo will be tagged with a **release** version tag. As a result of the submodule flow, this release will contain a snapshot of the code from the **caliptra-rtl** repo that was already tagged with the release version.

## Fail Case

1. Failure in caliptra-sw repo
    1. Manual intervention required. Create a new issue into the SW Repo. The fix will be made on the **main** branch.
    2. The next **nightly release** workflow will generate the release
2. Failure in RTL Repo
    1. Manual intervention required. Create a new issue into the RTL Repo. Nightly releases are gated to become major until a fix is merged to main.
    2. While HW fix requires longer time to be submitted, it is acceptable to temporarily diverge from the main branch.
        - A dev branch will be created from the tip of the RTL main branch, and WA fixes will be applied as individual commits
        - The RTL Sumbodule pointer in the **caliptra sw** repo will manually be updated to point to the dev branch.
        - The nightly release workflow will generate all individual patches as part of the collateral archive and list them in the release notes.
    3. Once the issue is fixed, the RTL dev branch will be deleted and the RTL submodule pointer will be repositioned to the HEAD of the RTL main branch.

## Release Collateral

- Release ZIP File
  - RTL SRC
  - ROM binary files (BIN, ELF, and HEX)
  - Additional Documentation
  - Caliptra Main Specs
  - Caliptra ROM Specs
  - Caliptra RTL Notes
  - Register Documentation (External)
  - Header files with:
    - Register definitions.
    - Reference code for mailbox, etc.
  - Release notes TXT file
  - Which tests were run and which ones passed/failed?
  - All relevant Git commit hashes from both repos
- Separate Supporting ZIP File (due to size concerns)
  - FPGA Bitstream file
  - C HW model
    - Headers and static library
  - Firmware signed (development key) binary files (BIN, ELF)
  - Integrator Test Checklist
    - Fuse Matrix
    - Test List
    - Development Key

## Release Rules/Opens

- All releases will come from the main branch with nightly cadence.
- Once a release is made the **nightly release branch** SHALL be deleted.
- Code from the **caliptra-rtl** repo that is included in a major release tag on the **caliptra-sw** repo must exactly match the major release tag that was made in the **caliptra-rtl** repo.

<br> *Caliptra Release Flow*
![Caliptra Release Flow Chart](doc/images/Caliptra_release_flow.svg)
