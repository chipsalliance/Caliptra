# Non-applicable requirements

See the ISO/IEC sources for requirement text.

### Not applicable to a hardware module
- AS02.05-06
- AS02.16-18
- AS05.05
- AS06.02-29
- AS07.17-33
- AS09.19, AS09.34-37 (Note that the module is expected to meet L2-L3 requirements in this section).
- AS11.19-21, AS11.30

### No known exclusions in the baseline module
- AS02.13-14

### No degraded mode
- AS02.25-32

### No control output interface
- AS03.09-10

### Out of scope for Security Level 1 overall
- AS03.16-22
- AS05.15-23
- AS07.34-42, AS07.73-86
- AS08.06-07
- AS09.20-24
- AS10.54-55
- AS11.27-28, AS11.31, AS11.33-35, AS11.37
- AS12.03-04

Note that the module is capable of meeting several AS11 L2+ requirements currently: AS11.22-25. AS11.26 is subject to the interpretation. The module incorporates unusable (latent) functionality.

### No user role (or role other than CO)
- AS04.06
- AS11.13

### No maintenance role, state or associated functionality
- AS04.07
- AS07.11-13, AS07-16

### No Bypass
- AS04.18-22
- AS10.21-22, AS10.47-51

### Loaded firmware is not a complete image replacement
- AS04.33-35

### Authentication is not required at Level 1
- AS04.36-55, AS04.57-59

### Fimrware integrity test does not use EDC
- AS05.07

### No zeroization for "physical security purposes" is required
- AS07.10

### Not applicable to single-chip emobodiments
- AS07.43-72

### The CMVP currently treats non-invasive attacks under AS12
AS08.01-07

### The module is wholly deterministic, no random source is required
- AS09.07-09

### No manual SSP establishment
***Note that this section is currently oddly interpreted; this list presumes an RFG gets traction***
- AS09.11-12, AS09.14-15
- AS10.42-46

### No cryptographicall protected SSPs cross the module boundary
- AS09.10, AS09.13

### No plaintext CSP output 
- AS09.16-17

### No wireless SSP I/O
- AS09.18

### The (hardware) module does include firmware
- AS10.19 (but this is irrelevant since the module implements self-tests).

### No critical functions are identified
- AS10.23-24, AS10.52

This section is ambiguous - currently, there is no good definition of a critical function. Guidance would be helpful but none is available.

### The module uses KATs for the Cryptographic Algorithm Self-Tests
- AS10.33-34

