FIPS Error States
*Ref: VE03.07.01; VE11.08.01; VE10.07.01; VE10.08.01; VE10.09.01.*

This section is taken from the [Caliptra Error Reporting and Handling](https://github.com/chipsalliance/Caliptra/blob/main/doc/Caliptra.md#error-reporting-and-handling) documentation, reorganizing it to align with the [FIPS140-3] notions of hard (Fatal) and soft (non-fatal) errors.

## Fatal errors
### Hardware
- ICCM, DCCM SRAM ECC.
- The second watchdog (WD) timer expiry triggers an NMI, and a FATAL error is signaled to the SoC.

### Firmware
- Control Flow Integrity (CFI) errors.
- KAT errors.
- FIPS Self-test errors.
- Mailbox commands received after FIPS Shutdown request completes.
- Hand-off errors detected upon transfer of control from ROM to FMC or FMC to Runtime.
- Mailbox protocol violations leading the mailbox to an inconsistent state if encountered by ROM during cold reset flow.
- Firmware image verification or authentication failures if encountered by ROM during Cold Reset flow.
- Non-aligned access to ICCM or DCCM.
- AHB access hangs, triggered through WD timer expiry.
- AHB access outside of the decoding range.

Fatal errors log the FATAL ERROR reasons into an architectural register that is RW from the external world. This register must be sticky (as in, reset is on powergood). This register may be cleared at any time via register write (W1C). When a fatal error occurs, all volatile assets that are stored in key vault are cleared.
Caliptra signals fatal errors using a cptra_error_fatal wire.
- SoCs should connect this into their SoC error handling logic. Upon detection of a FATAL ERROR in Caliptra, SoC shall treat any outstanding commands with Caliptra as failed, and SoC may recover by performing a Caliptra reset using the signal cptra_rst_b.
- This signal prevents forward progress of the boot process if measurement submission to Caliptra fails. If SoC detects a Caliptra fatal error while the SoC is in steady state, then there is no obligation for the SoC to immediately address that error. If rebooting the SoC for such failures is deemed unacceptable to uptime, the SoC should implement the ability to trigger a Caliptra warm reset independently of the SoC, and may use this mechanism to recover.
- Error mask registers (writable only by Caliptra microcontroller) may be used to prevent error signal assertion per-event. Mask registers only impact interrupts when they are set prior to the error occurrence.
- cptra_error_fatal remains asserted until Caliptra is reset. Note that, although the HW FATAL ERROR register fields may be cleared at any time, a reset is still required to clear the interrupt.

## Non-fatal errors
### Hardware
- Mailbox SRAM ECC (except initial firmware load).
- Mailbox incorrect protocol or commands. For example, incorrect access ordering or access without Lock.


### Firmware
- Firmware image verification or authentication failures if encountered by ROM during Update Reset flow.
- Mailbox protocol violations leading the mailbox to an inconsistent state (if encountered by ROM during Update Reset flow).
- Cryptography processing errors.

Non-fatal errors log the NON-FATAL ERROR reasons into an architectural register that is RW from the external world. This register must be sticky (as in, reset is on powergood). This register may be cleared at any time via register write (W1C).
Caliptra signals non-fatal errors using a cptra_error_non_fatal wire.
- Caliptra reset via cptra_rst_b, or a write to clear the NON-FATAL ERROR register, cause the interrupt to deassert.
- It is optional for SoCs to include this signal in their logic.
