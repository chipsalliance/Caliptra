# HW Release process

## Nightly

1. When a new release is triggered, if the RTL submodule pointer is comparaed against HEAD of the **main** branch
    - In case of divergece, the **RTL Submodule Pointer Update** flow will be executed
2. A verilator smoke test regression test will be executed against the HEAD of the **main** branch.
3. If the verilator smoke test passes:
    1. A **release collateral** archive will be generated and pushed as a Github Artifact

## RTL Submodule Pointer Update

    1. A new commit will update the RTL submodule pointer to point to the HEAD of the main branch, and update the registers RDL
    2. A new **nightly release** branch will be created from the HEAD of the **main** branch in the **caliptra-sw** repo
       - Naming of the branch will indicate it is a nightly release and will have a target point release date (ex. release_"date")
    3. The branch will be triggered as a PR, therefore all the CI tests required to submit a PR will be executed
    4. Upon succesfully completion of the CI tests, the branch will be merged and deleted

## Major Releases

1. The **release collateral** will be manually handed over the RTL team to be verified in the DV environment
2. Upon success of the DV verification a new release will be made on the **caliptra** repo
    -  A ZIP file containing the release collateral will be included as part of the release.
4. The **caliptra-rtl** and **caliptra-sw** repos will be tagged with a **release** version tag.

## Fail Case

1. Failure in caliptra-sw repo
    1. Manual intervention required. Create a new issue into the SW Repo. The fix will be made on the **main** branch.
    2. The next **nightly release** workflow will generate the release
2. Failure in RTL Repo
    1. Manual intervention required. Create a new issue into the RTL Repo. Nightly releases are gated until fix.
    2. Once the issue is fixed, the next **nightly release** workflow will generate the release.

## Release Collateral

- Release ZIP File
  - RTL SRC
  - ROM binary files (BIN ,ELF, and HEX)
  - Additional Documentation
  - All specs?
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

<br> *Caliptra Release Flow*
![Caliptra Release Flow Chart](doc/images/Caliptra_release_flow.svg)
