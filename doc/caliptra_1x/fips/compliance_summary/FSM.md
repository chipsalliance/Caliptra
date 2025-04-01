## Runtime Behavior, Inclusive of Finite State Model
*Ref: VE03.07.(01/02/03); VE03.10.(01/02); VE10.08.01; VE10.09.01; VE10.10.01; VE10.12.01; VE10.15.02; VE11.08.01*

## Module States
<table>
<caption><p>Table 9: Module States</p></caption>
<colgroup>
<col style="width: 15%" />
<col style="width: 84%" />
</colgroup>
<thead>
<tr>
<th style="text-align: left;">State</th>
<th style="text-align: left;">Description</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: left;">ANY</td>
<td style="text-align: left;">Notational convenience (rather than many arrows).</td>
</tr>
<tr>
<td style="text-align: left;">OFF</td>
<td style="text-align: left;">The module is off. Equivalent to AS11.10
<em><strong>Power on/off state</strong>.</em></td>
</tr>
<tr>
<td style="text-align: left;">INIT</td>
<td style="text-align: left;">The cold reset INIT state – equivalent to the AS11.10 <em><strong>General initialization state</strong>.</em></td>
</tr>
<tr>
<td style="text-align: left;">SELF-TEST</td>
<td style="text-align: left;">AS11.10 <em><strong>Self-test state</strong></em>.</td>
</tr>
<tr>
<td style="text-align: left;">ST01</td>
<td style="text-align: left;">Conditional self-test: SHA2-256 KAT (prior to FW Integrity test per AS10.20). Sha256Kat::default().execute.</td>
</tr>
<tr>
<td style="text-align: left;">ST02</td>
<td style="text-align: left;">FW Integrity test: SHA2-256 digest over ROM code. rom_integrity_test(<u>env</u>, &amp;rom_info.sha256_digest)?;.</td>
</tr>
<tr>
<td style="text-align: left;">ST03</td>
<td style="text-align: left;">Conditional self-test of internal SHA2-512 engine: execute_kat &gt; Sha384Kat::default().execute.</td>
</tr>
<tr>
<td style="text-align: left;">ST04</td>
<td style="text-align: left;">Conditional self-test of accelerator SHA2-512 engine: execute_kat &gt; Sha384AccKat::default().execute.</td>
</tr>
<tr>
<td style="text-align: left;">ST05</td>
<td style="text-align: left;">Conditional self-test of ECDSA ???: execute_kat &gt; Ecc384Kat::default().execute.</td>
</tr>
<tr>
<td style="text-align: left;">ST06</td>
<td style="text-align: left;">Conditional self-test of HMAC-SHA2-384:execute_kat &gt; Hmac384KdfKat::default().execute.</td>
</tr>
<tr>
<td style="text-align: left;">ST07</td>
<td style="text-align: left;">Conditional self-test of LMS: execute_kat &gt; LmsKat::default().execute.</td>
</tr>
<tr>
<td style="text-align: left;">READ SECRETS</td>
<td style="text-align: left;">Equivalent to the AS11.10 <em><strong>CSP entry state</strong></em>.</td>
</tr>
<tr>
<td style="text-align: left;">CTX IDEVID</td>
<td style="text-align: left;">IDevId layer identity and measurement generation.</td>
</tr>
<tr>
<td style="text-align: left;">CTX LDEVID</td>
<td style="text-align: left;">LDevId layer identity and measurement generation.</td>
</tr>
<tr>
<td style="text-align: left;">CTX FMC</td>
<td style="text-align: left;">FMC layer identity and measurement generation.</td>
</tr>
<tr>
<td style="text-align: left;">CTX RTn</td>
<td style="text-align: left;">Runtime layer identity and measurement generation (1 of n layers / contexts).</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Fn process_mailbox_command: equivalent to the AS11.10 <em><strong>Crypto Officer State</strong>.</em></td>
</tr>
<tr>
<td style="text-align: left;">MB SERVICE</td>
<td
style="text-align: left;">FirmwareProcessor::process_mailbox_command: equivalent to the AS11.10 <em><strong>Approved state</strong>.</em></td>
</tr>
<tr>
<td style="text-align: left;">FW_LOAD</td>
<td style="text-align: left;">Process CommandId FIRMWARE_LOAD.</td>
</tr>
<tr>
<td style="text-align: left;">IDENTITY</td>
<td style="text-align: left;">Process an <em>Identity</em><em>Management</em> service CommandId.</td>
</tr>
<tr>
<td style="text-align: left;">MEASUREMENT</td>
<td style="text-align: left;">Process a <em>Measurement</em> service CommandId.</td>
</tr>
<tr>
<td style="text-align: left;">SANITIZE</td>
<td style="text-align: left;">Vendor-specific destruction of CSPs.</td>
</tr>
<tr>
<td style="text-align: left;">SELF-TEST</td>
<td style="text-align: left;"><p>Processing the CommandId SELF_TEST_START invokes run_fips_test.</p>
<p>Processing the CommandId SELF_TEST_GET_RESULTS reports outcome.</p></td>
</tr>
<tr>
<td style="text-align: left;"><a href="#_Utility">UTILITY</a></td>
<td style="text-align: left;">Process a <a
href="#_Utility"><em>Utility</em> service</a> CommandId.</td>
</tr>
<tr>
<td style="text-align: left;"><a href="#_Verify">VERIFY</a></td>
<td style="text-align: left;">Process a <a
href="#_Verify"><em>Verify</em> service</a> CommandId.</td>
</tr>
<tr>
<td style="text-align: left;"><a href="#_Version">VERSION</a></td>
<td style="text-align: left;">Process a <a
href="#_Version"><em>Version</em> service</a> CommandId.</td>
</tr>
<tr>
<td style="text-align: left;">ERROR</td>
<td style="text-align: left;">Equivalent to the AS11.10 <em><strong>Error state</strong></em>.</td>
</tr>
</tbody>
</table>

All AS11.10 required states are cited above, with the exception of:

- *User state* (the User role is not implemented).

- *Bypass state* (the Module does not support Bypass).

- *Quiescent state* (support for this state is vendor specific).

See linked command specifications in Section 2.4 for Control In (CI), Data In (DI), Data Out (DO) and Status Out (SO) details.

Abbreviations used below: 
- CC/CS: Command code/checksum.
- CS/FS: Checksum/FIPS Status. 
- IDH: ID Handle.
- MI: Measurement item.
- MS: Message to be signed. 
- DS: Digital Signature.
- V: Version output.

## Transitions
<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 17%" />
<col style="width: 41%" />
<col style="width: 6%" />
<col style="width: 6%" />
<col style="width: 5%" />
<col style="width: 7%" />
</colgroup>
<thead>
<tr>
<th style="text-align: left;">From</th>
<th style="text-align: left;">To</th>
<th style="text-align: left;">Cause of transition</th>
<th style="text-align: center;">CI</th>
<th style="text-align: center;">DI</th>
<th style="text-align: center;">DO</th>
<th style="text-align: center;">SO</th>
</tr>
</thead>
<tbody>
<tr>
<td style="text-align: left;">OFF</td>
<td style="text-align: left;">INIT</td>
<td style="text-align: left;">Power on or cold reset.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">INIT</td>
<td style="text-align: left;">SELF-TEST</td>
<td style="text-align: left;">General initialization complete.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">SELFTEST</td>
<td style="text-align: left;">ST01</td>
<td style="text-align: left;">Self-test setup (completion of boot status
report).</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST01</td>
<td style="text-align: left;">ST02</td>
<td style="text-align: left;">ST01 completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST02</td>
<td style="text-align: left;">ST03</td>
<td style="text-align: left;">ST02 completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST03</td>
<td style="text-align: left;">ST04</td>
<td style="text-align: left;">ST03 completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST04</td>
<td style="text-align: left;">ST05</td>
<td style="text-align: left;">ST04 completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST05</td>
<td style="text-align: left;">ST06</td>
<td style="text-align: left;">ST05 completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST06</td>
<td style="text-align: left;">ST07</td>
<td style="text-align: left;">ST06 completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST07</td>
<td style="text-align: left;">SELF-TEST</td>
<td style="text-align: left;">ST07 completion; success of all
self-tests.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">ST07</td>
<td style="text-align: left;">ERROR</td>
<td style="text-align: left;">ST07 completion; failure of any
self-test.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">SELFTEST</td>
<td style="text-align: left;">READ_SECRETS</td>
<td style="text-align: left;">Pre-operational phase self-test successful
completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">SELFTEST</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">On-demand self-test successful
completion.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">READ_SECRETS</td>
<td style="text-align: left;">CTX_IDEVID</td>
<td style="text-align: left;">Successful deobfuscation of secrets (UDS,
Field entropy).</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">CTX_IDEVID</td>
<td style="text-align: left;">CTX_LDEVID</td>
<td style="text-align: left;">@CWG: what triggers IDevId &gt; LDevId
context switch ?</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">CTX_LDEVID</td>
<td style="text-align: left;">CTX_FMC</td>
<td style="text-align: left;">Completion of FW_LOAD, ROM hand-off to
FMC.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">CTX_FMC</td>
<td style="text-align: left;">CTX_RTn</td>
<td style="text-align: left;">FMC hand-off to Runtime.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">CTX_RTn</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Runtime entry into fn
process_mailbox_commands loop.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">FIPS_OK</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">FW_LOAD</td>
<td style="text-align: left;">Receipt of CommandId::FirmwareLoad.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">IMGC</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">FW_LOAD</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Successful completion of
CommandId::FirmwareLoad.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">FW_LOAD</td>
<td style="text-align: left;">ERROR</td>
<td style="text-align: left;">Unsuccessful completion of
CommandId::FirmwareLoad.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;"></td>
<td style="text-align: center;"></td>
<td style="text-align: center;">ERROR</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">IDENTITY</td>
<td style="text-align: left;">Receipt of any <a
href="#_Identity_Management"><em>Identity</em> <em>Management</em>
service</a> CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">IDH</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">IDENTITY</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Identity</em>
<em>Management</em> service CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">MEASUREMENT</td>
<td style="text-align: left;">Receipt of any <a
href="#_Measurement"><em>Measurement</em> service</a> CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">?</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">MEASUREMENT</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Measurement</em> service
CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">MI</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">SANITIZE</td>
<td style="text-align: left;">Receipt of any <a
href="#_Sanitize"><em>Sanitize</em> service</a> CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">SANITIZE</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Sanitize</em> service
CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">SELF-TEST</td>
<td style="text-align: left;">Receipt of any SELF_TEST_START
CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">SELF-TEST</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Identity</em>
<em>Management</em> service CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">UTILITY</td>
<td style="text-align: left;">Receipt of any <a
href="#_Utility"><em>Utility</em> service</a> CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">UTILITY</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Utility</em> service
CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">VERIFY</td>
<td style="text-align: left;">Receipt of any <a
href="#_Verify"><em>Verify</em> service</a> CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">MS</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">VERIFY</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Verify</em> service
CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">DS</td>
<td style="text-align: center;">CS/FS</td>
</tr>
<tr>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">VERSION</td>
<td style="text-align: left;">Receipt of any <a
href="#_Version"><em>Version</em> service</a> CommandId.</td>
<td style="text-align: center;">CC/CS</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
</tr>
<tr>
<td style="text-align: left;">VERSION</td>
<td style="text-align: left;">AWAIT CMD</td>
<td style="text-align: left;">Completion of <em>Version</em> service
CommandId.</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;">--</td>
<td style="text-align: center;"><p>CS/FS,</p>
<p>V</p></td>
</tr>
</tbody>
</table>


<img src="../../Images/CaliptraFSM.png" width="1200" height="600">  

```
stateDiagram-v2
  OFF --> INIT: Power-on, cold reset
  INIT --> SELFTEST
  READ_SECRETS --> CTX_IDEVID
  CTX_IDEVID --> AWAIT_CMD
  CTX_IDEVID --> CTX_LDEVID
  CTX_LDEVID --> AWAIT_CMD
  CTX_LDEVID --> CTX_FMC
  CTX_FMC --> AWAIT_CMD
  CTX_FMC --> CTX_RTn
  CTX_RTn --> AWAIT_CMD
  
  state SELFTEST {
    direction LR
    [*] --> ST01
    ST01 --> ST02
    ST02 --> ST03
    ST03 --> ST04
    ST04 --> ST05
    ST05 --> ST06
    ST06 --> ST07
    ST07 --> [*]
  }

SELFTEST --> ERROR
SELFTEST --> READ_SECRETS
SELFTEST --> AWAIT_CMD</td>

state AWAIT_CMD {
  direction TB
  [*] --> IDENTITY
  IDENTITY --> [*]
  [*] --> MEASUREMENT
  MEASUREMENT --> [*]
  [*] --> SANITIZE
  SANITIZE --> [*]
  [*] --> UTILITY
  UTILITY --> [*]
  [*] --> VERIFY
  VERIFY --> [*]
  [*] --> VERSION
  VERSION --> [*]
}

AWAIT_CMD --> SELFTEST
```
