# HW Release process

## Nightly

1. When a new release is triggered a new **release candidate** branch will be created from the HEAD of the **main** branch in the **caliptra-sw** repo.
    - Naming of the branch fill indicate it is a release candidate and will have a target point release version (ex. HWRC 0.8_0; HWRC 0.8_1)
2. A new commit will update the RTL submodule pointer to point to the new RTL release candidate branch creates in Step #1, and update the registers RDL
3. If all the caliptra-sw repo CI tests pass:
    1. A **release collateral** archive will be generated and pushed as a Github Artifact
    2. If the RTL submodule pointer has been updated (and no other changes were required to be cherry-picked), **release candidate** will turn into a PR into main

## Major Releases

1. The **release collateral** will be manually used for a RTL DV Checkout
2. If the RTL Regression passes a new release will be made on the **caliptra** repo and a ZIP file containing the release collateral will be included as part of the release.
3. The **caliptra-rtl** and **caliptra-sw** repos will be tagged with a **release** version tag.

## Fail Case

1. Failure in caliptra-sw repo
    1. Create PR with the fixes to go to **main** branch in the caliptra-sw repo
    2. Once PR is merged, fix will be cherry picked into **release candidate** branch and we would go back to Step #4
2. Failure in RTL Repo
    1. Create PR with the fixes to go to **main** branch in the caliptra-rtl repo
    2. Once PR is merged, go back to step #2

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

- All fixes go into a main branch first and then any required fixes for a release will get cherrypicked over.
- All releases will come from a release candidate branch and have a TAG created.
- Once a release is made the release candidate branch SHALL be deleted.

<br> *Caliptra Release Flow*
![Caliptra Release Flow Chart](doc/images/Caliptra_release_flow.svg)
