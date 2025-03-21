# Services and Haredware Module Interface
For [FIPS140-3] validation purposes, the Caliptra API is mapped to the set of services described in this section. The Module is configured at the factory to provide only approved security services (an approved mode of operation only). The sections below summarize each service implemented by the Module. See the [Caliptra Runtime Firmware v1.1](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md) Section of Caliptra documentation for complete details, inclusive of all input and output structures.

The [Caliptra documentation *Service surface*](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md#service-surface) section describes four high level services available via the command mailbox and associated SHA2-384 block:
- **Loading firmware**: Caliptra firmware is loaded via the mailbox at cold boot. In addition, Caliptra firmware can be loaded at runtime to support hitless or impactless updates (upgrade without downtime).
- **DICE-as-a-Service**: Caliptra exposes the TCG DICE Protection Environment iRoT Profile API, allowing Caliptra to derive and wield a DICE identity on behalf of other elements within the SoC. For example, Caliptra can sign messages for an SPDM responder.
- **Measurement Vault**: Caliptra manages measurements for the code and configuration of the SoC. 
- **Blob Authentication**: Caliptra supports ECDSA verification for SoC firmware beyond its own. The SHA2-384 block exposes a HW API for hashing firmware. The runtime firmware exposes an ECDSA verification API that uses the hash computed by the SHA2-384 block.

Additional services are available to satisfy [FIPS140-3] requirements and to provide utility operations:
  - Module identification and version.
  - Sanitize (destroy persistent CSPs at Module end of life).
  - Shutdown (shutdown the Module and zeroize runtime CSPs).
  - Utilities (non-cryptographic and administrative commands).
All commands except FW_LOAD include an explicit [FIPS_STATUS](https://github.com/chipsalliance/caliptra-sw/tree/main/runtime#fips-status) field, as illustrated in the example below. 

![Exposed command example - Capabilities](../../Images/Capabilities_HMI_example.png)

VE03.15.03-04: Mailbox transmit (tx) and receive (rx) size are indicated in the parcel struct [caliptra_mbox.h](https://github.com/chipsalliance/caliptra-sw/blob/main/libcaliptra/src/caliptra_mbox.h), enforced in [caliptra_api.c](https://github.com/chipsalliance/caliptra-sw/blob/main/libcaliptra/src/caliptra_api.c).

The complete set of Caliptra service indicators is enumerated in enum [libcaliptra_error](https://github.com/chipsalliance/caliptra-sw/blob/main/libcaliptra/inc/caliptra_enums.h#L12-L36).

The Caliptra Hardware Module Interface (HMI) is expressed logically by the [caliptr_api.h](https://github.com/chipsalliance/caliptra-sw/blob/main/libcaliptra/inc/caliptra_api.h). 

The complete set of Caliptra interfaces are listed next, grouped into the services as represented in the [MIS JSON](../../Security_Policy/baseline_v_1_0/Caliptra_Base_v1_0.mis.json#L296-L410) used to generate [Security Policy](../../Security_Policy/baseline_v_1_0/Caliptra_Base_v1_0_140-3_Security_Policy_Output.pdf) content.

## Digest
Calculate a digest using external SHA accelerator. 

Inputs: SHA CSR inputs.

Outputs: SHA CSR outputs.

## Firmware Load
Load and authenticate Caliptra firmware image. 

Caliptra firmware update does not constitute “complete image replacement” as the ROM is not replaceable; as such the following do not apply: AS04.33, AS04.34, AS04.25. See also [FIPS140-3IG 10.3.F](https://csrc.nist.gov/CSRC/media/Projects/cryptographic-module-validation-program/documents/fips%20140-3/FIPS%20140-3%20IG.pdf#page=96).

See [TBD]() for the sequence and process of the FIRMWARE_LOAD command, and the CALPITRA_FW_LOAD section of Caliptra documentation for the specification of command input and response output. 

The Firmware image format is summarized in the figure below for reviewer convenience; see the Firmware image format and verification section of Caliptra documentation for additional detail. 

![Firmware image format](../../Images/FirmwareImageFormat.png)

- caliptra_upload_fw: Upload Caliptra Firmware. Requires entire FW as fw_buffer. For loading chunks of data at a time, use start/send/end functions below.
- caliptra_upload_fw_start_req: If the SoC cannot buffer the entire FW, the following 3 functions can be used to write chunks at a time. Upload Caliptra Firmware Start Request. Begin a FW_LOAD command to caliptra. Total FW size is needed at the start per mailbox protocol.
- caliptra_upload_fw_send_data: Upload Caliptra Firmware Send Data. Load a chunk of the FW data to Caliptra. Intended to be called multiple times. MUST follow caliptra_upload_fw_start_req and precede caliptra_upload_fw_end_request. Size MUST be dword aligned for any chunks except the final chunk.
- caliptra_upload_fw_end_req: Upload Caliptra Firmware End Request. End the FW_LOAD request after sending all the FW data. Waits for Caliptra completion and response if async is false.

### Inputs
Mailbox command frame

Outputs: Mailbox response frame.

To verify the firmware, Caliptra ROM performs the following steps:
1.	Calculates the hash of the vendor public keys in the preamble and compares it against the hash in fuses (key_manifest_pk_hash). If the lifecycle is not "unprovisioned" and the hashes do not match, the boot fails.
2.	Calculates the hash of the owner public keys in the preamble and compares it against the hash in fuses (owner_pk_hash). If the owner_pk_hash fuse is not zero (i.e., unprovisioned) and hashes do not match, the boot fails. See the [Owner authorization](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md#owner-authorization) section.
3.	Ensures the vendor public key(s) selected by the preamble indices are not revoked based on fuse: key_manifest_pk_hash_mask for ECDSA public key, lms_revocation for LMS public key.
4.	Calculates the hash of the first byte through the vendor data field of the header (this includes the TOC digest). This is the vendor firmware digest.
5.	Calculates the hash of the first byte through the owner data field of the header (this includes the TOC digest). This is the owner firmware digest.
6.	Verifies the vendor signature using the vendor firmware digest from step 4 and the vendor key(s) from step 3.
7.	Verifies the owner signature using the owner firmware digest from step 5 and the owner key(s) from step 2.
8.	Verifies the TOC against the TOC digest that was verified in steps 6 and 7. The TOC contains the SVNs and digests for the FMC and runtime images.
9.	Verifies the FMC against the FMC digest in the TOC.
10.	If Caliptra is not in "unprovisioned" lifecycle state or "anti-rollback disable" state, ROM compares the FMC SVN against FMC SVN fuse (fuse_key_manifest_svn).
11.	Verifies the runtime against the runtime digest in the TOC.
12.	If Caliptra is not in "unprovisioned" lifecycle state or "anti-rollback disable" state, ROM compares the runtime digest against the runtime SVN fuse (fuse_runtime_svn).
In addition to cold boot, Caliptra ROM performs firmware verification on hitless updates. See the [hitless update](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md#hitless-update) section for details.


## Identity Management
Reconstruct or obtain device identities in certificate or key formats. 

### Entry points
- caliptra_get_idev_cert: Get IDEV cert.
- caliptra_get_idev_info: Exposes a command to get an IDevID public key.
- caliptra_populate_idev_cert: Populate IDEV cert.
- caliptra_get_ldev_cert: Get LDEV cert.
- caliptra_get_fmc_alias_cert: Get FMC Alias cert.
- caliptra_get_rt_alias_cert: Get RT Alias cert.
- caliptra_is_idevid_csr_ready: Query if IDevID CSR is ready.
- caliptra_retrieve_idevid_csr: 
- caliptra_req_idev_csr_start: 
- caliptra_req_idev_csr_complete: Clear IDEV CSR request.

Caliptra certificates follow the X.509 v3 format described in [RFC 5280](https://datatracker.ietf.org/doc/html/rfc5280). 
After vendor provisioning, Caliptra's certificate chain is represented as shown next.

![Caliptra Certificate Chain Representation](../../Images/CaliptraCertificateChain.png)

Inputs: Mailbox command frame

Outputs: Mailbox response frame.

## Measurement
Manage device measurements.

### Entry points
- caliptra_stash_measurement: Stash measurement.

inputs: Mailbox command frame; outputs: Mailbox response frame.

## Sanitize
Sanitize Caliptra SSPs. Indicator: fips_status.
inputs: Mailbox command frame; outputs: Mailbox response frame.

## Self-test
Pre-operational self-test via module HMI. 
### Entry points
- caliptra_self_test_start
- caliptra_self_test_get_results

Indicator: 
fips_status.

Inputs: async parameter.
Mailbox command frame; outputs: Mailbox response frame.

## Show Status
Report module name, version and status. Indicator: fips_status.
inputs: Mailbox command frame; outputs: Mailbox response frame.

## Show Version
Report module name, version and status. 
The VERSION command responds with the information in support of VE04.13.01 and VE04.14.01, with further information on VE04.13-14 requirements given in [SP].

![Verify command summary](../../Images/VerifyCommandSummary.png)

### Entry points
- caliptra_fips_version: FIPS version.

### Service level inputs
Mailbox command frame.

### Service level outputs
Mailbox response frame.

## Utility
Information retrieval and administrative commands. 

### Entry points
- caliptra_bootfsm_go: Write into Caliptra BootFSM Go Register; rturns 0 on success.
- caliptra_set_wdt_timeout: Set the WDT timeout value for caliptra
- void caliptra_configure_itrng_entropy: ?
- caliptra_mbox_pauser_set_and_lock: Sets the provided pauser value in one of the mbox_pauser_valid regs and sets the corresponding lock bit. Returns PAUSER_LOCKED if all slots are locked.
- caliptra_fuse_pauser_set_and_lock: Sets the provided pauser value in the fuse_pauser_valid reg and sets the lock bit. Returns PAUSER_LOCKED if already locked.
- caliptra_ready_for_fuses: Determine if Caliptra is ready to program fuses.  Returns bool.
- caliptra_init_fuses: Program calpitra_fuse object contents to caliptra fuses. Returns 0 (success), INVALID_PARAMS, NOT_READY_FOR_FUSES, STILL_READY_FOR_FUSES.
- caliptra_ready_for_firmware: Query if ROM is ready for firmware, returns bool.
- caliptra_read_fw_non_fatal_error: Read the value of the caliptra FW non-fatal error code. Returns: [Caliptra error code].(https://github.com/chipsalliance/caliptra-sw/blob/main/error/src/lib.rs).
- caliptra_read_fw_fatal_error: Read the value of the caliptra FW fatal error code. Returns: [Caliptra error code].(https://github.com/chipsalliance/caliptra-sw/blob/main/error/src/lib.rs).
- caliptra_write_reg: Generic write for a caliptra register.
- caliptra_read_reg: Generic read for a caliptra register.

### Service level indications
fips_status.

### Service level inputs
Mailbox command frame.

### Service level outputs
Mailbox response frame.

## Verify
Verify a digital signature.

### Entry points
- caliptra_ecdsa384_verify: ECDSA384 Verify.
- caliptra_lms_verify: LMS Verify.

### Service level inputs
Mailbox command frame.

### Service level outputs
Mailbox response frame.

Indicator: fips_status.
inputs: Mailbox command frame; outputs: Mailbox response frame.

- caliptra_invoke_dpe_command: DPE command.
- caliptra_disable_attestation: Disable attestation.
- caliptra_fw_info: FW Info.
- caliptra_dpe_tag_tci: DPE tag TCI.
- caliptra_dpe_get_tagged_tci: DPE get tagged TCI.
- caliptra_increment_pcr_reset_counter: Increment PCR Reset Counter.
- caliptra_quote_pcrs: Quote PCRs.
- caliptra_extend_pcr: Extend PCR.
- caliptra_add_subject_alt_name: Add subject alt name.
- caliptra_certify_key_extended: Certify key extended.

- caliptra_self_test_start: Self test start.
- caliptra_self_test_get_results: Self test get results.
- caliptra_shutdown: Shutdown.
- caliptra_capabilities: Capabilities.
- caliptra_is_idevid_csr_ready: Query if IDevID CSR is ready.
- caliptra_retrieve_idevid_csr: 
- caliptra_req_idev_csr_start.
- caliptra_req_idev_csr_complete: Clear IDEV CSR request.


- caliptra_test_for_completion: Test for completion of the previously issued mailbox command. Returns Mailbox status busy as True or False. 
- caliptra_complete: Resets the mailbox and SW state. Populates the response buffer provided when issuing the command if applicable. (See note above on return codes). 

- caliptra_mailbox_execute: Execute Mailbox Command. Generic function for sending and receiving a command with raw, user-defined command and buffers. NOT RECOMMENDED to be used directly when avoidable.
- use the functions below for the specific command. (See notes above on asynchronous operation and return codes).

For full command details, please refer to the Caliptra Runtime Readme file at runtime\README.md

## Zeroize
The Shutdown entry point shutsdown the Caliptra block.
Note that the CMVP ModVerApp tool and WebCryptik require this service to be named Zeroize (or a similar variation).

Vendor specific: external to Caliptra boundary, but required within FIPS boundary.

### Entry points
- caliptra_shutdown: Shutdown, inclusive of Caliptra volatile SSP zeroization.
- wrapper_sanitize: *vendor / module specific*. End of life SSP zeroization.
 
### Service level inputs
Mailbox command frame.

### Service level outputs
Mailbox response frame.



## MAILBOX COMMANDS
### Asynchronous operation
- All commands have an option for asynchronous usage as their last param
- Setting this will cause the command function to return once the request has been issued to caliptra
- The caller should then poll for completion using caliptra_test_for_completion
- After successfully polling, the caller should use caliptra_complete to finish the transaction and populate the response buffer originally provided.
- The caller MUST ensure the response buffer provided remains available until caliptra_complete returns

### Mailbox error codes
|Enumeration|Meaning|
|-----------|-------|
|0|Success|
|MBX_BUSY|Mailbox is still busy when trying to send, the previous operation was never completed.|
|INVALID_PARAMS|Params provided were null when not accepted or otherwise invalid.|
|MBX_COMPLETE_NOT_READY      |Mailbox is still busy (poll on caliptra_test_for_completion before calling).|
|MBX_NO_MSG_PENDING          |No mailbox request has been issued.|
|MBX_STATUS_FAILED           |Mailbox HW status was set to CMD_FAILURE by caliptra FW.|
|MBX_STATUS_UNKNOWN          |Mailbox HW status is not a known/expected value.|
|MBX_STATUS_NOT_IDLE         |Mailbox status did not return to idle after clearing execute.|
|MBX_RESP_NO_HEADER          |The response buffer is too small to contain a header.|
|MBX_RESP_CHKSUM_INVALID     |The checksum in the response is not valid.|
|MBX_RESP_FIPS_NOT_APPROVED  |FIPS status in the response was not "approved".|
|API_INTERNAL_ERROR          |The API internal state no longer matches the HW state (should not be possible).|
