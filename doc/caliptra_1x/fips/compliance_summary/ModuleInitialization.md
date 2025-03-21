*Ref: VE04.15.01; VE05.06.(01/02/03/04); VE05.07.01; VE10.15.(01/02); VE10.25.01; VE10.27.(01/02/03); VE10.28.(01/02); VE10.29.01; VE10.37.(01/02); VE10.53.01.(01/02); VE10.54.(01/02/03).*

The relationship between the SoC and the Caliptra block is illustrated below. Crypto derivations (the initialization of contexts leading to CTX_RTn) are performed only on cold reset. No crypto derivations are performed during warm reset or update reset.

![Module initialization sequence](../../Images/ModuleInitializationSequence.png)

## INIT detail
After the Caliptra microcontroller is out of reset, ROM executes an initialization script that:
- Resets instruction counter.
- Disables interrupts.
- Clears all general purpose registers.
- Sets up memory region attributes (Cacheable & Side effects).
- Sets up stack pointer.
- Sets up NMI and Exception handler.
- Zeros ICCM & DCCM memories (to initialize ECC).
- Jumps to Rust entry point.

## READ_SECRETS detail
Available only during cold reset. Described in documentation as [decrypt secrets](https://github.com/chipsalliance/caliptra-sw/tree/main/rom/dev#decrypt-secrets); however, “decryption” is provided by a non-approved Deobfuscation Engine. 
- UDS is deobfuscated and stored to Key Vault Slot 0.
- Field Entropy is deobfuscated and stored to Key Vault Slot 1.

## IDevId, LDevId and FMC context details
After Caliptra has deobfuscated secrets, Caliptra constructs the IDevId and LDevId contexts (layers):
- Calculates UDS Digest (SHA2-384) from UDS.
- Derives IDEVID_Priv and IDEVID_Pub from UDS Digest.
- Forms the IDEVID CSR.
- Calculates CDILDEVID (HMAC-SHA2-384 KBKDF) from UDS Digest.
- Derives LDEVID_Priv and LDEVID_Pub from CDILDEVID.
- Forms the LDevId CSR / Certificate.

## ROM AWAIT_CMD detail
Caliptra ROM asserts the READY_FOR_FW wire by writing an internal register; this register is also visible to read on the APB interface, hence the SoC can choose to poll on this bit instead of awaiting assertion of the signal as an interrupt . SoC pushes Caliptra FW into the mailbox, following the Sender Protocol (see Section 2.1.1). See also the Caliptra boot flow depiction in Caliptra documentation. 
Caliptra ROM enables the mailbox; until this point, any accidental or non-accidental writes that target the mailbox are dropped by the hardware. The command parser performs a switch-case check for all supported commands, with a default to handle all unsupported commands. The subset of mailbox commands accepted in the ROM phase are listed in Section 2.2 (ROM heading). Additional command specific checks may be performed within each handler.

## FIRMWARE_LOAD detail
The images to be loaded are stored in containers, as depicted in Section 2.4.1. Generally, a container can contain one or multiple images, as blocks of data with an associated load address. The SoC ROM/FMC boot establishes a firmware chain-of-trust: each firmware fetches, authenticates, measures, and executes the next firmware needed to establish the device operating environment. Each firmware deposits the next firmware's measurements into Caliptra prior to execution. The exception is Caliptra's firmware: SoC firmware delegates the measurement and execution of Caliptra's firmware to Caliptra ROM. 
On Caliptra ROM receipt of the FW_LOAD CommandId:
1.	Caliptra ROM authenticates, measures, and starts the Caliptra FMC firmware.
2.	Caliptra FMC firmware authenticates, measures, and starts the Caliptra Runtime firmware.
3.	The SoC may issue STASH_MEASUREMENT commands for measurements of other images.
4.	On completion of the FIRMWARE_LOAD command, Caliptra asserts READY_FOR_RTFLOWS wire and transitions the Module into the Runtime phase period, awaiting mailbox commands.

## Self-test Detail
For all self-tests, pre-computed inputs and reference output values are stored in the firmware image. 
VE10.15.01: The function run_fips_test is invoked from main.rs of ROM.
VE10.20.01: The SHA2-256 used for the ROM code integrity test is self-tested prior to the integrity test.
The full set of ROM CASTs are invoked with caliptra_kat::execute_kat(env).
- Sha1Kat::execute – [FIPS 140IG] 10.3.A R2 B1.
- Sha256Kat::execute [FIPS140IG] 10.3.A R2 B2.
- Sha384Kat::execute [FIPS140IG] 10.3.A R2 B4, B6. Self-test of SHA2-512 is required before use.
- Sha512AccKat::execute [FIPS140IG] 10.3.A R2 B4, B6. 
- Ecc384Kat::execute [FIPS140IG] 10.3.A R11 B4, B6.
- Hmac384KdfKat::execute  [FIPS140IG] 10.3.A R5
- LmsKat::execute [FIPS140IG] 10.3.A R6 B2

Firmware Integrity tests 
- Caliptra ROM firmware integrity test: 
  - Calculate SHA2-256 digest over the complete ROM image. 
  - Compare the calculated digest to the reference digest.
  - Failure yields the ERROR state.
- Caliptra FMC firmware integrity test:
  - Calculate SHA2-384 digest over the complete FMC image. 
  - Compare the calculated digest to the reference digest.
  - Failure yields the ERROR state.
- Caliptra Runtime (RT) firmware integrity test:
  - Calculate SHA2-384 digest over the complete RT image. 
  - Compare the calculated digest to the reference digest.
  - Failure yields the ERROR state.
